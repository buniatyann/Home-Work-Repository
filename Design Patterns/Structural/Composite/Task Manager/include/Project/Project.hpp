#ifndef PROJECT_HPP
#define PROJECT_HPP

#include "../Interface/ITask.hpp"
#include <vector>

class Project : public ITask {
public:
    Project(const std::string& name);
    void infoAbout() const override;
    void addTask(std::unique_ptr<ITask>&& task);

private:
    std::string name_;
    std::vector<std::unique_ptr<ITask>> tasks_;
};

#endif // PROJECT_HPP