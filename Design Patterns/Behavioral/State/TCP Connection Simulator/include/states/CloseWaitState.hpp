#ifndef CLOSE_WAIT_STATE_HPP
#define CLOSE_WAIT_STATE_HPP

#include "../TCPState.hpp"

class CloseWaitState : public TcpState {
public:
    static TcpState& instance();
    void close(TcpConnection&) override;
    std::string name() const override { return "CLOSE_WAIT"; }
    
private:
    CloseWaitState() = default;
};

#endif