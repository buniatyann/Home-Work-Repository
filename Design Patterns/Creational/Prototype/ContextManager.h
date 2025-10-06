#ifndef CONTEXTMANAGER_H
#define CONTEXTMANAGER_H

#include <string>
#include <unordered_map>
#include <stdexcept>

class ContextManager {
public:
	void setContext(const std::string& key, const std::string& value);
	std::string getContext(const std::string& key) const;

private:
	std::unordered_map<std::string, std::string> contexts_;
};


#endif // CONTEXTMANAGER_H