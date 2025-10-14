#ifndef SIMPLE_TASK_HPP
#define SIMPLE_TASK_HPP

#include "../Interface/ITask.hpp"


class SimpleTask : public ITask {
public:
    SimpleTask(const std::string& name, std::size_t id);
    void infoAbout() const override;

private:
    std::string name_;
    std::size_t id_;
};

#endif // SIMPLE_TASK_HPP