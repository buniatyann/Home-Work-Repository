#include "../include/states/ClosingState.hpp"
#include "../include/TCPConnection.hpp"
#include "../include/states/TimeWaitState.hpp"

TcpState& ClosingState::instance() {
    static ClosingState singleton;
    return singleton;
}

void ClosingState::acknowledge(TcpConnection& conn) {
    std::cout << "ACK received → TIME_WAIT\n";
    changeState(conn, std::make_unique<TimeWaitState>());
}