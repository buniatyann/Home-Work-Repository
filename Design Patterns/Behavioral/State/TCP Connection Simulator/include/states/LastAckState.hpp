#ifndef LAST_ACK_STATE_HPP
#define LAST_ACK_STATE_HPP

#include "../TCPState.hpp"

class LastAckState : public TcpState {
public:
    static TcpState& instance();
    void acknowledge(TcpConnection&) override;
    std::string name() const override { return "LAST_ACK"; }
    
private:
    LastAckState() = default;
};

#endif