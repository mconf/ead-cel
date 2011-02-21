#include "SocketWrapper.h"

#ifndef _MSC_VER
int SocketWrapper::WSAGetLastError()
{
    //printf("\nSocketWrapper: chamou WSAGetLastError errno = %d\n",errno);
    return errno;
}
#endif

int SocketWrapper::_send(SOCKET s, const char *buf, int len, int flags)
{
    return send(s, buf, len, flags);
}

int SocketWrapper::_sendto(SOCKET s, const char *buf, int len, int flags,
                   const struct sockaddr *to, int tolen)
{
    return sendto(s, buf, len, flags, to, tolen);
}

int SocketWrapper::_bind(SOCKET s, const struct sockaddr *name, int namelen)
{
    return bind(s, name, namelen);
}

int SocketWrapper::_connect(SOCKET s, const struct sockaddr *name, int namelen)
{
    return connect(s, name, namelen);
}

SOCKET SocketWrapper::_open(int family, int type, int protocol)
{
    return socket(family, type, protocol);
}

int SocketWrapper::_close(SOCKET s)
{
#ifdef _MSC_VER
    return closesocket(s);
#else
    close(s);
    return 0;
#endif
}

int SocketWrapper::_recv(SOCKET s, char *buf, int len, int flags)
{
    return recv(s, buf, len, flags);
}

int SocketWrapper::_recvfrom(SOCKET s, char* buf, int len, int flags, struct sockaddr* from,
                             socklen_t* fromlen)
{
    return recvfrom(s, buf, len, flags, from, fromlen);
}

int SocketWrapper::_shutdown(SOCKET s, int how)
{
    return shutdown(s, how);
}

int SocketWrapper::_listen(SOCKET s, int backlog)
{
    return listen(s, backlog);
}

int SocketWrapper::_accept(SOCKET s, struct sockaddr *addr, socklen_t *addrlen)
{
    return accept(s, addr, addrlen);
}

int SocketWrapper::_getsockopt(SOCKET s, int level, int optname, char *optval, socklen_t *optlen)
{
    return getsockopt(s, level, optname, optval, optlen);
}

int SocketWrapper::_setsockopt(SOCKET s, int level, int optname, const char *optval, int optlen)
{
    return setsockopt(s, level, optname, optval, optlen);
}

int SocketWrapper::_select(SOCKET s, SocketSelectType type, long msec)
{
    struct timeval tv;
    fd_set fdset;
    int ret = 0;

    tv.tv_sec = msec / 1000;
    tv.tv_usec = (msec % 1000) * 1000;
    FD_ZERO(&fdset);
    FD_SET(s, &fdset);
    switch (type) {
        case SELECT_READ:
            ret = select((int)s+1, &fdset, NULL, NULL, &tv);
            break;
        case SELECT_WRITE:
            ret = select((int)s+1, NULL, &fdset, NULL, &tv);
            break;
        case SELECT_EXCEPT:
            ret = select((int)s+1, NULL, NULL, &fdset, &tv);
            break;
    }
    return ret;
}

int SocketWrapper::_setkeepalive(SOCKET s, bool enable, int timeout, int interval)
{
    char alive = enable;

    // liga/desliga o keepalive
    int result = _setsockopt(s, SOL_SOCKET, SO_KEEPALIVE, (char*)&alive, sizeof(alive));
    if (result != 0)
        return result;

#ifdef _MSC_VER
    // http://msdn.microsoft.com/en-us/library/ms741621(VS.85).aspx
    struct tcp_keepalive settings, returned;
    DWORD dwBytes;
    settings.onoff = enable;
    settings.keepalivetime = timeout; // quando deve enviar o primeiro pacote de keepalive
    settings.keepaliveinterval = interval; // intervalo entre os pacotes

    // número de 'probes' não pode ser modificado no windows, é sempre 10
    // ou seja, só diz que socket tá sem conexão depois de falhar em 10 keepalives
    // suportado do windows 2000 em diante

    // seta as opções de intervalo, etc...
    return WSAIoctl(s, SIO_KEEPALIVE_VALS, &settings, sizeof(settings),
                    &returned, sizeof(returned), (LPDWORD)&dwBytes, NULL, NULL);
#else
    //int dontblock = 1;
    //ioctl(s, FIONBIO, (char *) &dontblock);
    /// \todo Achar equivalente de WSAIoctl para linux para implementar o keepalive
    return 0;
#endif

}

int SocketWrapper::_setlinger(SOCKET s, bool enable, int timeout_sec)
{
    struct linger settings;
    settings.l_onoff = enable;
    settings.l_linger = timeout_sec;
    
    return _setsockopt(s, SOL_SOCKET, enable? SO_LINGER : SO_DONTLINGER, (char*) &settings, sizeof(settings));
}

int SocketWrapper::_setreuse(SOCKET s, bool enable)
{
    char reuse = enable;
    return _setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
}

int SocketWrapper::_setbuffersize(SOCKET s, int bufsize)
{
    int r;

    r = _setsockopt(s, SOL_SOCKET, SO_RCVBUF, (char*) &bufsize, (int) sizeof(bufsize));
    if (r != 0)
        return r;
    
    r = _setsockopt(s, SOL_SOCKET, SO_SNDBUF, (char*) &bufsize, (int) sizeof(bufsize));
    if (r != 0)
        return r;

    return r;
}

int SocketWrapper::_addmembership(SOCKET s, struct ip_mreq* mreq)
{
    return _setsockopt(s, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*) mreq,
                        sizeof(struct ip_mreq));
}

int SocketWrapper::_dropmembership(SOCKET s, struct ip_mreq* mreq)
{
    return _setsockopt(s, IPPROTO_IP, IP_DROP_MEMBERSHIP, (char*) mreq,
                        sizeof(struct ip_mreq));
}

int SocketWrapper::_setttl(SOCKET s, char ttl)
{
    int r;
    char opt;

    socklen_t optlen;

    opt = ttl;
    r = _setsockopt(s, IPPROTO_IP, IP_MULTICAST_TTL, &opt, sizeof(opt));
    if (r != 0)
        return r;
    opt = 0;
    optlen = sizeof(opt);
    r = _getsockopt(s, IPPROTO_IP, IP_MULTICAST_TTL, &opt, &optlen);
    if (r != 0)
        return r;
    if (ttl != opt) {
        printf("Falha ao configurar IP_MULTICAST_TTL\n");
        return SOCKET_ERROR;
    }

    opt = ttl;
    r = _setsockopt(s, IPPROTO_IP, IP_TTL, &opt, sizeof(opt));
    if (r != 0)
        return r;
    opt = 0;
    optlen = sizeof(opt);
    r = _getsockopt(s, IPPROTO_IP, IP_TTL, &opt, &optlen);
    if (r != 0)
        return r;
    if (ttl != opt) {
        printf("Falha ao configurar IP_TTL\n");
        return SOCKET_ERROR;
    }

    return r;
}

int SocketWrapper::_setloop(SOCKET s, char loop)
{
    int r;
    char opt;

    socklen_t optlen;

    opt = loop;
    r = _setsockopt(s, IPPROTO_IP, IP_MULTICAST_LOOP, &opt, sizeof(opt));
    if (r != 0)
        return r;
    opt = 0;
    optlen = sizeof(opt);
    r = _getsockopt(s, IPPROTO_IP, IP_MULTICAST_LOOP, &opt, &optlen);
    if (r != 0)
        return r;
    if (loop != opt) {
        printf("Falha ao configurar IP_MULTICAST_LOOP\n");
        return SOCKET_ERROR;
    }
        
    return r;
}

int SocketWrapper::_getlasterror()
{
    return WSAGetLastError();
}

int SocketWrapper::_startup()
{
#ifdef _MSC_VER
    WORD wVersionRequested;
    WSADATA wsaData;
    wVersionRequested = MAKEWORD(2,2);
    return WSAStartup(wVersionRequested, &wsaData);
#else
    return 0;
#endif
}

int SocketWrapper::_cleanup()
{
#ifdef _MSC_VER
    return WSACleanup();
#endif
}

string SocketWrapper::_errorMessage(int error)
{
    switch (error) {
#ifdef _MSC_VER
        case WSA_INVALID_HANDLE:
            return "Specified event object handle is invalid";
        case WSA_NOT_ENOUGH_MEMORY:
            return "Insufficient memory available";
        case WSA_INVALID_PARAMETER:
            return "One or more parameters are invalid";
        case WSA_OPERATION_ABORTED:
            return "Overlapped operation aborted";
        case WSA_IO_INCOMPLETE: 
            return "Overlapped I/O event object not in signaled state";
        case WSA_IO_PENDING:
            return "Overlapped operations will complete later";
        case WSAEINTR:
            return "Interrupted function call";
        case WSAEBADF:
            return "File handle is not valid";
        case WSAEACCES:
            return "Permission denied";
        case WSAEFAULT:
            return "Bad address";
        case WSAEINVAL:
            return "Invalid argument";
        case WSAEMFILE:
            return "Too many open files";
        case WSAEWOULDBLOCK:
            return "Resource temporarily unavailable";
        case WSAEINPROGRESS:
            return "Operation now in progress";
        case WSAEALREADY:
            return "Operation already in progress";
        case WSAENOTSOCK:
            return "Socket operation on nonsocket";
        case WSAEDESTADDRREQ:
            return "Destination address required";
        case WSAEMSGSIZE:
            return "Message too long";
        case WSAEPROTOTYPE:
            return "Protocol wrong type for socket";
        case WSAENOPROTOOPT:
            return "Bad protocol option";
        case WSAEPROTONOSUPPORT:
            return "Protocol not supported";
        case WSAESOCKTNOSUPPORT:
            return "Socket type not supported";
        case WSAEOPNOTSUPP:
            return "Operation not supported";
        case WSAEPFNOSUPPORT:
            return "Protocol family not supported";
        case WSAEAFNOSUPPORT:
            return "Address family not supported by protocol family";
        case WSAEADDRINUSE:
            return "Address already in use";
        case WSAEADDRNOTAVAIL:
            return "Cannot assign requested address";
        case WSAENETDOWN:
            return "Network is down";
        case WSAENETUNREACH:
            return "Network is unreachable";
        case WSAENETRESET:
            return "Network dropped connection on reset";
        case WSAECONNABORTED:
            return "Software caused connection abort";
        case WSAECONNRESET:
            return "Connection reset by peer";
        case WSAENOBUFS:
            return "No buffer space available";
        case WSAEISCONN:
            return "Socket is already connected";
        case WSAENOTCONN:
            return "Socket is not connected";
        case WSAESHUTDOWN:
            return "Cannot send after socket shutdown";
        case WSAETOOMANYREFS:
            return "Too many references";
        case WSAETIMEDOUT:
            return "Connection timed out";
        case WSAECONNREFUSED:
            return "Connection refused";
        case WSAELOOP:
            return "Cannot translate name";
        case WSAENAMETOOLONG:
            return "Name too long";
        case WSAEHOSTDOWN:
            return "Host is down";
        case WSAEHOSTUNREACH:
            return "No route to host";
        case WSAENOTEMPTY:
            return "Directory not empty";
        case WSAEPROCLIM:
            return "Too many processes";
        case WSAEUSERS:
            return "client quota exceeded";
        case WSAEDQUOT:
            return "Disk quota exceeded";
        case WSAESTALE:
            return "Stale file handle reference";
        case WSAEREMOTE:
            return "Item is remote";
        case WSASYSNOTREADY:
            return "Network subsystem is unavailable";
        case WSAVERNOTSUPPORTED:
            return "Winsock.dll version out of range";
        case WSANOTINITIALISED:
            return "Successful WSAStartup not yet performed";
        case WSAEDISCON:
            return "Graceful shutdown in progress";
        case WSAENOMORE:
            return "No more results";
        case WSAECANCELLED:
            return "Call has been canceled";
        case WSAEINVALIDPROCTABLE:
            return "Procedure call table is invalid";
        case WSAEINVALIDPROVIDER:
            return "Service provider is invalid";
        case WSAEPROVIDERFAILEDINIT:
            return "Service provider failed to initialize";
        case WSASYSCALLFAILURE:
            return "System call failure";
        case WSASERVICE_NOT_FOUND:
            return "Service not found";
        case WSATYPE_NOT_FOUND:
            return "Class type not found";
        case WSA_E_NO_MORE:
            return "No more results";
        case WSA_E_CANCELLED:
            return "Call was canceled";
        case WSAEREFUSED:
            return "Database query was refused";
        case WSAHOST_NOT_FOUND:
            return "Host not found";
        case WSATRY_AGAIN:
            return "Nonauthoritative host not found";
        case WSANO_RECOVERY:
            return "This is a nonrecoverable error";
        case WSANO_DATA:
            return "Valid name, no data record of requested type";
        case WSA_QOS_RECEIVERS:
            return "QOS receivers";
        case WSA_QOS_SENDERS:
            return "QOS senders";
        case WSA_QOS_NO_SENDERS:
            return "No QOS senders";
        case WSA_QOS_NO_RECEIVERS:
            return "QOS no receivers";
        case WSA_QOS_REQUEST_CONFIRMED:
            return "QOS request confirmed";
        case WSA_QOS_ADMISSION_FAILURE:
            return "QOS admission error";
        case WSA_QOS_POLICY_FAILURE:
            return "QOS policy failure";
        case WSA_QOS_BAD_STYLE:
            return "QOS bad style";
        case WSA_QOS_BAD_OBJECT:
            return "QOS bad object";
        case WSA_QOS_TRAFFIC_CTRL_ERROR:
            return "QOS traffic control error";
        case WSA_QOS_GENERIC_ERROR:
            return "QOS generic error";
        case WSA_QOS_ESERVICETYPE:
            return "QOS service type error";
        case WSA_QOS_EFLOWSPEC:
            return "QOS flowspec error";
        case WSA_QOS_EPROVSPECBUF:
            return "Invalid QOS provider buffer";
        case WSA_QOS_EFILTERSTYLE:
            return "Invalid QOS filter style";
        case WSA_QOS_EFILTERTYPE:
            return "Invalid QOS filter type";
        case WSA_QOS_EFILTERCOUNT:
            return "Incorrect QOS filter count";
        case WSA_QOS_EOBJLENGTH:
            return "Invalid QOS object length";
        case WSA_QOS_EFLOWCOUNT:
            return "Incorrect QOS flow count";
        case WSA_QOS_EUNKOWNPSOBJ:
            return "Unrecognized QOS object";
        case WSA_QOS_EPOLICYOBJ:
            return "Invalid QOS policy object";
        case WSA_QOS_EFLOWDESC:
            return "Invalid QOS flow descriptor";
        case WSA_QOS_EPSFLOWSPEC:
            return "Invalid QOS provider-specific flowspec";
        case WSA_QOS_EPSFILTERSPEC:
            return "Invalid QOS provider-specific filterspec";
        case WSA_QOS_ESDMODEOBJ:
            return "Invalid QOS shape discard mode object";
        case WSA_QOS_ESHAPERATEOBJ:
            return "Invalid QOS shaping rate object";
        case WSA_QOS_RESERVED_PETYPE:
            return "Reserved policy QOS element type";
#else
        case EDEADLK:
            return "Resource deadlock would occur";
        case ENAMETOOLONG:
            return "File name too long";
        case ENOLCK:
            return "No record locks available";
        case ENOSYS:
            return "Function not implemented";
        case ENOTEMPTY:
            return "Directory not empty";
        case ELOOP:
            return "Too many symbolic links encountered";
        case EWOULDBLOCK:
            return "Operation would block";
        //case EAGAIN:
            //return "Operation would block";
        case ENOMSG:
            return "No message of desired type";
        case EIDRM:
            return "Identifier removed";
        case ECHRNG:
            return "Channel number out of range";
        case EL2NSYNC:
            return "Level 2 not synchronized";
        case EL3HLT:
            return "Level 3 halted";
        case EL3RST:
            return "Level 3 reset";
        case ELNRNG:
            return "Link number out of range";
        case EUNATCH:
            return "Protocol driver not attached";
        case ENOCSI:
            return "No CSI structure available";
        case EL2HLT:
            return "Level 2 halted";
        case EBADE:
            return "Invalid exchange";
        case EBADR:
            return "Invalid request descriptor";
        case EXFULL:
            return "Exchange full";
        case ENOANO:
            return "No anode";
        case EBADRQC:
            return "Invalid request code";
        case EBADSLT:
            return "Invalid slot";
        case EBFONT:
            return "Bad font file format";
        case ENOSTR:
            return "Device not a stream";
        case ENODATA:
            return "No data available";
        case ETIME:
            return "Timer expired";
        case ENOSR:
            return "Out of streams resources";
        case ENONET:
            return "Machine is not on the network";
        case ENOPKG:
            return "Package not installed";
        case EREMOTE:
            return "Object is remote";
        case ENOLINK:
            return "Link has been severed";
        case EADV:
            return "Advertise error";
        case ESRMNT:
            return "Srmount error";
        case ECOMM:
            return "Communication error on send";
        case EPROTO:
            return "Protocol error";
        case EMULTIHOP:
            return "Multihop attempted";
        case EDOTDOT:
            return "RFS specific error";
        case EBADMSG:
            return "Not a data message";
        case EOVERFLOW:
            return "Value too large for defined data type";
        case ENOTUNIQ:
            return "Name not unique on network";
        case EBADFD:
            return "File descriptor in bad state";
        case EREMCHG:
            return "Remote address changed";
        case ELIBACC:
            return "Can not access a needed shared library";
        case ELIBBAD:
            return "Accessing a corrupted shared library";
        case ELIBSCN:
            return ".lib section in a.out corrupted";
        case ELIBMAX:
            return "Attempting to link in too many shared libraries";
        case ELIBEXEC:
            return "Cannot exec a shared library directly";
        case EILSEQ:
            return "Illegal byte sequence";
        case ERESTART:
            return "Interrupted system call should be restarted";
        case ESTRPIPE:
            return "Streams pipe error";
        case EUSERS:
            return "Too many users";
        case ENOTSOCK:
            return "Socket operation on non-socket";
        case EDESTADDRREQ:
            return "Destination address required";
        case EMSGSIZE:
            return "Message too long";
        case EPROTOTYPE:
            return "Protocol wrong type for socket";
        case ENOPROTOOPT:
            return "Protocol not available";
        case EPROTONOSUPPORT:
            return "Protocol not supported";
        case ESOCKTNOSUPPORT:
            return "Socket type not supported";
        case EOPNOTSUPP:
            return "Operation not supported on transport endpoint";
        case EPFNOSUPPORT:
            return "Protocol family not supported";
        case EAFNOSUPPORT:
            return "Address family not supported by protocol";
        case EADDRINUSE:
            return "Address already in use";
        case EADDRNOTAVAIL:
            return "Cannot assign requested address";
        case ENETDOWN:
            return "Network is down";
        case ENETUNREACH:
            return "Network is unreachable";
        case ENETRESET:
            return "Network dropped connection because of reset";
        case ECONNABORTED:
            return "Software caused connection abort";
        case ECONNRESET:
            return "Connection reset by peer";
        case ENOBUFS:
            return "No buffer space available";
        case EISCONN:
            return "Transport endpoint is already connected";
        case ENOTCONN:
            return "Transport endpoint is not connected";
        case ESHUTDOWN:
            return "Cannot send after transport endpoint shutdown";
        case ETOOMANYREFS:
            return "Too many references: cannot splice";
        case ETIMEDOUT:
            return "Connection timed out";
        case ECONNREFUSED:
            return "Connection refused";
        case EHOSTDOWN:
            return "Host is down";
        case EHOSTUNREACH:
            return "No route to host";
        case EALREADY:
            return "Operation already in progress";
        case EINPROGRESS:
            return "Operation now in progress";
        case ESTALE:
            return "Stale NFS file handle";
        case EUCLEAN:
            return "Structure needs cleaning";
        case ENOTNAM:
            return "Not a XENIX named type file";
        case ENAVAIL:
            return "No XENIX semaphores available";
        case EISNAM:
            return "Is a named type file";
        case EREMOTEIO:
            return "Remote I/O error";
        case EDQUOT:
            return "Quota exceeded";
        case ENOMEDIUM:
            return "No medium found";
        case EMEDIUMTYPE:
            return "Wrong medium type";
        case ECANCELED:
            return "Operation Canceled";
        case ENOKEY:
            return "Required key not available";
        case EKEYEXPIRED:
            return "Key has expired";
        case EKEYREVOKED:
            return "Key has been revoked";
        case EKEYREJECTED:
            return "Key was rejected by service";
#endif
        default:
            return "Unknown error";
    }
}
