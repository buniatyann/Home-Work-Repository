#include "../include/TCPConnection.hpp"
#include "../include/states/ClosedState.hpp"

TcpConnection::TcpConnection() : state_(std::make_unique<ClosedState>()) {
    std::cout << "[TCP] New connection created → CLOSED\n";
}

void TcpConnection::printStatus() const {
    std::cout << "[TCP] Current state: " << state_->name() << "\n";
}

#define FWD(name) void TcpConnection::name() { state_->name(*this); }
FWD(open)
FWD(close)
FWD(listen)
FWD(synchronize)
FWD(acknowledge)
FWD(sendFin)
FWD(sendAck)
FWD(receiveFin)
FWD(timeout)