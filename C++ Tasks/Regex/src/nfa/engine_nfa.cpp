#include "../../include/nfa/engine_nfa.hpp"
#include <algorithm>
#include <stdexcept>
#include <iostream>

constexpr bool debug = false;

state::state(const std::string& name) : name_(name) {}

void state::add_transition(std::shared_ptr<state> to_state, std::shared_ptr<matcher> matcher) {
    transitions_.emplace_back(matcher, to_state);
}

void state::unshift_transition(std::shared_ptr<state> to_state, std::shared_ptr<matcher> matcher) {
    transitions_.insert(transitions_.begin(), {matcher, to_state});
}

void state::add_start_group(int group) {
    starts_groups_.push_back(group);
}

void state::add_end_group(int group) {
    ends_groups_.push_back(group);
}

engine_nfa::engine_nfa() {}

void engine_nfa::set_initial_state(const std::string& state) {
    initial_state_ = state;
}

void engine_nfa::set_ending_states(const std::vector<std::string>& states) {
    ending_states_ = states;
}

void engine_nfa::add_state(const std::string& name) {
    states_[name] = std::make_shared<state>(name);
}

void engine_nfa::declare_states(const std::vector<std::string>& names) {
    for (const auto& n : names) {
        add_state(n);
    }
}

void engine_nfa::add_transition(const std::string& from, const std::string& to, std::shared_ptr<matcher> matcher) {
    auto from_state = states_.find(from);
    auto to_state = states_.find(to);
    if (from_state == states_.end() || to_state == states_.end()) {
        throw std::runtime_error("Invalid state name");
    }
    
    from_state->second->add_transition(to_state->second, matcher);
}

void engine_nfa::unshift_transition(const std::string& from, const std::string& to, std::shared_ptr<matcher> matcher) {
    auto from_state = states_.find(from);
    auto to_state = states_.find(to);
    if (from_state == states_.end() || to_state == states_.end()) {
        throw std::runtime_error("Invalid state name");
    }
    
    from_state->second->unshift_transition(to_state->second, matcher);
}

void engine_nfa::add_group(const std::string& start, const std::string& end, int group) {
    auto start_state = states_.find(start);
    auto end_state = states_.find(end);
    if (start_state == states_.end() || end_state == states_.end()) {
        throw std::runtime_error("Invalid state name");
    }
    
    start_state->second->add_start_group(group);
    end_state->second->add_end_group(group);
}

void engine_nfa::append_nfa(std::shared_ptr<engine_nfa> nfa, const std::string& union_state, std::shared_ptr<matcher> matcher) {
    for (const auto& [name, state] : nfa->states_) {
        states_[name] = state;
    }
    
    add_transition(union_state, nfa->initial_state_, matcher);
    if (std::find(ending_states_.begin(), ending_states_.end(), union_state) != ending_states_.end()) {
        ending_states_.erase(std::remove(ending_states_.begin(), ending_states_.end(), union_state), ending_states_.end());
        ending_states_.insert(ending_states_.end(), nfa->ending_states_.begin(), nfa->ending_states_.end());
    }
}

void engine_nfa::thompson_append_nfa(std::shared_ptr<engine_nfa> nfa, const std::string& union_state) {
    auto union_it = states_.find(union_state);
    if (union_it == states_.end()) {
        throw std::runtime_error("Union state not found");
    }
    
    for (const auto& [name, state] : nfa->states_) {
        if (name != nfa->initial_state_) {
            if (states_.find(name) != states_.end() && name != union_state) {
                throw std::runtime_error("Duplicate state name");
            }
    
            states_[name] = state;
        }
    }
    
    for (const auto& [matcher, to_state] : nfa->states_.at(nfa->initial_state_)->transitions()) {
        add_transition(union_state, to_state->name(), matcher);
    }
    
    for (int group : nfa->states_.at(nfa->initial_state_)->starts_groups()) {
        states_[union_state]->add_start_group(group);
    }
    
    for (int group : nfa->states_.at(nfa->initial_state_)->ends_groups()) {
        states_[union_state]->add_end_group(group);
    }
    
    if (std::find(ending_states_.begin(), ending_states_.end(), union_state) != ending_states_.end()) {
        ending_states_.erase(std::remove(ending_states_.begin(), ending_states_.end(), union_state), ending_states_.end());
        ending_states_.insert(ending_states_.end(), nfa->ending_states_.begin(), nfa->ending_states_.end());
    }
}

void engine_nfa::thompson_append_nfa(std::unique_ptr<engine_nfa> nfa, const std::string& union_state) {
    auto union_it = states_.find(union_state);
    if (union_it == states_.end()) {
        throw std::runtime_error("Union state not found");
    }

    for (const auto& [name, state] : nfa->states_) {
        if (name != nfa->initial_state_) {
            if (states_.find(name) != states_.end() && name != union_state) {
                throw std::runtime_error("Duplicate state name");
            }
            
            states_[name] = state;
        }
    }

    for (const auto& [matcher, to_state] : nfa->states_.at(nfa->initial_state_)->transitions()) {
        add_transition(union_state, to_state->name(), matcher);
    }

    for (int group : nfa->states_.at(nfa->initial_state_)->starts_groups()) {
        states_[union_state]->add_start_group(group);
    }

    for (int group : nfa->states_.at(nfa->initial_state_)->ends_groups()) {
        states_[union_state]->add_end_group(group);
    }

    if (std::find(ending_states_.begin(), ending_states_.end(), union_state) != ending_states_.end()) {
        ending_states_.erase(std::remove(ending_states_.begin(), ending_states_.end(), union_state), ending_states_.end());
        ending_states_.insert(ending_states_.end(), nfa->ending_states_.begin(), nfa->ending_states_.end());
    }
}


void engine_nfa::compute_groups(std::shared_ptr<state> state, compute_memory& memory, size_t i) const {
    for (int group : state->starts_groups()) {
        if (debug) {
            std::cout << "Entered group " << group << " in state " << state->name() << ". i=" << i << std::endl;
        }
    
        memory.active_groups[group] = i;
    }
    for (int group : state->ends_groups()) {
        if (debug) {
            std::cout << "Exited group " << group << " in state " << state->name() << ". i=" << i << std::endl;
        }
    
        memory.group_matches[group] = {group, memory.active_groups.at(group), i};
    }
}

nfa_result engine_nfa::compute(const std::string& string, size_t i) const {
    compute_memory memory;
    return recursive_compute(string, states_.at(initial_state_), memory, i);
}

nfa_result engine_nfa::recursive_compute(const std::string& string, std::shared_ptr<state> current_state, compute_memory memory, size_t i) const {
    compute_groups(current_state, memory, i);
    if (std::find(ending_states_.begin(), ending_states_.end(), current_state->name()) != ending_states_.end()) {
        memory.success = true;
        memory.ending_position = i;
    
        return {memory.success, memory.ending_position, memory.group_matches};
    }

    std::string input = i < string.length() ? std::string(1, string[i]) : "";
    for (const auto& [matcher, to_state] : current_state->transitions()) {
        if (matcher->matches(input, i)) {
            compute_memory copy_memory = memory;
            copy_memory.epsilon_visited.clear();
            if (debug) {
                std::cout << current_state->name() << " -> " << to_state->name() << " with input " << input << std::endl;
            }
    
            auto result = recursive_compute(string, to_state, copy_memory, i + 1);
            if (result.success) {
                return result;
            }
    
            if (debug) {
                std::cout << "Backtracked to state " << current_state->name() << std::endl;
            }
        } 
        else if (matcher->matches("EPSILON", i)) {
            if (std::find(memory.epsilon_visited.begin(), memory.epsilon_visited.end(), to_state->name()) == memory.epsilon_visited.end()) {
                compute_memory copy_memory = memory;
                copy_memory.epsilon_visited.push_back(current_state->name());
                if (debug) {
                    std::cout << current_state->name() << " -> " << to_state->name() << " with input EPSILON" << std::endl;
                }
        
                auto result = recursive_compute(string, to_state, copy_memory, i);
                if (result.success) {
                    return result;
                }
        
                if (debug) {
                    std::cout << "Backtracked to state " << current_state->name() << std::endl;
                }
            }
        }
    }

    nfa_result result;
    result.success = std::find(ending_states_.begin(), ending_states_.end(), current_state->name()) != ending_states_.end();
    result.ending_position = i;
    result.group_matches = memory.group_matches;
    
    return result;
}

nfa_result engine_nfa::iterative_compute(const std::string& string, size_t i) const {
    struct stack_frame {
        std::string string;
        size_t i;
        std::shared_ptr<state> current_state;
        compute_memory memory;
    };
    
    std::vector<stack_frame> stack;
    compute_memory initial_memory;
    stack.push_back({string, i, states_.at(initial_state_), initial_memory});

    while (!stack.empty()) {
        auto frame = stack.back();
        stack.pop_back();
        auto current_state = frame.current_state;
        auto remaining_string = frame.string;
        auto memory = frame.memory;
        auto pos = frame.i;

        compute_groups(current_state, memory, pos);
        if (std::find(ending_states_.begin(), ending_states_.end(), current_state->name()) != ending_states_.end()) {
            return {true, pos, memory.group_matches};
        }

        std::string input = pos < remaining_string.length() ? std::string(1, remaining_string[pos]) : "";
        for (auto it = current_state->transitions().rbegin(); it != current_state->transitions().rend(); ++it) {
            const auto& [matcher, to_state] = *it;
            if (matcher->matches(input, pos)) {
                compute_memory copy_memory = memory;
                copy_memory.epsilon_visited.clear();
                if (debug) {
                    std::cout << current_state->name() << " -> " << to_state->name() << " with input " << input << std::endl;
                }
                stack.push_back({remaining_string.substr(pos < remaining_string.length() ? 1 : 0), pos + 1, to_state, copy_memory});
            } 
            else if (matcher->matches("EPSILON", pos)) {
                if (std::find(memory.epsilon_visited.begin(), memory.epsilon_visited.end(), to_state->name()) == memory.epsilon_visited.end()) {
                    compute_memory copy_memory = memory;
                    copy_memory.epsilon_visited.push_back(current_state->name());
                    if (debug) {
                        std::cout << current_state->name() << " -> " << to_state->name() << " with input EPSILON" << std::endl;
                    }
            
                    stack.push_back({remaining_string, pos, to_state, copy_memory});
                }
            }
        }
    }

    nfa_result result;
    result.success = false;
    result.ending_position = i + string.length();
    result.group_matches = {};

    return result;
}

std::shared_ptr<engine_nfa> engine_nfa::clone(const engine_nfa& original, std::function<std::string()> state_builder) {
    auto cloned = std::make_shared<engine_nfa>();
    std::unordered_map<std::string, std::string> translation;
    for (const auto& [name, state] : original.states_) {
        auto new_name = state_builder();
        translation[name] = new_name;
        cloned->add_state(new_name);
    }
    
    for (const auto& [name, state] : original.states_) {
        for (const auto& [matcher, to_state] : state->transitions()) {
            cloned->add_transition(translation[name], translation[to_state->name()], matcher);
        }
    
        for (int group : state->starts_groups()) {
            cloned->states_[translation[name]]->add_start_group(group);
        }
    
        for (int group : state->ends_groups()) {
            cloned->states_[translation[name]]->add_end_group(group);
        }
    }
    
    cloned->set_initial_state(translation[original.initial_state_]);
    std::vector<std::string> new_ending_states;
    for (const auto& state : original.ending_states_) {
        new_ending_states.push_back(translation[state]);
    }
    
    cloned->set_ending_states(new_ending_states);
    return cloned;
}

std::string engine_nfa::initial_state() const {
    return initial_state_;
}

std::vector<std::string> engine_nfa::ending_state() const {
    return ending_states_;
}