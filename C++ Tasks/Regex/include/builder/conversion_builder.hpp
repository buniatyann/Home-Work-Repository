#ifndef CONVERSION_BUILDER_H
#define CONVERSION_BUILDER_H

#include "engine_nfa.hpp"
#include "ast.hpp"
#include <functional>
#include <memory>
#include <stdexcept>

class conversion_builder {
public:
    // using unique_ptr<engine_nfa> = ??;

    explicit conversion_builder(std::function<std::unique_ptr<engine_nfa>()> nfa_factory);
    std::unique_ptr<engine_nfa> regex_to_nfa(std::shared_ptr<pattern> regex_ast);

private:
    std::function<std::unique_ptr<engine_nfa>()> nfa_factory_;
    
    std::unique_ptr<engine_nfa> regex_to_nfa(std::shared_ptr<pattern> regex_ast, int group_id);
    std::unique_ptr<engine_nfa> single_regex_to_nfa(std::shared_ptr<regex> regex);
    std::unique_ptr<engine_nfa> alternative_to_nfa(std::shared_ptr<regex_alternative> alternative);
    std::unique_ptr<engine_nfa> asterisk(std::function<std::unique_ptr<engine_nfa>()> builder, bool lazy);
    std::unique_ptr<engine_nfa> plus(std::function<std::unique_ptr<engine_nfa>()> builder, bool lazy);
    std::unique_ptr<engine_nfa> asterisk_plus(std::function<std::unique_ptr<engine_nfa>()> builder, bool lazy, bool asterisk);
    std::unique_ptr<engine_nfa> atomic_pattern_nfa(const std::string& character);
    std::unique_ptr<engine_nfa> dot_pattern_nfa();
    std::unique_ptr<engine_nfa> character_class_nfa(const std::string& clazz);
    std::unique_ptr<engine_nfa> complex_character_class_nfa(std::shared_ptr<complex_class> ccc);
    std::unique_ptr<engine_nfa> one_step_nfa(std::shared_ptr<matcher> matcher);
    
    static std::string new_state();
    static void state_back();
    static int new_group();
    static void reset_group_numbers();
    static void reset_state_numbers();
};

#endif // CONVERSION_BUILDER_H