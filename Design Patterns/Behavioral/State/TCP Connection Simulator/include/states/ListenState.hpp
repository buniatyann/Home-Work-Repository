#ifndef LISTTEN_STATE_HPP
#define LISTEN_STATE_HPP

#include "../TCPState.hpp"

class ListenState : public TcpState {
public:
    static TcpState& instance();
    void synchronize(TcpConnection&) override;
    std::string name() const override { return "LISTEN"; }
private:
    ListenState() = default;
};

#endif // LISTEN_STATE_HPP