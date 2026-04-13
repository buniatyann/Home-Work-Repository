#include "cli/cli.h"
#include "core/errors/errors.h"
#include "engine/execution/executor.h"
#include "engine/graph/graph.h"
#include "engine/rule_database/rule_database.h"
#include "eval/expander.h"
#include "eval/variable_table.h"
#include "parser/lexer/lexer.h"
#include "parser/parser/parser.h"

#include <filesystem>
#include <iostream>

namespace {

constexpr int MAX_INCLUDE_DEPTH = 16;

void evaluate_makefile(const mymake::ast::Makefile& makefile,
                       mymake::VariableTable& vars,
                       mymake::Expander& expander,
                       mymake::RuleDatabase& rules,
                       mymake::Lexer& lexer,
                       mymake::Parser& parser,
                       int include_depth) {
    if (include_depth > MAX_INCLUDE_DEPTH) {
        throw mymake::MakeError("include depth limit exceeded (circular include?)");
    }

    for (auto& node : makefile) {
        if (auto* rule = std::get_if<mymake::ast::Rule>(&node)) {
            // Expand targets and prerequisites now (recipes are expanded at execution time).
            std::vector<std::string> expanded_targets;
            for (const auto& t : rule->targets) {
                auto words = mymake::Parser::split_words(expander.expand(t));
                expanded_targets.insert(expanded_targets.end(), words.begin(), words.end());
            }

            std::vector<std::string> expanded_normal;
            for (const auto& p : rule->normal_prereqs) {
                auto words = mymake::Parser::split_words(expander.expand(p));
                expanded_normal.insert(expanded_normal.end(), words.begin(), words.end());
            }

            std::vector<std::string> expanded_order;
            for (const auto& p : rule->order_only_prereqs) {
                auto words = mymake::Parser::split_words(expander.expand(p));
                expanded_order.insert(expanded_order.end(), words.begin(), words.end());
            }

            if (rule->is_pattern) {
                for (const auto& target : expanded_targets) {
                    mymake::PatternRule prule;
                    prule.target_pattern = target;
                    prule.prereq_patterns = expanded_normal;
                    prule.recipes = rule->recipes;
                    prule.loc = rule->loc;
                    rules.add_pattern_rule(std::move(prule));
                }
            } else {
                for (const auto& target : expanded_targets) {
                    mymake::ExplicitRule erule;
                    erule.target = target;
                    erule.normal_prereqs = expanded_normal;
                    erule.order_only_prereqs = expanded_order;
                    erule.recipes = rule->recipes; // recipes stay raw — expanded at execution time
                    erule.is_double_colon = rule->is_double_colon;
                    erule.loc = rule->loc;
                    rules.add_explicit_rule(std::move(erule));
                }
            }
        }
        else if (auto* assign = std::get_if<mymake::ast::VariableAssignment>(&node)) {
            mymake::VarOrigin origin = assign->is_override
                ? mymake::VarOrigin::Override : mymake::VarOrigin::File;

            switch (assign->flavor) {
            case mymake::ast::VariableAssignment::Simple: {
                // := — expand value now, store as Simple.
                std::string expanded = expander.expand(assign->value);
                vars.set(assign->name, expanded, mymake::VarFlavor::Simple, origin);
                break;
            }
            case mymake::ast::VariableAssignment::Recursive:
                // = — store raw, expand on every use.
                vars.set(assign->name, assign->value,
                         mymake::VarFlavor::Recursive, origin);
                break;
            case mymake::ast::VariableAssignment::Append: {
                // += — if variable is Simple, expand new value first.
                auto existing = vars.lookup_full(assign->name);
                if (existing && existing->flavor == mymake::VarFlavor::Simple) {
                    vars.append(assign->name, expander.expand(assign->value));
                } else {
                    vars.append(assign->name, assign->value);
                }
                break;
            }
            case mymake::ast::VariableAssignment::Conditional:
                // ?= — set only if undefined, treated as Recursive.
                vars.set_conditional(assign->name, assign->value,
                                     mymake::VarFlavor::Recursive, origin);
                break;
            }
        }
        else if (auto* inc = std::get_if<mymake::ast::Include>(&node)) {
            for (const auto& file_expr : inc->files) {
                std::string expanded = expander.expand(file_expr);
                auto filenames = mymake::Parser::split_words(expanded);

                for (const auto& f : filenames) {
                    try {
                        auto inc_lines = lexer.lex_file(f);
                        auto inc_ast = parser.parse(inc_lines);
                        evaluate_makefile(inc_ast, vars, expander, rules,
                                          lexer, parser, include_depth + 1);
                    } catch (const mymake::MakeError& e) {
                        if (!inc->is_silent) throw;
                        // -include / sinclude: silently ignore missing files.
                    }
                }
            }
        }
    }
}

} // anonymous namespace

int main(int argc, char* argv[]) {
    try {
        auto config = mymake::parse_args(argc, argv);

        // Change directory if requested
        if (!config.directory.empty()) {
            std::filesystem::current_path(config.directory);
        }

        // Set up variable table with command-line overrides
        mymake::VariableTable vars;
        for (const auto& [name, value] : config.overrides) {
            vars.set(name, value, mymake::VarFlavor::Simple,
                     mymake::VarOrigin::CommandLine);
        }

        mymake::Expander expander(vars);
        mymake::Lexer lexer;
        mymake::Parser parser;
        mymake::RuleDatabase rules;

        // Lex + Parse
        auto lines = lexer.lex_file(config.makefile_path);
        auto makefile = parser.parse(lines);

        // Evaluate: walk AST, expand variables, process includes, populate rules
        evaluate_makefile(makefile, vars, expander, rules, lexer, parser, 0);

        // Determine goals
        std::vector<std::string> goals = config.goals;
        if (goals.empty()) {
            if (rules.default_goal) {
                goals.push_back(*rules.default_goal);
            } else {
                std::cerr << "my_make: *** No targets.  Stop." << std::endl;
                return 2;
            }
        }

        // Build dependency graph
        mymake::DependencyGraph graph;
        graph.build(goals, rules);

        // Execute
        mymake::Executor executor(config, vars);
        return executor.execute(graph, goals);

    } catch (const mymake::MakeError& e) {
        std::cerr << mymake::format_error(e) << std::endl;
        return 2;
    } catch (const std::exception& e) {
        std::cerr << "my_make: *** " << e.what() << std::endl;
        return 2;
    }
}
