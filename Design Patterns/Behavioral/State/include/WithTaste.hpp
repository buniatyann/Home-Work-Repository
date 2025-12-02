#ifndef WITH_TASTE_HPP
#define WITH_TASTE_HPP

#include "IState.hpp"

class WithoutTaste;

class WithTaste : public IHumorTaste {
public:
    ~WithTaste() override = default;
    bool knowsKargin() override;
    // void switchState() override;
};

#endif // WITH_TASTE_HPP