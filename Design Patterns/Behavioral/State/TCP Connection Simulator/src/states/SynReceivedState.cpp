#include "../include/states/SynReceivedState.hpp"
#include "../include/TCPConnection.hpp"
#include "../include/states/EstablishedState.hpp"

TcpState& SynReceivedState::instance() {
    static SynReceivedState singleton;
    return singleton;
}

void SynReceivedState::acknowledge(TcpConnection& conn) {
    std::cout << "ACK received → connection ESTABLISHED\n";
    changeState(conn, std::make_unique<EstablishedState>());
}