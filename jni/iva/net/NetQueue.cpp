#include <CommonLeaks.h>
#include <cmath>
#include "netDefs.h"
#include "NetQueue.h"
#include <CommonLeaksCpp.h>

NetQueue::NetQueue(int maxSize)
{
    if (maxSize <= 0) {
        maxSize = DEFAULT_MAX_SIZE;
    } else {
        _maxSize = maxSize;
    }
    _lastId = -1;
    _lateCount = 0;
    _earlyCount = 0;
}

NetQueue::~NetQueue()
{
    // remove todos elementos da lista
    clear();
}

bool NetQueue::_CanBeInserted(int index)
{
    if (isEmpty()) {
        return true;
    }
    return (index <= _maxSize); // se cabe no limite estipulado pode ser inserido
}

int NetQueue::_GetItemIndex(net_seqnum_t seqnum)
{
    int index = -1;

    if (_lastId == -1) {
        return 0;
    }

    index = seqnum - _lastId + size() - 1;

    // < 0 e pq ta muito atrasado e >= _maxSize esta muito adiantado -- nao aceita nenhum caso
    if (index < 0) { 
        index = -1;
        _lateCount++;
    } else if (index >= _maxSize) {
        index = -1;
        _earlyCount++;
    } else {
        _earlyCount = 0;
        _lateCount = 0;
    }

    return index;
}

bool NetQueue::isEmpty()
{
    return (_list.size() == 0);
}

bool NetQueue::isFull()
{
    return (_maxSize != -1) && (_list.size() == _maxSize);
}

NetQueueItem * NetQueue::first()
{
    if (!isEmpty()) {
        return _list.front();
    } else {
        return NULL;
    }
}

NetQueueItem * NetQueue::last()
{
    if (!isEmpty()) {
        return _list.back();
    } else {
        return NULL;
    }
}

unsigned int NetQueue::size()
{
    return _list.size();
}

void NetQueue::_DeleteItem(NetQueueItem * item)
{
    if (item) {
        QueueExtraData * extra = item->getExtraData();
        if (extra) {
            delete extra;
        }
        delete item;
    }
}

void NetQueue::dequeue()
{
    if (!isEmpty()) {
        _mutex.lock();
        NetQueueItem * item = _list.front();
        _DeleteItem(item);
        _list.pop_front();
        _mutex.unlock();
    }
}

void NetQueue::clear()
{
    _mutex.lock();
    deque<NetQueueItem *>::iterator it;
    for (it = _list.begin(); it != _list.end(); ++it) {
        _DeleteItem(*it);
    }
    _list.clear();
    _lastId = -1;
    _lateCount = 0;
    _earlyCount = 0;
    _mutex.unlock();
}

int NetQueue::_Insert(NetQueueItem * item)
{
    _list.push_back(item);
    _lastId = item->getSequenceNumber();
    // se estourou o tamanho máximo, remove o primeiro item
    if (_list.size() > (unsigned int)_maxSize) {
        NetQueueItem * item = _list.front();
        _list.pop_front();
        delete item;
    }
    return E_OK;
}

void NetQueue::_InsertEmptyItems(int lastIndex)
{
    NetQueueItem * item;
    Milliseconds ts;

    if (lastIndex < (long)size()) return; // já estão todos inseridos

    // cria os itens necessários e os insere na lista da queue
    for (int i = size(); i <= lastIndex; i++) {
        item = new NetQueueItem();
        ts.setTimestamp();
        item->setArriveTime(ts);
        _Insert(item);
    }
}

int NetQueue::getEarlyCount()
{
    return _earlyCount;
}

int NetQueue::getLateCount()
{
    return _lateCount;
}

NetQueueItem * NetQueue::enqueue(NetPacket * packet)
{
    Milliseconds ts;
    int index;
    net_seqnum_t seqnum;
    NetQueueItem * item = NULL;

    if (!packet) return NULL;

    _mutex.lock();

    // pega o índice onde este item está na lista ou onde deve ser inserido
    seqnum = (net_seqnum_t)packet->getHeader()->getAttrAsInt(NetHeader::ATTR_SEQNUM);
    index = _GetItemIndex(seqnum);

    if (index >= 0) { // < 0 indica que e pra ignorar o pacote

        NetHeader * header = packet->getHeader();
        uint32_t fragSize = NetPacket::DEFAULT_PACKSIZE - packet->getHeader()->getSize();
        uint32_t frameSize = header->getAttrAsInt(NetHeader::ATTR_FRAMESIZE);
        if (fragSize > frameSize) {
            fragSize = frameSize;
        }
        ts.setTimestamp();

        // item já está na lista
        if ((unsigned int)index < size()) {
            item = _list[index];

            // se o item ainda não foi alocado (se é o primeiro fragmento deste frame)
            if (!item->getData()) {
                item->allocData(frameSize, fragSize);
                item->setExtraData(packet->getHeader()->createExtraData());
                item->setSequenceNumber(seqnum);
                item->setTimestamp(
                    Milliseconds(header->getAttrAsInt(NetHeader::ATTR_TIMESTAMP))
                    );
            }

            // atualiza o restante dos dados desse frame
            item->setArriveTime(ts);
            item->setTotalReceived(packet->getPayloadSize() + item->getTotalReceived());
            if (!item->getExtraData()) { // cria os dados extra se ainda não tinha
                item->setExtraData(packet->getHeader()->createExtraData());
            }
            item->insertData(packet->getPayloadPointer(), packet->getPayloadSize(),
                             packet->getHeader()->getAttrAsInt(NetHeader::ATTR_FRAGNUM));

        // item não está na lista ainda
        } else {

            // primeiro insere elementos até a posição desejada caso falte algum
            _InsertEmptyItems(index - 1);

            // cria o item alvo
            item = new NetQueueItem(frameSize, fragSize);
            item->setArriveTime(ts);
            item->setTotalReceived(packet->getPayloadSize());
            item->setExtraData(packet->getHeader()->createExtraData());
            item->setSequenceNumber(seqnum);
            item->setTimestamp(
                Milliseconds(header->getAttrAsInt(NetHeader::ATTR_TIMESTAMP))
                );
            item->insertData(packet->getPayloadPointer(), packet->getPayloadSize(),
                             packet->getHeader()->getAttrAsInt(NetHeader::ATTR_FRAGNUM));

            _Insert(item); // insere item na lista da queue
        }
    }

    _mutex.unlock();

    return item;
}

