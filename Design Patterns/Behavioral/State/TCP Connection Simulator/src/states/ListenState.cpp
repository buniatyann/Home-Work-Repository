#include "../include/states/ListenState.hpp"
#include "../include/TCPConnection.hpp"
#include "../include/states/SynReceivedState.hpp"

TcpState& ListenState::instance() {
    static ListenState singleton;
    return singleton;
}

void ListenState::synchronize(TcpConnection& conn) {
    std::cout << "SYN received → sending SYN-ACK\n";
    changeState(conn, std::make_unique<SynReceivedState>());
}