#ifndef REGEX_MATCH_HPP
#define REGEX_MATCH_HPP

#include <string>
#include <unordered_map>
#include <stdexcept>

struct nfa_result;

class match {
public:
    // using std::unordered_map<int, std::string> = ??

    match(const std::string& source, std::size_t start, std::size_t end, const std::unordered_map<int, std::string>& groups);
    static match from_nfa_result(const std::string& source, std::size_t start, const nfa_result& result);
    std::string group(int id) const;
    const std::unordered_map<int, std::string>& groups() const;
    std::size_t start() const {
        return start_;
    }

    std::size_t end() const {
        return end_;
    }

private:
    std::string source_;
    std::size_t start_;
    std::size_t end_;
    std::unordered_map<int, std::string> groups_;
};

#endif // REGEX_MATCH_HPP