#ifndef _SOCKET_H_
#define _SOCKET_H_

#include <common.h>
#include <string>
#include <iostream>

#include "SocketCtx.h"
#include "SocketWrapper.h"
#include "SocketException.h"

using namespace std;

class Socket
{
protected:

    int _lastError;         ///< Código do último erro que aconteceu neste socket
    SOCKET _socket;         ///< Socket base

    struct sockaddr_in _addr;
    int _addrsize;
    bool _opened,
        _bound,
        _connected,
        _server;
    // tamanho máximo do pacote = 65507

protected:

    static const int CONNECT_TIMEOUT = 5000;
    static const int SELECT_WAIT_TIME = 500;                    ///< Valor padrão para espera no 'select()' (em ms)
    static const int DEFAULT_MULTICAST_TTL = 32;                ///< Valor padrão para o TTL
    static const int DEFAULT_UNICAST_TTL = 32;
    static const int DEFAULT_LOOPBACK = 0;                      ///< Valor padrão para o 'loopback'
    static const int DEFAULT_ADAPTER_BUFFER_SIZE = (512*1024);  ///< Tamanho padrão para o buffer da placa de rede
    static const int DEFAULT_LINGER_TIMEOUT = 3;                ///< Em segundos

    Socket(SOCKET so) throw(SocketException*);      ///< Inicializa o socket através de um socket base
    int open(int family, int type, int protocol);

    /** \brief Liga um socket a um endereço
     *  \param name Estrutura sockaddr com o endereço
     *  \param namelen Tamanho da estrutura 'name'
     *  \return E_OK ou E_SOCKET_BIND em caso de erro. O erro específico é guardado
     *          internamente, para pegá-lo usar a função lastError().
     */
    virtual int bind();

    virtual int bind(const unsigned int port);

    virtual int bind(const string& ip, const unsigned int port);

    /** \brief Desabilita envio e/ou recebimento de mensagens no socket
     *  \param how Flag que indica que operações serão canceladas (ver a função
     *         'shutdown' dos sockets)
     *  \return E_OK ou E_SOCKET_ERROR em caso de erro. O erro específico é guardado
     *          internamente, para pegá-lo usar a função lastError().
     *  \todo O código de retorno E_SOCKET_ERROR deve ser modificado para
     *        E_SOCKET_SHUTDOWN. Ele tem que ser adicionado na common.
     */
    virtual int shutdown(int how = SD_BOTH);

    virtual int setbuffersize(int size = DEFAULT_ADAPTER_BUFFER_SIZE);

    virtual int setreuse(bool enable = true);

    virtual int setlinger(bool enable = false, int timeout_sec = DEFAULT_LINGER_TIMEOUT);

    /** \brief Espera até que o socket esteja pronto para uma tarefa, definida por 'type'
     *  \param type Tipo do select: leitura, escrita ou exceção
     *  \param sec Número de segundos para a espera
     *  \param usec Número de microssegundos para a espera
     *  \return 0 (zero) se o tempo de espera expirou, SOCKET_ERROR se aconteceu algum erro
     *          ou o número de sockets disponíveis para a tarefa solicitada. Se aconteceu erro,
     *          o erro específico é guardado internamente, para pegá-lo usar a função lastError().
     *          O retorno é praticamente o mesmo da função 'select' dos sockets.
     */
    virtual int select(SocketWrapper::SocketSelectType type, long msec = SELECT_WAIT_TIME);

public:

    enum SocketError {
        E_SOCKET_OK = 0,
        E_SOCKET_NOT_CONNECTED,
        E_SOCKET_ALREADY_CONNECTED
    };

    Socket() throw(SocketException *);
    virtual ~Socket();

    /** \brief Retorna o código do último erro que aconteceu neste socket
     */
    int lastError();

    /** \brief Retorna a mensagem do último erro que aconteceu
     */
    string lastErrorMessage();

    int invalidate();

    SOCKET getStdSocket();

    /** \brief Fecha (finaliza) um socket
     *  \return E_OK ou E_SOCKET_CLOSE em caso de erro. O erro específico é guardado
     *          internamente, para pegá-lo usar a função lastError().
     */
    virtual int close();

    /** \brief Aguarda, por um tempo máximo escolhido, até que o socket esteja pronto para leitura
     *  \param sec Número de segundos para a espera
     *  \param usec Número de microssegundos para a espera
     *  \return Retorno igual ao da função 'select()'.
     */
    virtual int waitRead(long msec = SELECT_WAIT_TIME);

    /** \brief Aguarda, por um tempo máximo escolhido, até que o socket esteja pronto para escrita
     *  \param sec Número de segundos para a espera
     *  \param usec Número de microssegundos para a espera
     *  \return Retorno igual ao da função 'select()'.
     */
    virtual int waitWrite(long msec = SELECT_WAIT_TIME);

    /** \brief Seta o socket como bloqueante ou não bloqueante
     *  \param blocking Setar como bloqueante (true) ou não bloqueante (false)
     *  \return E_OK ou E_SOCKET_IOCTLSOCKET em caso de erro. O erro específico é guardado
     *          internamente, para pegá-lo usar a função lastError().
     */
    virtual int setblocking(bool enable);

    virtual int setTtl(int ttl);
    virtual int setLoop(bool loop);
};

#endif
