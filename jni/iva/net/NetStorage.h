#ifndef _NET_STORAGE_H_
#define _NET_STORAGE_H_

#include "netDefs.h"
#include <Mutex.h>
#include <queue.h>
#include <Thread.h>
#include "NetPacket.h"
#include "NetQueue.h"
#include "NetQueueItem.h"
#include "NetStatistics.h"

/** \brief Estrutura de armazenamento dos dados recebidos na net
 *
 * A NetStorage é utilizada para gerenciar os pacotes que são recebidos na net.
 * Ela é utilizada principalmente para unir frames fragmentados para envio e para
 * ordenar os pacotes que chegam.
 * Dados são armazenados como frames, não como pacotes. Ou seja, se um frame
 * foi fragmentado em vários pacotes para envio, esses pacotes são unidos em um
 * só item aqui na NetStorage.
 */
class NetStorage
{
public:
    static const int KILLER_WAIT_TIME = 20;     ///< Tempo (em ms) que a thread killer dorme após cada execução
    static const int CLEAR_THRESHOLD  = 6;      /**< Limite de números de sequência fora de ordem para dar um
                                                     clear() na fila de pacotes */

private:
    NetQueue * _packetQueue;
    queue_t * _queue;
    Mutex _mutex;
    unsigned int _executionCont;
    NetStatistics * _stats;
    Thread<NetStorage> * _killerThread;
    bool _killerRunning;
    unsigned int _packWait;

    int _Enqueue(NetQueueItem * item);
    bool _RemoveAllCompleted(bool lock = true);

    /** \brief Thread que retira os pacotes incompletos da queue
     */
    void * _Killer(void * arg);

public:
    NetStorage(queue_t * queue, int killerMaxWait);
    ~NetStorage();

    /** \brief Associa um objeto para controle de estatísticas na storage
     *  \param value Objeto NetStatistics a ser utilizado
     *
     * É armazenado apenas o ponteiro para o objeto. Se não for setado nenhum objeto,
     * as estatísticas não serão controladas.
     */
    void setStatistics(NetStatistics * value);

    /** \brief Adiciona um pacote na lista da NetStorage
     *  \param packet Pacote a ser adicionado na lista
     */
    int add(NetPacket * packet);

    int size();

    int clear();

    int start();

    int stop();
};

#endif
