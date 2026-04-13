#include "core/config/config.h"
#include "engine/execution/executor.h"
#include "engine/graph/graph.h"
#include "engine/rule_database/rule_database.h"
#include "eval/variable_table.h"
#include <gtest/gtest.h>

using namespace mymake;

class ExecutorTest : public ::testing::Test {
protected:
    Config config;
    VariableTable vars;

    void SetUp() override {
        config.dry_run = true; // don't actually run commands
    }
};

TEST_F(ExecutorTest, DryRunPrintsCommand) {
    RuleDatabase rules;
    ExplicitRule r;
    r.target = "all";
    r.recipes = {"echo hello"};
    rules.add_explicit_rule(std::move(r));

    // Mark as phony so it always "needs rebuild"
    rules.phony_targets.insert("all");

    DependencyGraph graph;
    graph.build({"all"}, rules);

    Executor executor(config, vars);
    int rc = executor.execute(graph, {"all"});
    EXPECT_EQ(rc, 0);
}

TEST_F(ExecutorTest, NoRuleForTarget) {
    RuleDatabase rules;
    DependencyGraph graph;
    graph.build({"nonexistent"}, rules);

    Executor executor(config, vars);
    int rc = executor.execute(graph, {"nonexistent"});
    EXPECT_NE(rc, 0);
}
