#ifndef I_STATE_HPP
#define I_STATE_HPP

class IHumorTaste {
public:
    virtual ~IHumorTaste() = default;
    virtual bool knowsKargin() = 0;
    // virtual void switchState() = 0;
};


#endif // I_STATE_HPP