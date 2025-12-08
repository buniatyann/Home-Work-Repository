#ifndef FIN_WAIT_2_STATE_HPP
#define FIN_WAIT_2_STATE_HPP

#include "../TCPState.hpp"

class FinWait2State : public TcpState {
public:
    static TcpState& instance();
    void receiveFin(TcpConnection&) override;
    std::string name() const override { return "FIN_WAIT_2"; }
    
private:
    FinWait2State() = default;
};

#endif