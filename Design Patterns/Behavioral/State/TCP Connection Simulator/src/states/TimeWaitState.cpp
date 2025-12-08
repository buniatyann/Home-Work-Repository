#include "../include/states/TimeWaitState.hpp"
#include "../include/TCPConnection.hpp"
#include "../include/states/ClosedState.hpp"

TcpState& TimeWaitState::instance() {
    static TimeWaitState singleton;
    return singleton;
}

void TimeWaitState::timeout(TcpConnection& conn) {
    std::cout << "2MSL timeout passed → connection CLOSED\n";
    changeState(conn, std::make_unique<ClosedState>());
}