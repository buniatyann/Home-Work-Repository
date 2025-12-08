#include "../include/states/FinWait1State.hpp"
#include "../include/TCPConnection.hpp"
#include "../include/states/FinWait2State.hpp"
#include "../include/states/ClosingState.hpp"

TcpState& FinWait1State::instance() {
    static FinWait1State singleton;
    return singleton;
}

void FinWait1State::acknowledge(TcpConnection& conn) {
    std::cout << "ACK received for our FIN → FIN_WAIT_2\n";
    changeState(conn, std::make_unique<FinWait2State>());
}

void FinWait1State::receiveFin(TcpConnection& conn) {
    std::cout << "Simultaneous close → sending ACK → CLOSING\n";
    changeState(conn, std::make_unique<ClosingState>());
}