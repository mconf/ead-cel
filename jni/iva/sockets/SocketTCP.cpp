#include "SocketTCP.h"

SocketTCP::SocketTCP() throw(SocketException*)
    : Socket()
{
}

SocketTCP::SocketTCP(SOCKET so) throw(SocketException*)
    : Socket(so)
{
    int result;

    result = setkeepalive();
    if (result != E_OK) {
        throw new SocketException(result, 0, "Erro ao configurar o keepalive do socket");
    }

    result = setlinger();
    if (result != E_OK) {
        throw new SocketException(result, 0, "Erro ao configurar a espera no fechamento do socket");
    }
}

SocketTCP::~SocketTCP()
{
}

int SocketTCP::connect(const IPv4& ip, const unsigned int port)
{
    if (_connected)
        return E_SOCKET_ALREADY_CONNECTED;

    memset(&_addr.sin_zero, '\0', 8);
    _addr.sin_addr.s_addr = inet_addr(ip.getString().c_str());
    _addr.sin_family = AF_INET;
    _addr.sin_port = htons(port);

    return connect();
}

int SocketTCP::connect()
{
    if (_connected)
        return E_SOCKET_ALREADY_CONNECTED;

    int result;
    result = SocketWrapper::_connect(_socket,(struct sockaddr *) &_addr, _addrsize);
    if (result == SOCKET_ERROR) {
        _lastError = SocketWrapper::_getlasterror();
        NEW_ERROR(E_SOCKET_CONNECT, SocketWrapper::_errorMessage(_lastError));
        return E_SOCKET_CONNECT;
    }
    _connected = true;
    _server = false;
    return E_OK;
}

int SocketTCP::setkeepalive(bool enable, unsigned int timeout_msec, unsigned int interval_msec)
{
    if (SocketWrapper::_setkeepalive(_socket, enable, timeout_msec, interval_msec) != 0) {
        _lastError = SocketWrapper::_getlasterror();
        NEW_ERROR(E_SOCKET_SETSOCKOPT, SocketWrapper::_errorMessage(_lastError));
        return E_SOCKET_SETSOCKOPT;
    }
    return E_OK;
}

int SocketTCP::listen(int backlog)
{
    int result;

    result = SocketWrapper::_listen(_socket, backlog);
    if (result == SOCKET_ERROR) {
        _lastError = SocketWrapper::_getlasterror();
        NEW_ERROR(E_SOCKET_LISTEN, SocketWrapper::_errorMessage(_lastError));
        return E_SOCKET_LISTEN;
    }

    return E_OK;
}

SocketTCP* SocketTCP::accept(struct sockaddr *addr, socklen_t *addrlen)
{
    SOCKET remoteSocket;
    SocketTCP* remoteClient;

    remoteSocket = SocketWrapper::_accept(_socket, addr, addrlen);
    if (remoteSocket == INVALID_SOCKET) {
        _lastError = SocketWrapper::_getlasterror();
        NEW_ERROR(E_SOCKET_ACCEPT, SocketWrapper::_errorMessage(_lastError));
        return NULL;
    }

    // cria um objeto Socket com base no socket retornado
    try {
        remoteClient = new SocketTCP(remoteSocket);
    } catch(SocketException* e) {
        delete e;
        return NULL;
    }

    return remoteClient;
}

IPv4 SocketTCP::getRemoteIPv4Address() const
{
    IPv4 ip(COMMON_INVALID_IP);
    getRemoteIPv4Address(ip);
    return ip;
}

void SocketTCP::getRemoteIPv4Address(IPv4& ip) const
{
    sockaddr_in addr;
    socklen_t size = sizeof(addr);
    getpeername(_socket, (sockaddr*) &addr, &size);
    ip.setString(inet_ntoa(addr.sin_addr));
}

IPv4 SocketTCP::getLocalIPv4Address() const
{
    IPv4 ip(COMMON_INVALID_IP);
    getLocalIPv4Address(ip);
    return ip;
}

void SocketTCP::getLocalIPv4Address(IPv4& ip) const
{
    sockaddr_in addr;
    socklen_t size = sizeof(addr);
    getsockname(_socket, (sockaddr*) &addr, &size);
    ip.setString(inet_ntoa(addr.sin_addr));
}

int SocketTCP::openAsClient(const IPv4& ip, const unsigned int port, bool blocking, int connectTimeout)
{
    int r;

    r = open(_family, _type, _protocol);
    if (r != E_OK)
        return r;

    r = setkeepalive();
    if (r != E_OK) {
        return r;
    }

    r = setlinger();
    if (r != E_OK) {
        return r;
    }

    r = setblocking(false);
    if (r != E_OK)
        return r;

    r = connect(ip, port);
    if (blocking) {
        r = waitWrite(connectTimeout);
        if (r <= 0)
            return E_SOCKET_CONNECT;

        r = setblocking(blocking);
        if (r != E_OK)
            return r;
    }

    return r;
}

int SocketTCP::openAsServer(const unsigned int port, bool blocking)
{
    int r;

    r = open(_family, _type, _protocol);
    if (r != E_OK)
        return r;

    r = setkeepalive();
    if (r != E_OK){
        return r;
    }

    r = setlinger();
    if (r != E_OK){
        return r;
    }

    r = bind(port);
    if (r != E_OK)
        return r;

    r = listen();
    if (r != E_OK)
        return r;

    r = setblocking(blocking);
    if (r != E_OK)
        return r;

    return E_OK;
}

int SocketTCP::send(const char* buf, int len)
{
    int result;

    result = SocketWrapper::_send(_socket, buf, len, 0);
    if (result == SOCKET_ERROR) {
        _lastError = SocketWrapper::_getlasterror();
        NEW_ERROR(E_SOCKET_SEND, SocketWrapper::_errorMessage(_lastError));
    }
    return result;
}

int SocketTCP::send(const string& buf)
{
    return send(buf.c_str(), buf.size());
}

int SocketTCP::operator<<(const string& buf)
{
    return send(buf);
}

int SocketTCP::recv(char* buf, int len)
{
    int result;
    int received = 0;

    while (received < len) {
        result = SocketWrapper::_recv(_socket, buf + received, len - received, 0);
        if (result == 0) {
            _lastError = SocketWrapper::_getlasterror();
            // conexão finalizada de forma amigável
            NEW_WARNING(E_SOCKET_RECV, "Conexão finalizada de forma amigável");
            close();
            return result;
        } else if (result < 0) {
            _lastError = SocketWrapper::_getlasterror();
            //  erro na chamada do recv
            NEW_ERROR(E_SOCKET_RECV, SocketWrapper::_errorMessage(_lastError));
            return result;
        }
        received += result;
    }
    return received;
}

int SocketTCP::recv(string& buf, int len)
{
    char* temp = new char[len];
    memset(temp, '\0',len);
    int r = recv(temp, len);
    if (r > 0) {
        buf.clear();
        buf.append(string(temp, r));
    }
    delete temp;
    return r;
}
