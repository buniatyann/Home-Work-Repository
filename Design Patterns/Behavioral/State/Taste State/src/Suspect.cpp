#include "../include/Suspect.hpp"

Suspect::Suspect(std::unique_ptr<IHumorTaste> taste) : taste_(std::move(taste)) {}

void Suspect::giveControlQuestion() {
    std::cout << "Do you know who is Ando?\n" << "If yes, print 1; otherwise, print 2: ";
    int i;
    std::cin >> i;

    if (i == 1) {
        switchState(std::make_unique<WithTaste>());
    } 
    else {
        switchState(std::make_unique<WithoutTaste>());
    }
}

void Suspect::giveBlame() {
    if (!taste_->knowsKargin()) {
        std::cout << "You have no taste!!!!!!!!" << std::endl;
    } 
    else {
        std::cout << "You have my respect, aziz!" << std::endl;
    }
}

void Suspect::giveInfoAbout() const {
    if (!taste_->knowsKargin()) {
        std::cout << "Es vichaky indzi kazmaqandum a" << std::endl;
    } 
    else {
        std::cout << "Respect this man!" << std::endl;
    }
}

void Suspect::switchState(std::unique_ptr<IHumorTaste> taste) {
    taste_ = std::move(taste);
}
