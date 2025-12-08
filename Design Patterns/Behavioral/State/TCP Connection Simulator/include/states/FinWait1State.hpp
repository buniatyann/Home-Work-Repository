#ifndef FIN_WAIT_1_STATE_HPP
#define FIN_WAIT_1_STATE_HPP

#include "../TCPState.hpp"

class FinWait1State : public TcpState {
public:
    static TcpState& instance();
    void acknowledge(TcpConnection&) override;
    void receiveFin(TcpConnection&) override;
    std::string name() const override { return "FIN_WAIT_1"; }
    
private:
    FinWait1State() = default;
};

#endif