#include "../include/states/FinWait2State.hpp"
#include "../include/TCPConnection.hpp"
#include "../include/states/TimeWaitState.hpp"

TcpState& FinWait2State::instance() {
    static FinWait2State singleton;
    return singleton;
}

void FinWait2State::receiveFin(TcpConnection& conn) {
    std::cout << "FIN received → sending ACK → TIME_WAIT\n";
    changeState(conn, std::make_unique<TimeWaitState>());
}