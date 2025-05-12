#ifndef ENGINE_NFA_H
#define ENGINE_NFA_H

#include "matchers.hpp"
#include <string>
#include <unordered_map>
#include <vector>
#include <memory>

class state {
public:
    explicit state(const std::string& name);
    void add_transition(std::shared_ptr<state> to_state, std::shared_ptr<matcher> matcher);
    void unshift_transition(std::shared_ptr<state> to_state, std::shared_ptr<matcher> matcher);
    void add_start_group(int group);
    void add_end_group(int group);
    const std::string& name() const { return name_; }
    const std::vector<std::pair<std::shared_ptr<matcher>, std::shared_ptr<state>>>& transitions() const { return transitions_; }
    const std::vector<int>& starts_groups() const { return starts_groups_; }
    const std::vector<int>& ends_groups() const { return ends_groups_; }

private:
    std::string name_;
    std::vector<std::pair<std::shared_ptr<matcher>, std::shared_ptr<state>>> transitions_;
    std::vector<int> starts_groups_;
    std::vector<int> ends_groups_;
};

struct nfa_result {
    bool success;
    size_t ending_position;
    std::unordered_map<int, std::tuple<int, size_t, size_t>> group_matches;
};

struct compute_memory {
    std::unordered_map<int, size_t> active_groups;
    std::unordered_map<int, std::tuple<int, size_t, size_t>> group_matches;
    std::vector<std::string> epsilon_visited;
    bool success{false};
    size_t ending_position{0};
};

class engine_nfa {
public:
    engine_nfa();
    void set_initial_state(const std::string& state);
    void set_ending_states(const std::vector<std::string>& states);
    void add_state(const std::string& name);
    void declare_states(const std::vector<std::string>& names);
    void add_transition(const std::string& from, const std::string& to, std::shared_ptr<matcher> matcher);
    void unshift_transition(const std::string& from, const std::string& to, std::shared_ptr<matcher> matcher);
    void add_group(const std::string& start, const std::string& end, int group);
    void append_nfa(std::shared_ptr<engine_nfa> nfa, const std::string& union_state, std::shared_ptr<matcher> matcher);
    void thompson_append_nfa(std::shared_ptr<engine_nfa> nfa, const std::string& union_state);
    nfa_result compute(const std::string& string, size_t i = 0) const;
    nfa_result iterative_compute(const std::string& string, size_t i = 0) const;
    static std::shared_ptr<engine_nfa> clone(const engine_nfa& original, std::function<std::string()> state_builder);

private:
    std::unordered_map<std::string, std::shared_ptr<state>> states_;
    std::string initial_state_;
    std::vector<std::string> ending_states_;
    
    void compute_groups(std::shared_ptr<state> state, compute_memory& memory, size_t i) const;
    nfa_result recursive_compute(const std::string& string, std::shared_ptr<state> state, compute_memory memory, size_t i) const;
};

#endif // ENGINE_NFA_H