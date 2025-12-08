#include "../include/states/CloseWaitState.hpp"
#include "../include/TCPConnection.hpp"
#include "../include/states/LastAckState.hpp"

TcpState& CloseWaitState::instance() {
    static CloseWaitState singleton;
    return singleton;
}

void CloseWaitState::close(TcpConnection& conn) {
    std::cout << "Application closed → sending FIN\n";
    changeState(conn, std::make_unique<LastAckState>());
}