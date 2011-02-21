#ifndef _NET_SEND_H_
#define _NET_SEND_H_

#include "netDefs.h"
#include <queue.h>
#include <Mutex.h>
#include <Thread.h>
#include <SocketUDP.h>
#include "NetPacket.h"
#include "NetStatistics.h"

/** \brief Classe para envio de dados pela rede
 *
 */
class NetSend
{
private:
    SocketUDP _socket;                      ///< Socket usado para enviar os dados
    NetType _contentType;                   ///< Tipo de conteúdo que esta netrecv está recebendo
    NetStatistics _stats;                   ///< Objeto com as estatísticas da NetSend
    Mutex _mutex;                           ///< Mutex para controle geral da NetSend
    Thread<NetSend> * _thread;              ///< Thread para envio dos pacotes
    bool _threadRun;                        ///< Flag de controle sobre a '_thread'
    queue_t * _queue;                       ///< Fila de onde são retirados os dados que serão enviados
    net_seqnum_t _seqnum;                   ///< Objeto para controle do número de sequência dos pacotes
    uint16_t _sessionId;                    ///< Identificador da sessão

    void _FillDefaultPacket(NetPacket * packet, uint32_t dataSize, uint32_t frameSize,
                            uint32_t timestamp, uint16_t seqnum, QueueExtraData * extraData);
    int _SendPacket(NetPacket * packet);

    void * _SendThread(void *);
public:
    NetSend(NetType type, queue_t * queue, uint16_t sessionId = 0);
    ~NetSend();

    int start(const IPv4 &ip, unsigned int port);
    int stop();

    NetStatistics * getStatistics();
    NetType getType();

    uint16_t getSessionId();
    void setSessionId(uint16_t value);

};

#endif
