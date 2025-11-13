#ifndef INTERFACE_IDATABASE_HPP
#define INTERFACE_IDATABASE_HPP

#include <memory>
#include <string>
#include <unordered_map>

class IDataBase {
public:
    using Ptr = std::unique_ptr<IDataBase>;

    virtual ~IDataBase() = default;

    virtual std::string execute(
        const std::string& query,
        const std::unordered_map<std::string, std::string>& params = {}
    ) = 0;
};

#endif // INTERFACE_IDATABASE_HPP