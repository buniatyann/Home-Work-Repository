#ifndef CONFIG_MANAGER_HPP
#define CONFIG_MANAGER_HPP

#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <mutex>

class ConfigManager {
public:
    static std::shared_ptr<ConfigManager> getInstance();
    void setConfig(const std::string& key, const std::string& value);
    std::string getConfig(const std::string& key);

private:
    ConfigManager();
    ~ConfigManager();
    std::unordered_map<std::string, std::string> configs_;
    static std::shared_ptr<ConfigManager> instance_;
    static std::mutex mtx_;
};

#endif // CONFIG_MANAGER_HPP
