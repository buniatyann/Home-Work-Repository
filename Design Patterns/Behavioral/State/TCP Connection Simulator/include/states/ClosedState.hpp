#ifndef CLOSED_STATE_HPP
#define CLOSED_STATE_HPP

#include "../TCPState.hpp"

class ClosedState : public TcpState {
public:
    static TcpState& instance();
    void open(TcpConnection&) override;
    void listen(TcpConnection&) override;
    std::string name() const override { return "CLOSED"; }

private:
    ClosedState() = default;
};

#endif