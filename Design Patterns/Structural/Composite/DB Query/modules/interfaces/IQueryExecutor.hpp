#ifndef IQUERYEXECUTOR_HPP
#define IQUERYEXECUTOR_HPP

#include "Result.hpp"
#include <memory>
#include <vector>
#include <map>
#include <string>

class IQuery;
class ExecutionContext;

class IQueryExecutor {
public:
    virtual ~IQueryExecutor() = default;
    virtual Result<std::vector<std::map<std::string, std::string>>> 
        execute(const IQuery& query, ExecutionContext& ctx) = 0;
};

#endif // IQUERYEXECUTOR_HPP