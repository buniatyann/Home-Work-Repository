#ifndef SYN_RECEIVED_STATE_HPP
#define SYN_RECEIVED_STATE_HPP

#include "../TCPState.hpp"

class SynReceivedState : public TcpState {
public:
    static TcpState& instance();
    void acknowledge(TcpConnection&) override;
    std::string name() const override { return "SYN_RCVD"; }
    
private:
    SynReceivedState() = default;
};

#endif