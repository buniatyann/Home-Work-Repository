#ifndef SUSPECT_HPP
#define SUSPECT_HPP

#include "WithoutTaste.hpp"
#include "WithTaste.hpp"
#include <iostream>
#include <memory>

class Suspect {
public:
    Suspect(std::unique_ptr<IHumorTaste> taste);
    void giveControlQuestion();
    void giveBlame();
    void giveInfoAbout() const;

private:
    std::unique_ptr<IHumorTaste> taste_;
    void switchState(std::unique_ptr<IHumorTaste> taste);
};

#endif // SUSPECT_HPP
