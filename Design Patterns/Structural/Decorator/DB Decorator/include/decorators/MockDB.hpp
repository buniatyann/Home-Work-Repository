#ifndef MOCKDB_HPP
#define MOCKDB_HPP

#include "../interface/IDataBase.hpp"

class MockDB : public IDataBase {
public:
    std::string execute(const std::string& query,
                        const std::unordered_map<std::string, std::string>& params) override;
};

#endif // MOCKDB_HPP