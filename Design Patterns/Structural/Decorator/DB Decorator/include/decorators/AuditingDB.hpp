#ifndef AUDITINGDB_HPP
#define AUDITINGDB_HPP

#include "../interface/DatabaseDecorator.hpp"

class AuditingDB : public DatabaseDecorator {
public:
    explicit AuditingDB(IDataBase::Ptr db);
    std::string execute(const std::string& q,
                        const std::unordered_map<std::string, std::string>& p) override;
private:
    void writeAudit(const std::string& q,
                    const std::unordered_map<std::string, std::string>& p);
};

#endif // AUDITINGDB_HPP