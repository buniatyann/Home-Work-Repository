#ifndef TCP_CONNECTION_HPP
#define TCP_CONNECTION_HPP

#include "TCPState.hpp"
#include <memory>
#include <iostream>

class TcpConnection {
public:
    TcpConnection();

    void open();
    void close();
    void listen();
    void synchronize();
    void acknowledge();
    void sendFin();
    void sendAck();
    void timeout();
    void receiveFin();

    void printStatus() const;

private:
    friend class TcpState;
    std::unique_ptr<TcpState> state_;
};

#endif