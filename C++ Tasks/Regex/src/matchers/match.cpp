#include "../../include/matchers/match.hpp"

match::match(const std::string &source, std::size_t start, std::size_t end, const std::unordered_map<int, std::string> &groups)
: source_(source), start_(start), end_(end), groups_(groups) {}

match match::from_nfa_result(const std::string &source, std::size_t start, const nfa_result &result)
{
    std::unordered_map<int, std::string> groups;
    if (result.success) {
        for (const auto& [group, positions] : result.group_matches) {
            auto [_, start_pos, end_pos] = positions;
            groups[group] = source.substr(start_pos, end_pos - start_pos);
        }
    }

    return match(source, start, result.ending_position, groups);
}

std::string match::group(int id) const
{
    auto it = groups_.find(id);
    if (it == groups_.end()) {
        throw std::out_of_range("Group ID is not found");
    }

    return it->second;
}

const std::unordered_map<int, std::string> &match::groups() const
{
    return groups_;
}
