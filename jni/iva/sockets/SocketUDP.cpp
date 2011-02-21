#include "SocketUDP.h"

SocketUDP::SocketUDP() throw(SocketException*)
    : Socket()
    , _ip(127,0,0,1)
    , _igmpSender()
    , _leaveGroup(false)
{
    memset(_recvbuf, '\0', MAX_UDP_MESSAGE_SIZE);
}

SocketUDP::~SocketUDP()
{
}

int SocketUDP::openAsSender(const string& ip, int port, bool blocking)
{
    int r;

    _leaveGroup = false;

    r = _ip.setString(ip);
    if (r != E_OK)
        return r;

    r = open(_family, _type, _protocol);
    if (r != E_OK)
        return r;

    memset(&_addr.sin_zero, '\0', 8);
    _addr.sin_family = AF_INET;
    _addr.sin_addr.s_addr = inet_addr(ip.c_str());
    _addr.sin_port = htons(port);

    if (_ip.getType() == IPv4::TYPE_MULTICAST) {

        r = setTtl(DEFAULT_MULTICAST_TTL);
        if (r != E_OK)
            return r;

        r = setLoop(DEFAULT_LOOPBACK);
        if (r != E_OK)
            return r;

/*
        // seta valores default para TTL e LOOP
        if (setsockopt(IPPROTO_IP, IP_MULTICAST_TTL, (char *)&ttl, sizeof(ttl)) < 0) {
            throw 1;
        }
        if (setsockopt(IPPROTO_IP, IP_MULTICAST_LOOP, (char *)&loop, sizeof(loop)) < 0) {
            throw 1;
        }

        // permite envio dos pacotes de qualquer interface
        _mreq.imr_interface.s_addr = htonl(INADDR_ANY);
        if (setsockopt(IPPROTO_IP, IP_MULTICAST_IF, (char *)&_mreq.imr_interface,
            sizeof(struct ip_mreq)) < 0) {
            throw 1;
        }
*/            
    } else {
        r = setTtl(DEFAULT_UNICAST_TTL);
        if (r != E_OK)
            return r;
    }

    r = setblocking(blocking);
    if (r != E_OK)
        return r;

    return E_OK;
}

int SocketUDP::openAsReceiver(const string& ip, int port, bool blocking)
{
    int r;

    _leaveGroup = false;

    r = _ip.setString(ip);
    if (r != E_OK)
        return r;

    r = open(_family, _type, _protocol);
    if (r != E_OK)
        return r;

    r = bind(port);
    if (r != E_OK)
        return r;

    if (_ip.getType() == IPv4::TYPE_MULTICAST) {
        r = joinGroup(_ip);
        if (r != E_OK)
            return r;
        _igmpSender.start(_ip);
        _leaveGroup = true;
    }

    r = setblocking(blocking);
    if (r != E_OK)
        return r;

    return E_OK;
}

int SocketUDP::openAsReceiver(int port, bool blocking)
{
    int r;

    _leaveGroup = false;

    r = _ip.setString("127.0.0.1");
    if (r != E_OK)
        return r;

    r = open(_family, _type, _protocol);
    if (r != E_OK)
        return r;

    r = bind(port);
    if (r != E_OK)
        return r;

    r = setblocking(blocking);
    if (r != E_OK)
        return r;

    return E_OK;
}

int SocketUDP::close()
{
    int r;
    
    if (_ip.getType() == IPv4::TYPE_MULTICAST && _leaveGroup) {
        _igmpSender.pause();

        r = leaveGroup();
        if (r != E_OK)
            return r;
    }
    
    return Socket::close();
}

int SocketUDP::joinGroup(const IPv4& ip)
{
    _mreq.imr_multiaddr.s_addr = inet_addr(_ip.getString().c_str());
    _mreq.imr_interface.s_addr = htonl(INADDR_ANY);

    int r;

    r = SocketWrapper::_addmembership(_socket,&_mreq);
    if (r != 0) {
        _lastError = SocketWrapper::_getlasterror();
        NEW_ERROR(E_SOCKET_SETSOCKOPT, SocketWrapper::_errorMessage(_lastError));
    }
    return r;
}

int SocketUDP::leaveGroup()
{
    int r;

    r = SocketWrapper::_dropmembership(_socket,&_mreq);
    if (r != 0) {
        _lastError = SocketWrapper::_getlasterror();
        NEW_ERROR(E_SOCKET_SETSOCKOPT, SocketWrapper::_errorMessage(_lastError));
    }
    return r;
}

int SocketUDP::send(const char* buf, int len)
{
    int r;

    r = SocketWrapper::_sendto(_socket, buf, len, 0, (struct sockaddr*) &_addr, _addrsize);
    if (r == SOCKET_ERROR) {
        _lastError = SocketWrapper::_getlasterror();
        NEW_ERROR(E_SOCKET_SEND, SocketWrapper::_errorMessage(_lastError));
    }
    return r;
}

int SocketUDP::send(const string& buf)
{
    return send(buf.c_str(), buf.size());
}

int SocketUDP::operator<<(const string& buf)
{
    return send(buf);
}

int SocketUDP::recv(char* buf, int len)
{
    int result;

    result = SocketWrapper::_recvfrom(_socket, buf, len);
    if (result == 0) {
        _lastError = SocketWrapper::_getlasterror();
        // conexo finalizada de forma amigável
        NEW_WARNING(E_SOCKET_RECV, SocketWrapper::_errorMessage(_lastError));
    } else if (result < 0) {
        _lastError = SocketWrapper::_getlasterror();
        NEW_ERROR(E_SOCKET_RECV, SocketWrapper::_errorMessage(_lastError));
    }
    return result;
}

int SocketUDP::recv(string& buf, int len)
{
    int r = recv(_recvbuf, len);
    if (r > 0) {
        buf.clear();
        buf.append(_recvbuf);
        memset(_recvbuf, '\0', r);
    }
    return r;
}

int SocketUDP::operator>>(string& buf)
{
    return recv(buf);
}
