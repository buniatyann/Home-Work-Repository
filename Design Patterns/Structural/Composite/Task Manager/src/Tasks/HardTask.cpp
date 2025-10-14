#include "../../include/Tasks/HardTask.hpp"

HardTask::HardTask(const std::string& name, std::size_t id) : name_(name), id_(id) {}

void HardTask::infoAbout() const {
    std::cout << "Hard Task:\n  Name: " << name_ << "\n  Id: " << id_ << "\n";
}