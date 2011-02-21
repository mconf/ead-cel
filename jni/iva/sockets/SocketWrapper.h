#ifndef _SOCKET_WRAPPER_H_
#define _SOCKET_WRAPPER_H_

#include <string>

#ifdef _MSC_VER
#include <winsock2.h>
#include <Iphlpapi.h>
#include <ws2tcpip.h>
#include <Mstcpip.h>
#define socklen_t int
#else // Linux
#include <common.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <unistd.h>
#define SOCKET int
#define SD_BOTH 2
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define DWORD unsigned int
#define SO_DONTLINGER false
#endif


using namespace std;

class SocketWrapper
{
public:

    enum SocketSelectType {
        SELECT_READ,
        SELECT_WRITE,
        SELECT_EXCEPT
    };

#ifndef _MSC_VER
    static int WSAGetLastError();
#endif


    /**
     *  http://msdn.microsoft.com/en-us/library/ms740149%28VS.85%29.aspx
     *  \return bytes enviados em caso de sucesso
     *  \return SOCKET_ERROR em caso de erro
     */
    static int _send(SOCKET s, const char *buf, int len, int flags);
    /**
     *  http://msdn.microsoft.com/en-us/library/ms740148%28VS.85%29.aspx
     *  \return bytes enviados em caso de sucesso
     *  \return SOCKET_ERROR em caso de erro
     */
    static int _sendto(SOCKET s, const char *buf, int len, int flags,
                       const struct sockaddr *to, int tolen);
    /**
     *  http://msdn.microsoft.com/en-us/library/ms740121%28VS.85%29.aspx
     *  \return bytes recebidos em caso de sucesso
     *  \return 0 se a conexão foi finalizada graciosamente
     *  \return SOCKET_ERROR em caso de erro
     */
    static int _recv(SOCKET s, char *buf, int len, int flags);
    /**
     *  http://msdn.microsoft.com/en-us/library/ms740120%28VS.85%29.aspx
     *  \return bytes recebidos em caso de sucesso
     *  \return 0 se a conexão foi finalizada graciosamente
     *  \return SOCKET_ERROR em caso de erro
     */
    static int _recvfrom(SOCKET s, char* buf, int len, int flags = 0, 
                    struct sockaddr* from = NULL, socklen_t* fromlen = NULL);
    /**
     *  http://msdn.microsoft.com/en-us/library/ms737550%28VS.85%29.aspx
     *  \return 0 em caso de sucesso
     *  \return SOCKET_ERROR em caso de erro
     */
    static int _bind(SOCKET s, const struct sockaddr *name, int namelen);
    /**
     *  http://msdn.microsoft.com/en-us/library/ms737625%28VS.85%29.aspx
     *  \return 0 em caso de sucesso
     *  \return SOCKET_ERROR em caso de erro, se o socket é bloqueante,
     *      ou retorno normal se o socket é não bloqueante - deve testar o
     *      select writable para saber se a conexão foi atendida
     */
    static int _connect(SOCKET s, const struct sockaddr *name, int namelen);
    static SOCKET _open(int family, int type, int protocol);
    /**
     *  http://msdn.microsoft.com/en-us/library/ms737582%28VS.85%29.aspx
     *  \return 0 em caso de sucesso
     *  \return SOCKET_ERROR em caso de erro
     */
    static int _close(SOCKET s);
    /**
     *  http://msdn.microsoft.com/en-us/library/ms740481%28VS.85%29.aspx
     *  \return 0 em caso de sucesso
     *  \return SOCKET_ERROR em caso de erro
     */
    static int _shutdown(SOCKET s, int how);
    /**
     *  http://msdn.microsoft.com/en-us/library/ms739168%28VS.85%29.aspx
     *  \return 0 em caso de sucesso
     *  \return SOCKET_ERROR em caso de erro
     */
    static int _listen(SOCKET s, int backlog);
    /**
     *  http://msdn.microsoft.com/en-us/library/ms737526%28VS.85%29.aspx
     *  \return descritor de um socket válido em caso de sucesso
     *  \return INVALID_SOCKET em caso de erro
     */
    static int _accept(SOCKET s, struct sockaddr *addr = NULL, socklen_t *addrlen = NULL);
    /**
     *  http://msdn.microsoft.com/en-us/library/ms738544%28VS.85%29.aspx
     *  \return 0 em caso de sucesso
     *  \return SOCKET_ERROR em caso de erro
     */
    static int _getsockopt(SOCKET s, int level, int optname, char *optval, socklen_t *optlen);
    /**
     *  http://msdn.microsoft.com/en-us/library/ms740476%28VS.85%29.aspx
     *  \return 0 em caso de sucesso
     *  \return SOCKET_ERROR em caso de erro
     */
    static int _setsockopt(SOCKET s, int level, int optname, const char *optval, int optlen);
    /**
     *  http://msdn.microsoft.com/en-us/library/ms740141%28VS.85%29.aspx
     *  \return +0 se o sockt está pronto para ser lido/escrito
     *  \return 0 em caso de timeout
     *  \return SOCKET_ERROR em caso de erro
     */
    static int _select(SOCKET s, SocketSelectType type, long msec);
    /**
     *  http://msdn.microsoft.com/en-us/library/ms741621%28VS.85%29.aspx
     *  \return 0 em caso de sucesso
     *  \return SOCKET_ERROR em caso de erro
     */
    static int _setkeepalive(SOCKET s, bool enable, int timeout, int interval);
    /**
     *  http://msdn.microsoft.com/en-us/library/ms739165%28v=VS.85%29.aspx
     *  \return 0 em caso de sucesso
     *  \return SOCKET_ERROR em caso de erro
     */
    static int _setlinger(SOCKET s, bool enable, int timeout_sec);
    /**
     *  \return 0 em caso de sucesso
     *  \return SOCKET_ERROR em caso de erro
     */
    static int _setreuse(SOCKET s, bool enable);
    /**
     *  \return 0 em caso de sucesso
     *  \return SOCKET_ERROR em caso de erro
     */
    static int _setbuffersize(SOCKET s, int size);
    /**
     *  \return 0 em caso de sucesso
     *  \return SOCKET_ERROR em caso de erro
     */
//    static int _getmaxpacketsize(SOCKET s, int& packetsize);
    /**
     *  \return 0 em caso de sucesso
     *  \return SOCKET_ERROR em caso de erro
     */
    static int _addmembership(SOCKET s, struct ip_mreq* mreq);
    /**
     *  \return 0 em caso de sucesso
     *  \return SOCKET_ERROR em caso de erro
     */
    static int _dropmembership(SOCKET s, struct ip_mreq* mreq);
    /**
     *  \return 0 em caso de sucesso
     *  \return SOCKET_ERROR em caso de erro
     */
    static int _setttl(SOCKET s, char ttl);
    /**
     *  \return 0 em caso de sucesso
     *  \return SOCKET_ERROR em caso de erro
     */
    static int _setloop(SOCKET s, char loop);

    /**
     *  http://msdn.microsoft.com/en-us/library/ms742213(VS.85).aspx
     *  \return 0 em caso de sucesso
     *  \return !0 em caso de erro
     */
    static int _startup();
    /**
     *  http://msdn.microsoft.com/en-us/library/ms741549(VS.85).aspx
     *  \return 0 em caso de sucesso
     *  \return SOCKET_ERROR em caso de erro
     */
    static int _cleanup();
    static int _getlasterror();
    /**
     *  http://msdn.microsoft.com/en-us/library/ms740668%28VS.85%29.aspx
     */
    static string _errorMessage(int error);
};

#endif
