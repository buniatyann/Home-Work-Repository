#ifndef HARD_TASK_HPP
#define HARD_TASK_HPP

#include "../Interface/ITask.hpp"

class HardTask : public ITask {
public:
    HardTask(const std::string& name, std::size_t id);
    void infoAbout() const override;

private:
    std::string name_;
    std::size_t id_;
};

#endif // HARD_TASK_HPP