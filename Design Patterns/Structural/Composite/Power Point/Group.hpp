#ifndef GROUP_HPP
#define GROUP_HPP

#include "IGraphObject.hpp"
#include <vector>
#include <string>

class Group : public IGraphObject {
public:
    Group(const std::string& name) : name_(name) {}

    void draw() const override {
        for (const auto& vec : vec_) {
            vec->draw();
        }
    }
    
    void addObject(std::unique_ptr<IGraphObject>&& obj) {
        if (obj) {
            vec_.push_back(std::move(obj));
        }
    }

private:
    std::string name_;
    std::vector<std::unique_ptr<IGraphObject>> vec_;
};

#endif // GROUP_HPP