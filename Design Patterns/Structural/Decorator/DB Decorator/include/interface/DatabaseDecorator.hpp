#ifndef DATABASE_DECORATOR_HPP
#define DATABASE_DECORATOR_HPP

#include "IDataBase.hpp"

class DatabaseDecorator : public IDataBase {
public:
    explicit DatabaseDecorator(IDataBase::Ptr component)
        : component_(std::move(component)) {}

    std::string execute(const std::string& q,
                        const std::unordered_map<std::string, std::string>& p) override                     
    {
        return component_->execute(q, p);
    }

protected:
    IDataBase::Ptr component_;
};

#endif // DATABASE_DECORATOR_HPP