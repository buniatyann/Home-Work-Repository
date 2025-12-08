#ifndef TIME_WAIT_STATE_HPP
#define TIME_WAIT_STATE_HPP

#include "../TCPState.hpp"

class TimeWaitState : public TcpState {
public:
    static TcpState& instance();
    void timeout(TcpConnection&) override;
    std::string name() const override { return "TIME_WAIT"; }
    
private:
    TimeWaitState() = default;
};

#endif