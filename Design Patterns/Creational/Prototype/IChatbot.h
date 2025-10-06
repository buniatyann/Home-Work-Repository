#include <memory>
#include <string>
#include "ContextManager.h"

class IChatbot {
public:
    virtual ~IChatbot() = default;
    virtual std::unique_ptr<IChatbot> clone() const = 0;
    virtual std::string respond(const std::string& request) = 0;
    void setContext(const std::string& key, const std::string& value);
    std::string getContext(const std::string& key) const;

protected:
    std::string bot_name_;
    std::string greeting_;
    ContextManager manager_;
};