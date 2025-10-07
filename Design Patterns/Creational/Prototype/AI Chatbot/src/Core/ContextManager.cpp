#include "../../include/Core/ContextManager.h"

void ContextManager::setContext(const std::string& key, const std::string& value) {
	contexts_[key] = value;
}

std::string ContextManager::getContext(const std::string& key) const {
	if (contexts_.find(key) == contexts_.end()) {
		throw std::runtime_error("getContext: you're trying to access the key that doesn't exist");
	}

	return contexts_[key];
}