#include "conversion_builder.hpp"
#include "matchers.hpp"
#include <stdexcept>

namespace {
    int state_counter = 0;
    int group_counter = 0;
    const std::string epsilon = "EPSILON";
    std::shared_ptr<matcher> epsilon_matcher = std::make_shared<character_matcher>(epsilon);

    bool is_word_char(const std::string& c) {
        if (c.empty()) return false;
        char ch = c[0];
        
        return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9') || ch == '_';
    }

    bool is_space_char(const std::string& c) {
        if (c.empty()) return false;
        static const std::string single_space = " \f\n\r\t\v\u00a0\u1680\u2028\u2029\u202f\u205f\u3000\ufeff";
        
        return single_space.find(c) != std::string::npos || (c >= "\u2000" && c <= "\u200a");
    }

    std::shared_ptr<matcher> get_class_matcher(const std::string& clazz) {
        if (clazz == "\\d") {
            return std::make_shared<positive_matcher>(
                [](const std::string& c) { return !c.empty() && c[0] >= '0' && c[0] <= '9'; }, clazz);
        } 
        else if (clazz == "\\D") {
            return std::make_shared<negated_matcher>(
                [](const std::string& c) { return c.empty() || c[0] < '0' || c[0] > '9'; }, clazz);
        } 
        else if (clazz == "\\w") {
            return std::make_shared<positive_matcher>(is_word_char, clazz);
        } 
        else if (clazz == "\\W") {
            return std::make_shared<negated_matcher>([](const std::string& c) { return !is_word_char(c); }, clazz);
        } 
        else if (clazz == "\\s") {
            return std::make_shared<positive_matcher>(is_space_char, clazz);
        } 
        else if (clazz == "\\S") {
            return std::make_shared<negated_matcher>([](const std::string& c) { return !is_space_char(c); }, clazz);
        }
        
        throw std::runtime_error("Unknown character class: " + clazz);
    }
}

conversion_builder::conversion_builder(std::function<std::unique_ptr<engine_nfa>()> nfa_factory)
    : nfa_factory_(nfa_factory) {}

std::string conversion_builder::new_state() {
    return "q" + std::to_string(state_counter++);
}

void conversion_builder::state_back() {
    --state_counter;
}

int conversion_builder::new_group() {
    return group_counter++;
}

void conversion_builder::reset_group_numbers() {
    group_counter = 0;
}

void conversion_builder::reset_state_numbers() {
    state_counter = 0;
}

std::unique_ptr<engine_nfa> conversion_builder::regex_to_nfa(std::shared_ptr<pattern> regex_ast) {
    reset_state_numbers();
    reset_group_numbers();
    
    return regex_to_nfa(regex_ast, 0);
}

std::unique_ptr<engine_nfa> conversion_builder::regex_to_nfa(std::shared_ptr<pattern> regex_ast, int group_id) {
    if (auto alternative = std::dynamic_pointer_cast<regex_alternative>(regex_ast)) {
        return alternative_to_nfa(alternative);
    } 
    else if (auto regex_ptr = std::dynamic_pointer_cast<regex>(regex_ast)) {
        return single_regex_to_nfa(regex_ptr);
    }
    
    throw std::runtime_error("Invalid regex AST type");
}

std::unique_ptr<engine_nfa> conversion_builder::single_regex_to_nfa(std::shared_ptr<regex> regex) {
    std::unique_ptr<engine_nfa> nfa = nullptr;
    bool is_first = true;
    int group_name = regex->is_capturing_group() ? (regex->group_name.empty() ? new_group() : std::stoi(regex->group_name)) : -1;

    for (const auto& [quantifier_str, pattern] : regex->subpatterns) {
        quantifier quant = quantifier::none;
        if (quantifier_str == "*") {
            quant = quantifier::asterisk
        }
        else if (quantifier_str == "*?") {
            quant = quantifier::lazy_asterisk;
        }
        else if (quantifier_str == "+") {
            quant = quantifier::plus;
        }
        else if (quantifier_str == "+?") {
            quant = quantifier::lazy_plus;
        }
        else if (quantifier_str == "?") {
            quant = quantifier::optional;
        }
        else if (quantifier_str == "??") {
            quant = quantifier::lazy_optional;
        }

        std::function<std::unique_ptr<engine_nfa>()> base_builder;
        if (auto atomic = std::dynamic_pointer_cast<atomic_pattern>(pattern)) {
            base_builder = [this, char_ = atomic->char_]() { return atomic_pattern_nfa(char_); };
        } 
        else if (auto alt = std::dynamic_pointer_cast<regex_alternative>(pattern)) {
            base_builder = [this, alt]() { return alternative_to_nfa(alt); };
        } 
        else if (auto reg = std::dynamic_pointer_cast<regex>(pattern)) {
            base_builder = [this, reg]() { return single_regex_to_nfa(reg); };
        } 
        else if (auto dot = std::dynamic_pointer_cast<dot_pattern>(pattern)) {
            base_builder = [this]() { return dot_pattern_nfa(); };
        } 
        else if (auto clazz = std::dynamic_pointer_cast<character_class>(pattern)) {
            base_builder = [this, clazz_ = clazz->class_]() { return character_class_nfa(clazz_); };
        } 
        else if (auto ccc = std::dynamic_pointer_cast<complex_class>(pattern)) {
            base_builder = [this, ccc]() { return complex_character_class_nfa(ccc); };
        } 
        else if (auto caret = std::dynamic_pointer_cast<caret_anchor>(pattern)) {
            base_builder = [this]() { return one_step_nfa(std::make_shared<start_of_input_matcher>()); };
        } 
        else if (auto dollar = std::dynamic_pointer_cast<dollar_anchor>(pattern)) {
            base_builder = [this]() { return one_step_nfa(std::make_shared<end_of_input_matcher>()); };
        } 
        else {
            throw std::runtime_error("Unknown pattern type");
        }

        if (!is_first) {
            state_back();
        }
        
        is_first = false;

        std::unique_ptr<engine_nfa> base;
        if (quant == quantifier::asterisk || quant == quantifier::lazy_asterisk) {
            base = asterisk(base_builder, quant == quantifier::lazy_asterisk);
        } 
        else if (quant == quantifier::plus || quant == quantifier::lazy_plus) {
            base = plus(base_builder, quant == quantifier::lazy_plus);
        } 
        else if (quant == quantifier::optional || quant == quantifier::lazy_optional) {
            base = base_builder();
            if (quant == quantifier::lazy_optional) {
                base->unshift_transition(base->initial_state_, base->ending_states_[0], epsilon_matcher);
            } 
            else {
                base->add_transition(base->initial_state_, base->ending_states_[0], epsilon_matcher);
            }
        } 
        else {
            base = base_builder();
        }

        if (!nfa) {
            nfa = std::move(base);
        } 
        else {
            nfa->thompson_append_nfa(base, nfa->ending_states_[0]);
        }
    }

    if (group_name != -1) {
        nfa->add_group(nfa->initial_state_, nfa->ending_states_[0], group_name);
    }
    
    return nfa;
}

std::unique_ptr<engine_nfa> conversion_builder::asterisk(std::function<std::unique_ptr<engine_nfa>()> builder, bool lazy) {
    return asterisk_plus(builder, lazy, true);
}

std::unique_ptr<engine_nfa> conversion_builder::plus(std::function<std::unique_ptr<engine_nfa>()> builder, bool lazy) {
    return asterisk_plus(builder, lazy, false);
}

std::unique_ptr<engine_nfa> conversion_builder::asterisk_plus(std::function<std::unique_ptr<engine_nfa>()> builder, bool lazy, bool asterisk) {
    auto base = builder();
    auto new_init = new_state();
    auto new_end = new_state();
    base->add_state(new_init);
    base->add_state(new_end);

    if (lazy) {
        if (asterisk) {
            base->add_transition(new_init, new_end, epsilon_matcher);
        }
        
        base->add_transition(new_init, base->initial_state_, epsilon_matcher);
        base->add_transition(base->ending_states_[0], new_end, epsilon_matcher);
        base->add_transition(base->ending_states_[0], base->initial_state_, epsilon_matcher);
    } 
    else {
        base->add_transition(new_init, base->initial_state_, epsilon_matcher);
        base->add_transition(base->ending_states_[0], base->initial_state_, epsilon_matcher);
        base->add_transition(base->ending_states_[0], new_end, epsilon_matcher);
        if (asterisk) {
            base->add_transition(new_init, new_end, epsilon_matcher);
        }
    }

    base->set_initial_state(new_init);
    base->set_ending_states({new_end});
    
    return base;
}

std::unique_ptr<engine_nfa> conversion_builder::atomic_pattern_nfa(const std::string& character) {
    return one_step_nfa(std::make_shared<character_matcher>(character));
}

std::unique_ptr<engine_nfa> conversion_builder::dot_pattern_nfa() {
    return one_step_nfa(std::make_shared<dot_matcher>());
}

std::unique_ptr<engine_nfa> conversion_builder::character_class_nfa(const std::string& clazz) {
    return one_step_nfa(get_class_matcher(clazz));
}

std::unique_ptr<engine_nfa> conversion_builder::complex_character_class_nfa(std::shared_ptr<complex_class> ccc) {
    auto lambda = [ccc](const std::string& c) { return ccc->matches(c); };
    if (ccc->negated) {
        return one_step_nfa(std::make_shared<negated_matcher>([lambda](const std::string& c) { return !lambda(c); }, ccc->name));
    }
    
    return one_step_nfa(std::make_shared<positive_matcher>(lambda, ccc->name));
}

std::unique_ptr<engine_nfa> conversion_builder::one_step_nfa(std::shared_ptr<matcher> matcher) {
    auto nfa = nfa_factory_();
    auto a = new_state();
    auto b = new_state();
    nfa->declare_states({a, b});
    nfa->set_initial_state(a);
    nfa->set_ending_states({b});
    nfa->add_transition(a, b, matcher);

    return nfa;
}

std::unique_ptr<engine_nfa> conversion_builder::alternative_to_nfa(std::shared_ptr<regex_alternative> alternative) {
    int group_name = alternative->is_capturing_group() ? (alternative->group_name.empty() ? new_group() : std::stoi(alternative->group_name)) : -1;
    auto nfa = nfa_factory_();
    auto start = new_state();
    nfa->add_state(start);
    nfa->set_initial_state(start);
    std::vector<std::string> ending_states;

    for (const auto& alt : alternative->alternatives) {
        auto tmp = single_regex_to_nfa(alt);
        ending_states.insert(ending_states.end(), tmp->ending_states_.begin(), tmp->ending_states_.end());
        nfa->thompson_append_nfa(tmp, start);
    }

    auto end = new_state();
    nfa->add_state(end);
    for (const auto& end_state : ending_states) {
        nfa->add_transition(end_state, end, epsilon_matcher);
    }
    
    nfa->set_ending_states({end});
    if (group_name != -1) {
        nfa->add_group(start, end, group_name);
    }
    
    return nfa;
}