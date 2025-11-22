#ifndef PARSE_RESULT_HPP
#define PARSE_RESULT_HPP

#include <string>
#include <any>

struct ParseResult {
    
    static ParseResult ok(const std::string& fmt, std::any d = std::any()) {
        ParseResult r;
        r.success = true;
        r.format = fmt;
        r.data = std::move(d);

        return r;
    }
    
    static ParseResult fail(const std::string& err) {
        ParseResult r;
        r.success = false;
        r.error = err;

        return r;
    }

    std::string format;
    std::any data;
    std::string error;
    bool success = false;
};

#endif // PARSE_RESULT_HPP