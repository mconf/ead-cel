#include <CommonLeaks.h>
#include "NetRedir.h"
#include <CommonLeaksCpp.h>

NetRedir::NetRedir()
{
    _lastId = -1;
}

NetRedir::~NetRedir()
{
}

int NetRedir::_NextId()
{
    _lastId++;
    if (_lastId >= INT_MAX) {
        _lastId = 0;
    }
    return _lastId;
}

NetRedirItem * NetRedir::add(IPv4 &ip, unsigned int port)
{
    _mutex.lock();

    // cria o novo item
    NetRedirItem * item;
    item = new NetRedirItem(_NextId(), false, ip, port);

    // adiciona ele na lista
    pair<int, NetRedirItem *> elem(item->getId(), item);
    pair<map<int, NetRedirItem *>::iterator, bool> ret;
    ret = _redirs.insert(elem);

    _mutex.unlock();

    // segundo elemento do retorno da insert() indica se o item foi inserido ou se já existia
    if (ret.second) {
        return item;
    } else {
        return NULL;
    }
}

NetRedirItem * NetRedir::get(int id)
{
    return _redirs[id];
}

int NetRedir::remove(NetRedirItem * item)
{
    if (item) {
        return remove(item->getId());
    } else {
        return E_ERROR;
    }
}

int NetRedir::remove(int id)
{
    // monta o índice e tenta remover o elemento
    _mutex.lock();
    NetRedirItem * item = get(id);
    int ret = _redirs.erase(id);
    if (item)
        delete item;
    _mutex.unlock();

    // erase retorna o número de elementos removidos ou 0 se não encontrou ele
    if (ret) {
        return E_OK;
    } else {
        return E_ERROR;
    }
}

int NetRedir::removeAll()
{
    _mutex.lock();
    map<int, NetRedirItem *>::iterator it;
    for (it = _redirs.begin(); it != _redirs.end(); ++it) {
        NetRedirItem * item = (*it).second;
        delete item;
    }
    _redirs.clear();
    _mutex.unlock();

    return E_OK;
}

int NetRedir::_SetEnabled(int id, bool value)
{
    int ret = E_ERROR;

    _mutex.lock();
    NetRedirItem * item = _redirs[id];
    if (item) {
        item->setEnabled(value);
        ret = E_OK;
    }
    _mutex.unlock();

    return ret;
}

int NetRedir::enable(NetRedirItem * item)
{
    if (item) {
        return enable(item->getId());
    } else {
        return E_ERROR;
    }
}

int NetRedir::enable(int id)
{
    return _SetEnabled(id, true);
}

int NetRedir::disable(NetRedirItem * item)
{
    if (item) {
        return disable(item->getId());
    } else {
        return E_ERROR;
    }
}

int NetRedir::disable(int id)
{
    return _SetEnabled(id, false);
}

int NetRedir::enableAll()
{
    _mutex.lock();
    map<int, NetRedirItem *>::iterator it;
    for (it = _redirs.begin(); it != _redirs.end(); ++it) {
        NetRedirItem * item = (*it).second;
        item->setEnabled(true);
    }
    _mutex.unlock();
    return E_OK;
}

int NetRedir::disableAll()
{
    _mutex.lock();
    map<int, NetRedirItem *>::iterator it;
    for (it = _redirs.begin(); it != _redirs.end(); ++it) {
        NetRedirItem * item = (*it).second;
        item->setEnabled(false);
    }
    _mutex.unlock();
    return E_OK;
}

int NetRedir::send(NetPacket * packet)
{
    int ret = 0;

    _mutex.lock();
    map<int, NetRedirItem *>::iterator it;
    for (it = _redirs.begin(); it != _redirs.end(); ++it) {
        NetRedirItem * item = (*it).second;
        if (item->getEnabled()) {
            ret += item->send(packet);
        }
    }
    _mutex.unlock();

    return ret;
}

