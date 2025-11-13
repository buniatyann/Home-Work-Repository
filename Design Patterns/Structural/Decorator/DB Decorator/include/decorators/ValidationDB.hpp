#ifndef VALIDATIONDB_HPP
#define VALIDATIONDB_HPP

#include "../interface/DatabaseDecorator.hpp"
#include <vector>

class ValidationDB : public DatabaseDecorator {
public:
    explicit ValidationDB(IDataBase::Ptr db);
    std::string execute(const std::string& q,
                        const std::unordered_map<std::string, std::string>& p) override;
private:
    bool safe(const std::string& q) const;
    const std::vector<std::string> forbidden_ = {"DROP", "DELETE", "TRUNCATE", "ALTER", ";--"};
};

#endif // VALIDATIONDB_HPP