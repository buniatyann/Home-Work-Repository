#ifndef ITASK_HPP
#define ITASK_HPP

#include <memory>
#include <iostream>
#include <string>
#include <cstddef>

class ITask {
public:
    virtual ~ITask() = default;
    virtual void infoAbout() const = 0;
};

#endif // ITASK_HPP