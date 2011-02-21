#ifndef _NET_QUEUE_H_
#define _NET_QUEUE_H_

#include "netDefs.h"
#include <deque>
#include <Mutex.h>
#include <queue.h>
#include "NetQueueItem.h"
#include "NetPacket.h"
#include "QueueExtraData.h"

using namespace std;

/** \brief Fila de frames recebidos
 *
 * Fila para armazenar os frames recebidos na net. É útil para controlar frames fragmentados
 * em diversos pacotes, duplicação de pacotes e frames fora de ordem, principalmente.
 *
 * Mantém os dados organizados por ordem de seqnum. Quando é feito um enqueue(), se o frame ainda
 * não existe na queue ele é criado. O seqnum deste frame entra em uma das condições abaixo:
 *  - seqnum é +1 do último seqnum da queue: insere o frame como último da queue
 *  - seqnum é menor que o primeiro da queue: ignora, não insere na queue
 *  - seqnum é +n do último seqnum da queue (n > 1): insere (n-1) frame vazios na queue e então
 *    insere o novo frame. Faz isso para manter a ordem por seqnum. Só insere se couber no tamanho
 *    máximo.
 *
 */
class NetQueue
{
public:
    static const int DEFAULT_MAX_SIZE = 30;     ///< Tamanho máximo default para a queue

private:
    deque<NetQueueItem *> _list;
    int _maxSize;
    Mutex _mutex;
    int _lastId;
    int _lateCount;
    int _earlyCount;

    int _GetItemIndex(net_seqnum_t seqnum);
    int _Insert(NetQueueItem * item);
    void _InsertEmptyItems(int lastIndex);
    bool _CanBeInserted(int index);
    void _DeleteItem(NetQueueItem * item);

public:
    /** \brief Construtor padrão onde é especificado o número máximo de frames na queue
     *  \param maxSize Número máximo de elementos (frames). Se -1, queue fica com tamanho
     *         infinito.
     */
    NetQueue(int maxSize = DEFAULT_MAX_SIZE);
    ~NetQueue();

    /** \brief Adiciona um elemento na queue
     *  \param packet Pacote recebido na net que será inserido na queue
     *  \return Objeto com o item adicionado na queue ou NULL se não foi inserido
     *
     * O pacote é inserido na queue ordenado pelo seu número de sequência.
     * Se o número de sequência já existe na queue, é porque este pacote
     * é parte de um frame que foi fragmentado. Então insere os dados do pacote
     * no item já existente da queue, na posição correta do buffer (conforme o
     * número de fragmento do pacote).
     * Função retorna NULL se o pacote não pode ser inserido (seu número de sequência
     * não encaixa nas posições disponíveis da queue).
     */
    NetQueueItem * enqueue(NetPacket * packet);

    /** \brief Remove o primeiro elemento da queue e o destrói
     *
     *  O elemento é destruído e removido da queue. Para acessá-lo, usar a função first() antes
     *  de usar essa função.
     */
    void dequeue();

    unsigned int size();
    bool isFull();
    bool isEmpty();
    NetQueueItem * first();
    NetQueueItem * last();
    void clear();
    int getEarlyCount();
    int getLateCount();
};

#endif

