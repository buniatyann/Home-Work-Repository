#ifndef IQUERYVALIDATOR_HPP
#define IQUERYVALIDATOR_HPP

#include "ValidationResult.hpp"
#include <memory>

class IQuery;

class IQueryValidator {
public:
    virtual ~IQueryValidator() = default;
    virtual ValidationResult validate(const IQuery& query) const = 0;
};

#endif // IQUERYVALIDATOR_HPP