#ifndef SYN_SENT_STATE_HPP
#define SYN_SENT_STATE_HPP

#include "../TCPState.hpp"

class SynSentState : public TcpState {
public:
    static TcpState& instance();
    void acknowledge(TcpConnection&) override;
    std::string name() const override { return "SYN_SENT"; }
    
private:
    SynSentState() = default;
};

#endif