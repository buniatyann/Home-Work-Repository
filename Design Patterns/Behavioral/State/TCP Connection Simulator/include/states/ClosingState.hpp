#ifndef CLOSING_STATE_HPP
#define CLOSING_STATE_HPP

#include "../TCPState.hpp"

class ClosingState : public TcpState {
public:
    static TcpState& instance();
    void acknowledge(TcpConnection&) override;
    std::string name() const override { return "CLOSING"; }
    
private:
    ClosingState() = default;
};

#endif