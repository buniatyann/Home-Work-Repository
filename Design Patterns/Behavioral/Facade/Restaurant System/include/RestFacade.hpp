#ifndef REST_FACADE_HPP
#define REST_FACADE_HPP

#include "KitchenSubsystem.hpp"
#include "WaiterSubsystem.hpp"
#include <memory>


class RestFacade {
public:
    RestFacade();
    void orderFood(const std::string& name);
    void receiveBadReview();

private:
    std::unique_ptr<KitchenSubsystem> kitchen_;
    std::unique_ptr<WaiterSubsystem> waiter_;
};

#endif // REST_FACADE_HPP