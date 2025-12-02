#ifndef WITHOUT_TASTE_HPP
#define WITHOUT_TASTE_HPP

#include "IState.hpp"

class WithoutTaste : public IHumorTaste {
public:
    ~WithoutTaste() override = default;
    bool knowsKargin() override;
    // void switchState() override;
};

#endif // WITHOUT_TASTE_HPP