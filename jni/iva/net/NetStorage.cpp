#include <CommonLeaks.h>
#include "NetStorage.h"
#include <CommonLeaksCpp.h>

NetStorage::NetStorage(queue_t * queue, int killerMaxWait) :
    _stats(NULL), _queue(queue), _packWait(killerMaxWait),
    _killerThread(NULL)
{
    _packetQueue = new NetQueue();
}

NetStorage::~NetStorage()
{
    stop();
    delete _packetQueue;
}

void NetStorage::setStatistics(NetStatistics * value)
{
    _stats = value;
}

bool NetStorage::_RemoveAllCompleted(bool lock)
{
    NetQueueItem * item;
    bool ret = false;

    if (lock) _mutex.lock();
    item = _packetQueue->first();
    while (item && item->isComplete()) {
        if (_stats) { /// \todo Está contabilizando mesmo se dataSize==0
            _stats->increment(NetStatistics::ATTR_RECEIVED_FRAMES);
        }
        _Enqueue(item);
        _packetQueue->dequeue();
        item = _packetQueue->first();
        ret = true;
    }
    if (lock) _mutex.unlock();
    return ret;
}

int NetStorage::_Enqueue(NetQueueItem *item)
{
    unsigned char * buffer;
    int ret;
    Milliseconds ts = item->getTimestamp();

    if (item->getTotalReceived()) {
        buffer = (unsigned char*)queue_malloc(item->getTotalReceived());
        memcpy(buffer, item->getData(), item->getTotalReceived());
        ret = queue_enqueue(_queue, buffer, item->getTotalReceived(), ts.getTime(),
                            item->getExtraData());
        if (ret != E_OK) {
            queue_dealloc(buffer);
        }
    } else { // pode não ter recebido dados, apenas um cabeçalho
        ret = queue_enqueue(_queue, NULL, 0, ts.getTime(), item->getExtraData());
    }

    return ret;
}

int NetStorage::add(NetPacket *packet)
{
    NetQueueItem * queueItem;
    int ret = E_OK;

    _mutex.lock();
    queueItem = _packetQueue->enqueue(packet);
    if (queueItem) {
        _RemoveAllCompleted(false);
    } else {
        if (_packetQueue->getEarlyCount() > CLEAR_THRESHOLD ||
            _packetQueue->getLateCount() > CLEAR_THRESHOLD) {
                _packetQueue->clear();
        }
        ret = E_ERROR;
    }
    _mutex.unlock();

    return ret;
}

int NetStorage::clear()
{
    _mutex.lock();
    _packetQueue->clear();
    _mutex.unlock();

    return E_OK;
}

int NetStorage::start()
{
    _mutex.lock();
    _killerRunning = true;
    _killerThread = new Thread<NetStorage>(this, &NetStorage::_Killer);
    _killerThread->run(NULL, true);
    _mutex.unlock();

    return E_OK;
}

int NetStorage::stop()
{
    _mutex.lock();
    _killerRunning = false;
    if (_killerThread && _killerThread->isRunning()) {
        _killerThread->join(NULL);
    }
    delete _killerThread;
    _killerThread = NULL;
    _mutex.unlock();

    return E_OK;
}

int NetStorage::size()
{
    return _packetQueue->size();
}

void * NetStorage::_Killer(void *arg)
{
    Milliseconds ts, tsDiff;
    bool discarded;
    NetQueueItem * item;
    unsigned int bytesReceived = 0;

    _executionCont = 0;

    while (_killerRunning) {
        _executionCont++;

        _mutex.lock();

        // primeiro limpa todos completos
        if (!_packetQueue->isEmpty()) {
            _RemoveAllCompleted(false);
        }

        // verifica se os frames estão muito atrasados e os descarta
        discarded = true;
        while (!_packetQueue->isEmpty() && discarded) {
            item = _packetQueue->first();
            ts.setTimestamp();
            tsDiff = ts - item->getArriveTime();
            if ((unsigned int)tsDiff.getTime() > _packWait && !item->isComplete()) {
                if (_stats) {
                    _stats->increment(NetStatistics::ATTR_DISCARDED_FRAMES);
                    _stats->increment(NetStatistics::ATTR_DISCARDED_BYTES,
                                      item->getTotalReceived());
                }
                //item->setStatus(NetQueueItem::FREE);
                _packetQueue->dequeue();
                discarded = true; // se descartou frame, marca true pra continuar no loop
            } else {
                discarded = false;
            }
        }

        _mutex.unlock();

        Milliseconds(NetStorage::KILLER_WAIT_TIME).sleep();
    }
    return NULL;
}

