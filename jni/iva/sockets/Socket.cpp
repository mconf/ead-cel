#include "Socket.h"

Socket::Socket(SOCKET s) throw(SocketException*)
    : _lastError(0)
    , _socket(s)
    , _addr()
    , _addrsize(sizeof(_addr))
    , _opened(false)
    , _connected(false)
    , _server(false)
//    , _maxPacketSize(0)
{
    int result;

    if (s == INVALID_SOCKET) {
        throw new SocketException(E_SOCKET_CREATE, 0, "Socket invalido");
    }

    _opened = true;

    result = setbuffersize();
    if (result != E_OK) {
        throw new SocketException(E_SOCKET_SETSOCKOPT, 0, "Erro na mudanca do tamanho do buffer da interface de rede");
    }

    result = setreuse();
    if (result != E_OK) {
        throw new SocketException(E_SOCKET_SETSOCKOPT, 0, "Erro ao transformar o endereco do socket em reusavel");
    }
}

Socket::Socket() throw(SocketException*)
    : _lastError(0)
    , _socket(INVALID_SOCKET)
    , _addr()
    , _addrsize(sizeof(_addr))
    , _opened(false)
    , _connected(false)
    , _server(false)
{
}

Socket::~Socket()
{
    close();
}

int Socket::lastError()
{
    return _lastError;
}

int Socket::open(int family, int type, int protocol)
{
    if (_opened) {
        return E_OK;
    }

    _socket = SocketCtx::createSocket(family, type, protocol);
    if (_socket == INVALID_SOCKET) {
        _lastError = SocketWrapper::_getlasterror();
        NEW_ERROR(E_SOCKET_CREATE, SocketWrapper::_errorMessage(_lastError));
        return E_SOCKET_CREATE;
    }

    // tenta setar tamanho padrão do buffer e reuseaddr
    // continua mesmo que aconteça algum erro abaixo
    setbuffersize();
    setreuse();

    _opened = true;
    return E_OK;
}

int Socket::shutdown(int how)
{
    int result;

    result = SocketWrapper::_shutdown(_socket, how);
    if (result == SOCKET_ERROR) {
        _lastError = SocketWrapper::_getlasterror();
        NEW_ERROR(E_SOCKET_SHUTDOWN, SocketWrapper::_errorMessage(_lastError));
        return E_SOCKET_SHUTDOWN;
    }
    return E_OK;
}

int Socket::bind()
{
    if (_connected)
        return E_SOCKET_ALREADY_CONNECTED;

    int result;

    result = SocketWrapper::_bind(_socket, (struct sockaddr*) &_addr, _addrsize);
    if (result != 0) {
        _lastError = SocketWrapper::_getlasterror();
        NEW_ERROR(E_SOCKET_BIND, SocketWrapper::_errorMessage(_lastError));
        return E_SOCKET_BIND;
    }
    return E_OK;
}

int Socket::bind(const unsigned int port)
{
    if (_connected)
        return E_SOCKET_ALREADY_CONNECTED;

    memset(&_addr.sin_zero, '\0', 8);
    _addr.sin_addr.s_addr = htonl(INADDR_ANY);   // qualquer IP
    _addr.sin_family = AF_INET;
    _addr.sin_port = htons(port);                // se liga a uma porta específica

    int r = bind();
    if (r == E_OK) {
        _server = true;
        _connected = true;
    }
    return r;
}

int Socket::bind(const string& ip, const unsigned int port)
{
    if (_connected)
        return E_SOCKET_ALREADY_CONNECTED;

    struct sockaddr_in addr;
    memset(&addr.sin_zero, '\0', 8);
    addr.sin_addr.s_addr = inet_addr(ip.c_str());   // se liga a um ip específico
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);                    // se liga a uma porta específica

    return bind();
}

int Socket::invalidate()
{
    _socket = INVALID_SOCKET;
    return E_OK;
}

SOCKET Socket::getStdSocket()
{
    return _socket;
}

int Socket::close()
{
    if (!_opened)
        return E_OK;

    int result = SocketCtx::closeSocket(_socket);
    if (result != E_OK) {
        _lastError = SocketWrapper::_getlasterror();
        NEW_ERROR(E_SOCKET_CLOSE, SocketWrapper::_errorMessage(_lastError));
        return E_SOCKET_CLOSE;
    }
    _opened = false;
    _connected = false;
    _server = false;
    _socket = INVALID_SOCKET;
    return E_OK;
}

int Socket::setbuffersize(int size)
{
    int result;

    result = SocketWrapper::_setbuffersize(_socket, size);
    if (result == SOCKET_ERROR) {
        _lastError = SocketWrapper::_getlasterror();
        NEW_ERROR(E_SOCKET_SETSOCKOPT, SocketWrapper::_errorMessage(_lastError));
        return E_SOCKET_SETSOCKOPT;
    }
    return E_OK;
}

int Socket::setblocking(bool enable)
{
    enable = !enable;
#ifdef _MSC_VER
    int ret = ioctlsocket(_socket, FIONBIO, (u_long*) &enable); // 0x8004667e
#else
    int ret = ioctl(_socket, FIONBIO, (u_long*) &enable); // 0x8004667e
#endif

    if (ret == SOCKET_ERROR){ 
        _lastError = SocketWrapper::_getlasterror();
        NEW_ERROR(E_SOCKET_IOCTL, SocketWrapper::_errorMessage(_lastError));
        return E_SOCKET_IOCTL;
    }
    return E_OK;
}

int Socket::setreuse(bool enable)
{
    if (SocketWrapper::_setreuse(_socket, enable) != 0) {
        _lastError = SocketWrapper::_getlasterror();
        NEW_ERROR(E_SOCKET_SETSOCKOPT, SocketWrapper::_errorMessage(_lastError));
        return E_SOCKET_SETSOCKOPT;
    }
    return E_OK;
}

int Socket::setlinger(bool enable, int timeout_sec)
{
    if (SocketWrapper::_setlinger(_socket, enable, timeout_sec) != 0) {
        _lastError = SocketWrapper::_getlasterror();
        NEW_ERROR(E_SOCKET_SETSOCKOPT, SocketWrapper::_errorMessage(_lastError));
        return E_SOCKET_SETSOCKOPT;
    }
    return E_OK;
}

int Socket::setTtl(int ttl)
{
    char ttl_ = ttl;
    if (SocketWrapper::_setttl(_socket, ttl_) != 0) {
        _lastError = SocketWrapper::_getlasterror();
        NEW_ERROR(E_SOCKET_SETSOCKOPT, SocketWrapper::_errorMessage(_lastError));
        return E_SOCKET_SETSOCKOPT;
    }
    return E_OK;
}

int Socket::setLoop(bool loop)
{
    char loop_ = loop;
    if (SocketWrapper::_setloop(_socket, loop_) != 0) {
        _lastError = SocketWrapper::_getlasterror();
        NEW_ERROR(E_SOCKET_SETSOCKOPT, SocketWrapper::_errorMessage(_lastError));
        return E_SOCKET_SETSOCKOPT;
    }
    return E_OK;
}

int Socket::waitRead(long msec)
{
    return select(SocketWrapper::SELECT_READ, msec);
}

int Socket::waitWrite(long msec)
{
    return select(SocketWrapper::SELECT_WRITE, msec);
}

int Socket::select(SocketWrapper::SocketSelectType type, long msec)
{
    int ret = SocketWrapper::_select(_socket, type, msec);
    if (ret < 0) { // não foi timeout, foi erro
        _lastError = SocketWrapper::_getlasterror();
        NEW_ERROR(E_SOCKET_SELECT, SocketWrapper::_errorMessage(_lastError));
    }
    return ret;
}

string Socket::lastErrorMessage()
{
    return SocketWrapper::_errorMessage(SocketWrapper::_getlasterror());
}



