#include "../include/states/SynSentState.hpp"
#include "../include/TCPConnection.hpp"
#include "../include/states/EstablishedState.hpp"

TcpState& SynSentState::instance() {
    static SynSentState singleton;
    return singleton;
}

void SynSentState::acknowledge(TcpConnection& conn) {
    std::cout << "SYN-ACK received → sending ACK\n";
    changeState(conn, std::make_unique<EstablishedState>());
}