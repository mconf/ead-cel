#include "SocketRaw.h"

SocketRaw::SocketRaw(int protocol)
    : Socket()
    , _protocol(protocol)
{
}

SocketRaw::~SocketRaw(void)
{
}

int SocketRaw::openAsSender(const IPv4& ip, bool blocking)
{
    int r;

    r = open(_family, _type, _protocol);
    if (r != E_OK)
        return r;

    memset(&_addr.sin_zero, '\0', 8);
    _addr.sin_family = AF_INET;
    _addr.sin_addr.s_addr = inet_addr(ip.getString().c_str());

    r = setLoop(false);
    if (r != E_OK)
        return r;

    r = setTtl(1);
    if (r != E_OK)
        return r;

    r = setblocking(blocking);
    if (r != E_OK)
        return r;

    return r;
}

int SocketRaw::send(const char* buf, int len)
{
    int r;

    r = SocketWrapper::_sendto(_socket, buf, len, 0, (struct sockaddr*) &_addr, _addrsize);
    if (r == SOCKET_ERROR) {
        _lastError = SocketWrapper::_getlasterror();
        NEW_ERROR(E_SOCKET_SEND, SocketWrapper::_errorMessage(_lastError));
    }
    return r;
}

int SocketRaw::send(const string& buf)
{
    return send(buf.c_str(), buf.size());
}

int SocketRaw::operator<<(const string& buf)
{
    return send(buf);
}