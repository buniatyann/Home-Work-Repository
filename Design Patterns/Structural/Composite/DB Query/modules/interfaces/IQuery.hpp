#ifndef IQUERY_HPP
#define IQUERY_HPP

#include <memory>

class IQueryVisitor;

class IQuery {
public:
    virtual ~IQuery() = default;
    virtual void accept(IQueryVisitor& visitor) = 0;
    virtual std::unique_ptr<IQuery> clone() const = 0;
    virtual bool equals(const IQuery& other) const = 0;
};

#endif // IQUERY_HPP