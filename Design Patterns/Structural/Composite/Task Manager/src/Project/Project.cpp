#include "../../include/Project/Project.hpp"

Project::Project(const std::string& name) : name_(name) {}

void Project::infoAbout() const {
    std::cout << "Project: " << name_ << "\n";
    for (const auto& task : tasks_) {
        std::cout << "  "; 
        task->infoAbout();
    }
}

void Project::addTask(std::unique_ptr<ITask>&& task) {
    if (task) {
        tasks_.push_back(std::move(task));
    }
}