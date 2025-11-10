#ifndef IQUERYVISITOR_HPP
#define IQUERYVISITOR_HPP

class AtomicQuery;
class CompositeQuery;

class IQueryVisitor {
public:
    virtual ~IQueryVisitor() = default;
    virtual void visit(const AtomicQuery& query) = 0;
    virtual void visit(const CompositeQuery& query) = 0;
};

#endif // IQUERYVISITOR_HPP