#include "../include/decorators/AuditingDB.hpp"
#include "../include/settings/Settings.hpp"
#include <fstream>
#include <chrono>

AuditingDB::AuditingDB(IDataBase::Ptr db) : DatabaseDecorator(std::move(db)) {}

void AuditingDB::writeAudit(const std::string& q,
                            const std::unordered_map<std::string, std::string>& p) {
    std::ofstream f(settings::AUDIT_FILE, std::ios::app);
    if (f) {
        auto t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        f << "[AUDIT] " << std::ctime(&t) << "QUERY: " << q << "  PARAMS: ";
        for (const auto& kv : p) {
            f << kv.first << "=" << kv.second << " ";
        }
        
        f << "\n";
    }
}

std::string AuditingDB::execute(const std::string& q,
                                const std::unordered_map<std::string, std::string>& p) {
    writeAudit(q, p);
    return DatabaseDecorator::execute(q, p);
}