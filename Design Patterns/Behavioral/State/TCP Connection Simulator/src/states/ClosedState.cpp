#include "../include/states/ClosedState.hpp"
#include "../include/TCPConnection.hpp"
#include "../include/states/SynSentState.hpp"
#include "../include/states/ListenState.hpp"

TcpState& ClosedState::instance() {
    static ClosedState singleton;
    return singleton;
}

void ClosedState::open(TcpConnection& conn) {
    std::cout << "Active OPEN → sending SYN\n";
    changeState(conn, std::make_unique<SynSentState>());
}

void ClosedState::listen(TcpConnection& conn) {
    std::cout << "Passive OPEN → listening\n";
    changeState(conn, std::make_unique<ListenState>());
}