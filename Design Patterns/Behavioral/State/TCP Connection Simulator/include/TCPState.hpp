#ifndef TCP_STATE_HPP
#define TCP_STATE_HPP

#include <string>
#include <memory>

class TcpConnection;

class TcpState {
public:
    virtual ~TcpState() = default;

    virtual void open(TcpConnection&)        { notAllowed("open"); }
    virtual void close(TcpConnection&)       { notAllowed("close"); }
    virtual void listen(TcpConnection&)      { notAllowed("listen"); }
    virtual void synchronize(TcpConnection&) { notAllowed("synchronize"); }
    virtual void acknowledge(TcpConnection&) { notAllowed("acknowledge"); }
    virtual void sendFin(TcpConnection&)     { notAllowed("send FIN"); }
    virtual void sendAck(TcpConnection&)     { notAllowed("send ACK"); }
    virtual void timeout(TcpConnection&)     { notAllowed("timeout"); }
    virtual void receiveFin(TcpConnection&) {notAllowed("receive Fin");}

    virtual std::string name() const = 0;

protected:
    void changeState(TcpConnection&, std::unique_ptr<TcpState>);
    void notAllowed(const std::string& action) const;
};

#endif