#include "include/Tasks/HardTask.hpp"
#include "include/Tasks/SimpleTask.hpp"
#include "include/Project/Project.hpp"
#include <iostream>

int main() {
    Project root("Main Project");
    root.addTask(std::make_unique<SimpleTask>("Write Documentation", 101));
    root.addTask(std::make_unique<HardTask>("Implement API", 102));

    Project subproject("Backend Development");
    subproject.addTask(std::make_unique<SimpleTask>("Database Setup", 201));
    subproject.addTask(std::make_unique<HardTask>("Authentication Module", 202));

    root.addTask(std::make_unique<Project>(std::move(subproject)));
    root.addTask(std::make_unique<SimpleTask>("Test Application", 103));
    Project second("Second project");

    std::cout << "Task Hierarchy:\n";
    root.infoAbout();

    return 0;
}