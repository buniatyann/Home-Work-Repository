#include "ConfigManager.hpp"

std::shared_ptr<ConfigManager> ConfigManager::instance_ = nullptr;
std::mutex ConfigManager::mtx_;

std::shared_ptr<ConfigManager> ConfigManager::getInstance() {
    std::lock_guard<std::mutex> lock(mtx_);
    if (!instance_) {
        instance_ = std::make_shared<ConfigManager>();
    }

    return instance_;
}

void ConfigManager::setConfig(const std::string& key, const std::string& value) {
    std::lock_guard<std::mutex> lock(mtx_);
    configs_[key] = value;
}

std::string ConfigManager::getConfig(const std::string& key) {
    std::lock_guard<std::mutex> lock(mtx_);
    if (configs_.find(key) != configs_.end()) {
        return configs_[key];
    }
    
    return "";
}

ConfigManager::ConfigManager() {}

ConfigManager::~ConfigManager() {}
