#include "../../include/Tasks/SimpleTask.hpp"

SimpleTask::SimpleTask(const std::string& name, std::size_t id) : name_(name), id_(id) {}

void SimpleTask::infoAbout() const {
    std::cout << "Simple Task:\n  Name: " << name_ << "\n  Id: " << id_ << "\n";
}