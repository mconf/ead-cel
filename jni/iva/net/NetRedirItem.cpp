#include <CommonLeaks.h>
#include "NetRedirItem.h"
#include <CommonLeaksCpp.h>

NetRedirItem::NetRedirItem(int id, bool enabled, const IPv4& ipv4,
                           unsigned int port) :
    _id(id), _enabled(enabled), _port(port), _ipv4(ipv4)
{
    _OpenSocket();
}

NetRedirItem::~NetRedirItem()
{
    _CloseSocket();
}

void NetRedirItem::_OpenSocket()
{
    _socketSend.openAsSender(_ipv4.getString(), _port, false);
}

void NetRedirItem::_CloseSocket()
{
    _socketSend.close();
}

int NetRedirItem::getId() const
{
    return _id;
}

bool NetRedirItem::getEnabled() const
{
    return _enabled;
}

bool NetRedirItem::getMulticast() const
{
    return (_ipv4.getType() == IPv4::TYPE_MULTICAST);
}

unsigned int NetRedirItem::getPort() const
{
    return _port;
}

const IPv4& NetRedirItem::getIp() const
{
    return _ipv4;
}

void NetRedirItem::setId(int value)
{
    _id = value;
}

void NetRedirItem::setEnabled(bool value)
{
    _enabled = value;
}

void NetRedirItem::setPort(unsigned int value)
{
    _port = value;
    _CloseSocket();
    _OpenSocket();
}

void NetRedirItem::setIp(const IPv4& value)
{
    _ipv4 = value;
    _CloseSocket();
    _OpenSocket();
}

int NetRedirItem::send(NetPacket * packet)
{
    int ret = 0;
    if (packet && packet->getPayloadSize() > 0) {
        ret = _socketSend.send((const char *)packet->getBufferPointer(),
                               packet->getSize());
    }
    return ret;
}


