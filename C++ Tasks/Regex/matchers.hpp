#ifndef REGEX_MATCHERS_H
#define REGEX_MATCHERS_H

#include <string>
#include <functional>

class matcher {
public:
    virtual ~matcher() = default;
    virtual bool matches(const std::string& char_, size_t i) const = 0;
    virtual std::string label() const = 0;
};

class character_matcher : public matcher {
public:
    explicit character_matcher(const std::string& c);
    bool matches(const std::string& char_, size_t i) const override;
    std::string label() const override;

private:
    std::string c_;
};

class start_of_input_matcher : public matcher {
public:
    bool matches(const std::string& char_, size_t i) const override;
    std::string label() const override;
};

class end_of_input_matcher : public matcher {
public:
    bool matches(const std::string& char_, size_t i) const override;
    std::string label() const override;
};

class dot_matcher : public matcher {
public:
    bool matches(const std::string& char_, size_t i) const override;
    std::string label() const override;
};

class negated_matcher : public matcher {
public:
    negated_matcher(std::function<bool(const std::string&)> lambda, const std::string& name);
    bool matches(const std::string& char_, size_t i) const override;
    std::string label() const override;

private:
    std::function<bool(const std::string&)> lambda_;
    std::string name_;
};

class positive_matcher : public matcher {
public:
    positive_matcher(std::function<bool(const std::string&)> lambda, const std::string& name);
    bool matches(const std::string& char_, size_t i) const override;
    std::string label() const override;

private:
    std::function<bool(const std::string&)> lambda_;
    std::string name_;
};

#endif // REGEX_MATCHERS_H