#ifndef ESTABLISHED_STATE_HPP
#define ESTABLISHED_STATE_HPP

#include "../TCPState.hpp"

class EstablishedState : public TcpState {
public:
    static TcpState& instance();
    void close(TcpConnection&) override;
    void receiveFin(TcpConnection&) override;
    std::string name() const override { return "ESTABLISHED"; }
    
private:
    EstablishedState() = default;
};

#endif