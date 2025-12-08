#include "../include/states/EstablishedState.hpp"
#include "../include/TCPConnection.hpp"
#include "../include/states/FinWait1State.hpp"
#include "../include/states/CloseWaitState.hpp"

TcpState& EstablishedState::instance() {
    static EstablishedState singleton;
    return singleton;
}

void EstablishedState::close(TcpConnection& conn) {
    std::cout << "Sending FIN → initiating close\n";
    changeState(conn, std::make_unique<FinWait1State>());
}

void EstablishedState::receiveFin(TcpConnection& conn) {
    std::cout << "Received FIN → sending ACK\n";
    changeState(conn, std::make_unique<CloseWaitState>());
}