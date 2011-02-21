#include <CommonLeaks.h>
#include "netDefs.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include "NetHeader.h"
#include "NetHeaderAttr.h"
#include <CommonLeaksCpp.h>

NetHeader::NetHeader() : _headerSize(0), _buffer(NULL)
{
    // cria a lista padrão de atributos, por enquanto todos sem apontar pra nada
    _CreateAttribute(ATTR_SIGN, 2);
    _CreateAttribute(ATTR_TYPE, 6);
    _CreateAttribute(ATTR_FRAMESIZE, 24);
    _CreateAttribute(ATTR_SEQNUM, 16);
    _CreateAttribute(ATTR_FRAGNUM, 16);
    _CreateAttribute(ATTR_TIMESTAMP, 32);
    _CreateAttribute(ATTR_SESSION_ID, 16);
    _CreateAttribute(ATTR_NULL, 16);
}

NetHeader::~NetHeader()
{
    map<int, NetHeaderAttr *>::iterator it;
    for (it = _attrs.begin(); it != _attrs.end(); ++it) {
        NetHeaderAttr * attr = (*it).second;
        if (attr) {
            delete attr;
        }
    }
    _attrs.clear();
}

NetType NetHeader::getType()
{
    return NET_TYPE_NONE;
}

void NetHeader::_SetDefaultAttrs()
{
    //uint8_t type = ((uint8_t)NET_TYPE_NONE << 2) >> 2; // pra garantir que só tem 6 bits
    //setAttrAsInt(NetHeader::ATTR_TYPE, ((uint8_t)ATTR_TYPE_SIGN << 6) | type);
    setAttrAsInt(NetHeader::ATTR_SIGN, IVA_SIGN);
    setAttrAsInt(NetHeader::ATTR_TYPE, getType());
}

void NetHeader::clear()
{
    // varre os atributos zerando o buffer deles
    map<int, NetHeaderAttr *>::iterator it;
    for (it = _attrs.begin(); it != _attrs.end(); ++it) {
        NetHeaderAttr * attr = (*it).second;
        attr->setData(_buffer, 0);
    }
    _SetDefaultAttrs();
}

void NetHeader::_CreateAttribute(int id, unsigned int size)
{
    _attrs[id] = new NetHeaderAttr(size, _headerSize);
    _headerSize += size; // tamanho em BITS
}

int NetHeader::getSize()
{
    return (int)ceil((double)_headerSize / 8);
}

int NetHeader::_SetBuffer(unsigned char * buffer)
{
    _buffer = buffer;
    if (_buffer) {
        _SetDefaultAttrs();
    }
    return E_OK;
}

int NetHeader::unsetBuffer()
{
    return _SetBuffer(NULL);
}

int NetHeader::setBuffer(unsigned char * buffer, unsigned int bufferSize)
{
    // para tentar garantir que o buffer de entrada é grande o suficiente pro header
    // se buffer é NULL
    if (bufferSize < (unsigned int)getSize()) {
        return E_ERROR;
    }
    return _SetBuffer(buffer);
}

NetHeaderAttr * NetHeader::getAttr(int id)
{
    return _attrs[id];
}

uint32_t NetHeader::getAttrAsInt(int id)
{
    uint32_t ret = 0;
    NetHeaderAttr * attr = getAttr(id);
    if (attr) {
        ret = attr->getData(_buffer);
    }
    return ret;
}
/*
void NetHeader::setAttr(int id, unsigned char * value)
{
    NetHeaderAttr * attr = getAttr(id);
    if (attr) {
        attr->copyData(_buffer, value);
    }
}
*/
void NetHeader::setAttrAsInt(int id, uint32_t value)
{
    NetHeaderAttr * attr = getAttr(id);
    if (attr) {
        attr->setData(_buffer, value);
    }
}

bool NetHeader::hasAttr(int id)
{
    NetHeaderAttr * attr = getAttr(id);
    return (attr != NULL);
}

QueueExtraData * NetHeader::createExtraData()
{
    return NULL;
}

int NetHeader::setExtraData(QueueExtraData * extra)
{
    return E_OK;
}

void NetHeader::print()
{
    unsigned int max = 1 << 31, i, words, b, bit = 0;
    int count;

    LogData log;

    if (_buffer) {
        words = (unsigned int)ceil(_headerSize / 32.0);
        for (b = 0; b < words; b++) {
            uint32_t data;
            memcpy(&data, _buffer + (4*b), 4);
            count = 0;
            for (i = max; i > 0 && bit < _headerSize; i /= 2) {
                if (data & i) log << "1";
                else log << "0";
                count++;
                if (count == 4) {
                    log << ".";
                } else if (count == 8) {
                    log << " ";
                    count = 0;
                }
                bit++;
            }
            log << endl;
        }
        log << endl;
    }

    log.push();
}
/*
void NetHeader::print()
{
    unsigned int i, bytes;
    uint8_t max = 1 << 7;
    int count, bit = 0;
    uint32_t data;

    if (_buffer) {
        bytes = (unsigned int)ceil(_headerSize / 8.0);
        for (int b = 0; b < bytes; b++) {
            if (b && b % 4 == 0) {
                cout << endl;
            }
            memcpy(&data, _buffer + b, 1);
            count = 0;
            for (i = max; i > 0 && bit < _headerSize; i /= 2) {
                if (data & i) cout << "1";
                else cout << "0";
                count++;
                if (count == 4) {
                    cout << ".";
                }
                bit++;
            }
            cout << " ";
        }
        cout << endl << endl;
    }
}

*/

