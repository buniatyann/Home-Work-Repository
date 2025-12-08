#include "../include/states/LastAckState.hpp"
#include "../include/TCPConnection.hpp"
#include "../include/states/ClosedState.hpp"

TcpState& LastAckState::instance() {
    static LastAckState singleton;
    return singleton;
}

void LastAckState::acknowledge(TcpConnection& conn) {
    std::cout << "ACK received → connection fully closed\n";
    changeState(conn, std::make_unique<ClosedState>());
}