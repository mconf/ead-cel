#include <CommonLeaks.h>
#include <cmath>
#include "netDefs.h"
#include "NetQueueItem.h"
#include <CommonLeaksCpp.h>

NetQueueItem::NetQueueItem() :
    _fragCount(0), _data(NULL), _dataSize(0), _fragSize(0)
{
    _Clear();
}

NetQueueItem::NetQueueItem(unsigned int frameSize, int fragSize) :
    _fragCount(0), _data(NULL), _dataSize(0), _fragSize(0)
{
    allocData(frameSize, fragSize);
}

NetQueueItem::~NetQueueItem()
{
    deallocData();
}

int NetQueueItem::allocData(unsigned int frameSize, int fragSize)
{
    deallocData();

    _dataSize = frameSize;
    if (_dataSize > 0) {
        _data = new unsigned char[_dataSize];
    } else {
        _data = NULL;
    }

    // conforme o número de fragmentos que o frame tem
    _fragSize = fragSize;
    if (_fragSize > 0) {
        float aux = _dataSize / (float)_fragSize;
        _fragCount = (int)floor(aux);
        if (aux - _fragCount > 0) { // se não foi divisão exata, tem um fragmento menor no final
            _fragCount++;
        }
    } else {
        _fragCount = 1;
    }
    _fragList = vector<char>(_fragCount, false);

    _Clear();
    return E_OK;
}

int NetQueueItem::deallocData()
{
    if (_data) {
        _fragCount = 0;
        _dataSize = 0;
        delete _data;
        _data = NULL;
        _Clear();
    }
    return E_OK;
}

void NetQueueItem::_Clear()
{
    setArriveTime(Interval(0, 0));
    setSequenceNumber(0);
    setTimestamp(Interval(0, 0));
    setTotalReceived(0);
    setExtraData(NULL);
    _status = FREE;
    _fragList = vector<char>(_fragCount, false);
}

unsigned int NetQueueItem::getDataSize()
{
    return _dataSize;
}

net_seqnum_t NetQueueItem::getSequenceNumber()
{
    return _seqnum;
}

const Interval NetQueueItem::getTimestamp()
{
    return _timestamp;
}

const Interval NetQueueItem::getArriveTime()
{
    return _arriveTime;
}

unsigned int NetQueueItem::getTotalReceived()
{
    return _totalReceived;
}

QueueExtraData * NetQueueItem::getExtraData()
{
    return _extraData;
}

NetQueueItem::NetQueueItemStatus NetQueueItem::getStatus()
{
    return _status;
}

string NetQueueItem::getFragListStr()
{
    stringstream ret;
    ret << _fragList.size() << " (";
    vector<char>::iterator it;
    for (it = _fragList.begin(); it != _fragList.end(); ++it) {
        if (it != _fragList.begin()) {
            ret << ",";
        }
        if (*it) {
            ret << "1";
        } else {
            ret << "0";
        }
    }
    ret << ")";
    return ret.str();
}

void NetQueueItem::setSequenceNumber(net_seqnum_t value)
{
    _seqnum = value;
}

void NetQueueItem::setTimestamp(const Interval &value)
{
    _timestamp = value;
}

void NetQueueItem::setArriveTime(const Interval &value)
{
    _arriveTime = value;
}

void NetQueueItem::setTotalReceived(unsigned int value)
{
    _totalReceived = value;
}

void NetQueueItem::setExtraData(QueueExtraData * value)
{
    _extraData = value;
}

unsigned char * NetQueueItem::getData()
{
    return _data;
}

bool NetQueueItem::isComplete()
{
    // pra garantir que existem dados no buffer
    if (_status != BUSY) {
        return false;
    }

    // vai em ordem reversa pois é mais fácil achar um false no fim
    vector<char>::reverse_iterator it;
    for (it = _fragList.rbegin(); it != _fragList.rend(); ++it) {
        if (!(*it)) {
            return false;
        }
    }
    return true;
}

int NetQueueItem::insertData(unsigned char * data, unsigned int size, int fragNum)
{
    // verifica se os dados cabem no buffer
    int jump = fragNum * _fragSize;
    if (jump + size > _dataSize) {
        return E_ERROR;
    }

    // controle de fragmentos duplicados
    if (_fragList[fragNum]) {
        return E_NET_FRAG_ALREADY_RECEIVED;
    }
    _fragList[fragNum] = true;

    // copia dados pro buffer
    _status = BUSY;

    // _data pode ser nulo quando recebe pacotes sem dados, apenas com cabeçalho
    if (_data && size) {
        memcpy(_data + jump, data, size);
    }

    return E_OK;
}



