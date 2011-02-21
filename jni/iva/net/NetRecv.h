#ifndef _NET_RECV_H_
#define _NET_RECV_H_

#include "netDefs.h"
#include <queue.h>
#include <Mutex.h>
#include <Thread.h>
#include <SocketUDP.h>
#include "NetStorage.h"
#include "NetPacket.h"
#include "NetRedir.h"
#include "NetRecvValidator.h"

/** \brief Classe para recebimento de dados pela rede
 *
 */
class NetRecv
{
public:
    static const int MAX_PACKET_WAIT_AUDIO = 80;    ///< Espera máxima por pacotes de áudio atrasados
    static const int MAX_PACKET_WAIT_VIDEO = 100;   ///< Espera máxima por pacotes de vídeo atrasados
    static const int DEFAULT_BUFFER_SIZE = 150;     ///< Tamanho máximo do buffer (em frames)

private:
    SocketUDP _socket;                       ///< Socket usado para receber dados
    queue_t * _outQueue;                     ///< Fila de destino
    Mutex _mutexSocket;                      ///< Mutex para controle geral da NetRecv
    Thread<NetRecv> * _thread;               ///< Thread para recebimento dos pacotes
    bool _threadRun;                         ///< Flag de controle sobre a '_thread'
    Mutex _redirMutex;                       ///< Mutex para controle dos redirecionamentos
    NetStorage * _storage;                   ///< Objeto que administra os pacotes que chegam na rede
    int _bufferSize;                         ///< Quantidade de buffers
    unsigned int _maxPacketWait;
    NetType _contentType;                    ///< Tipo de conteúdo que esta netrecv está recebendo
    NetRedir * _redir;                       ///< Objeto que trata o redirecionamento
    NetRecvValidator * _validator;           ///< Objeto que trata a validação dos pacotes
    NetStatistics _stats;                    ///< Objeto que mantém as estatísticas de recebimento
    IPv4 _ip;                                ///< IP de onde está recebendo os dados
    uint16_t _sessionId;                     ///< Identificador da sessão

    int _RecvThread_WaitPacket(NetPacket * packet);
    void * _RecvThread(void *);

public:
    /** \brief Contrutor padrão da Netrecv
     *  \param type Tipo dos pacotes que serão recebidos (áudio, vídeo, ...)
     *  \param queue Queue onde serão colocados os dados recebidos
     *  \param maxPackWait Tempo máximo de espera por pacotes que não chegaram ainda (em ms). Se
     *         zero, seta o valor padrão conforme \a type
     *  \param bufferSize Número máximo de items (frames) no buffer.
     */
    NetRecv(NetType type, queue_t * queue,
            uint16_t sessionId = 0,
            unsigned int maxPacketWait = 0,
            unsigned int bufferSize = DEFAULT_BUFFER_SIZE);
    ~NetRecv();

    /** \brief Inicia o recebimento dos dados
     *  \param ip IP do transmissor ou do grupo multicast
     *  \param port Porta que deve ser ouvida
     *  \return E_OK em caso de sucesso ou o código de erro gerado
     */
    int start(const IPv4 &ip, unsigned int port);

    /** \brief Para o recebimento dos dados
     *  \return E_OK em caso de sucesso ou o código de erro gerado
     */
    int stop();

    /** \brief Seta o tempo máximo de espera dos pacotes
     *  \param value Tempo em ms
     *
     * Indica o tempo máximo que a lib irá esperar por um pacote que ainda não
     * foi recebido. Exemplo: são recebidos os frames com número de sequência
     * 1 e 3, mas o 2 não foi recebido. O frame 3 não será entregue até que o
     * frame 2 seja recebido, com um timeout de \a value milisegundos. Se o frame
     * 2 contém vários pacotes, a cada pacote do frame 2 que é recebido o timeout
     * é zerado e começa de novo.
     */
    void setMaxPacketWait(unsigned int value);

    /** \brief Associa uma estrutura de redirecionamentos na NetRecv
     *  \param value Estrutura que contém os redirecionamentos
     *
     * A NetRecv utiliza esta estrutura para verificar se deve redirecionar
     * os dados que recebe. Cada pacote recebido é redirecionado automaticamente
     * para cada item de redirecionamento existente no objeto NetRedir.
     */
    void setRedirect(NetRedir * value);

    /** \brief Seta um objeto para validação dos pacotes recebidos
     *  \param value Validador
     *
     * A validação é feita após as validações básicas (tipo do pacote, id da sessão) e
     * após o redirecionamento dos pacotes. Além disso os pacotes são contabilizados
     * nas estatísticas antes de serem da validação.
     * Um exemplo de uso é para descartar pacotes com determinadas flags de áudio.
     */
    void setPacketValidator(NetRecvValidator * value);

    /** \brief Retorna objeto para acesso às estatísticas de pacotes recebidos
     *  \return Referência para o objeto com as estatísticas atuais
     */
    NetStatistics & getStatistics();

    /** \brief Retorna o tipo dos dados que a net deve receber
     */
    NetType getType();

    /** \brief Envia um report IGMP para o grupo multicast de onde está recebendo dados
     *  \return E_OK em caso de sucesso ou E_ERROR em caso de erro
     */
    int sendSingleIGMPReport();

    uint16_t getSessionId();

    void setSessionId(uint16_t value);
};

#endif
