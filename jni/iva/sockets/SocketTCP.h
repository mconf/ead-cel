#ifndef _SOCKET_TCP_H_
#define _SOCKET_TCP_H_

#include "Socket.h"

class SocketTCP : public Socket
{
private:
    static const int _family = AF_INET;
    static const int _type = SOCK_STREAM;
    static const int _protocol = IPPROTO_TCP;

    SocketTCP(SOCKET so) throw(SocketException*);

protected:

    /** \brief Conecta a um endereço
     *  \param name Estrutura sockaddr com o endereço
     *  \param size Tamanho da estrutura 'name'
     *  \return E_OK ou E_SOCKET_CONNECT em caso de erro. O erro específico é guardado
     *          internamente, para pegá-lo usar a função lastError().
     *
     * Para sockets bloqueantes, o connect retorna um valor indicando se conseguiu ou não
     * conectar.
     * Para sockets NÃO bloqueantes, ele sempre retorna código de erro e depois continua
     * tentando conectar. Nesse caso não é necessário chamar o connect novamente. Para
     * descrobrir se a conexão já está pronta, testar se o socket é ''writable''
     * (ver função waitWrite).
     */
    virtual int connect();

    virtual int setkeepalive(bool enable = true, unsigned int timeout_msec = DEFAULT_KEEPALIVE_TIMEOUT, unsigned int interval_msec = DEFAULT_KEEPALIVE_INTERVAL);

    /**
     *  Operador >> para recv não faz sentido no tcp, pois precisa saber quanto
     *  do stream será lido
     */

    /** \brief Coloca o socket em estado de espera por uma conexão
     *  \param backlog Tamanho máximo da fila das conexões pendentes
     *  \return E_OK ou E_SOCKET_LISTEN em caso de erro. O erro específico é guardado
     *          internamente, para pegá-lo usar a função lastError().
     */
    virtual int listen(int backlog = SOMAXCONN);

    virtual int connect(const IPv4& ip, const unsigned int port);

public:
    static const int DEFAULT_KEEPALIVE_TIMEOUT = 2000;
    static const int DEFAULT_KEEPALIVE_INTERVAL = 1000;
    static const int DEFAULT_KEEPALIVE_PROBES = 10;         ///< Valor não configurável no windows

    SocketTCP() throw(SocketException*);
    virtual ~SocketTCP();

    /** \brief Aceita uma nova conexão
     *  \param addr Ponteiro opcional para estrutura que armazenará o endereço da
     *              entidade que se conectou a este socket
     *  \param addrlen Retorna o tamanho, em bytes, da estrutura em 'addr'
     *  \return E_OK ou NULL em caso de erro. O erro específico é guardado
     *          internamente, para pegá-lo usar a função lastError().
     */


    virtual SocketTCP* accept(struct sockaddr* addr = NULL, socklen_t* addrlen = NULL);

    virtual int send(const char* buf, int len);
    virtual int send(const string& buf);
    virtual int operator<<(const string& buf);

    virtual int recv(char* buf, int len);
    virtual int recv(string& buf, int len);

    IPv4 getLocalIPv4Address() const;
    void getLocalIPv4Address(IPv4& ip) const;

    IPv4 getRemoteIPv4Address() const;
    void getRemoteIPv4Address(IPv4& ip) const;

    virtual int openAsClient(const IPv4& ip, const unsigned int port, bool blocking = true, int connectTimeout = CONNECT_TIMEOUT);

    virtual int openAsServer(const unsigned int port, bool blocking = true);
};

#endif
