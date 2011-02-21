#include <CommonLeaks.h>
#include <QueueExtraDataAudio.h>
#include <QueueExtraDataVideo.h>
#include "netDefs.h"
#include "NetPacket.h"
#include <CommonLeaksCpp.h>

NetPacket::NetPacket(NetType type)
{
    _type = type;
    _buffer = NULL;
    _payloadPt = NULL;
    _payloadSize = 0;

    if (_type == NET_TYPE_AUDIO) {
        _header = new NetHeaderAudio();
    } else if (type == NET_TYPE_VIDEO) {
        _header = new NetHeaderVideo();
    } else {
        throw E_NET_INVALID_TYPE;
    }
}

NetPacket::~NetPacket()
{
    delete _header;
    _header = NULL;
    deallocBuffer();
}

int NetPacket::allocBuffer(unsigned int payloadSize)
{
    deallocBuffer();

    // aloca o novo buffer 
    int headerSize = _header->getSize();
    //_buffer = new unsigned char[headerSize + payloadSize];
    _buffer = (unsigned char *)malloc(sizeof(unsigned char) *
                                      (headerSize + payloadSize));
    //memset(_buffer, 0, headerSize + payloadSize);

    // calcula o novo tamanho e ponteiro do data
    _payloadSize = payloadSize;
    _payloadPt = _buffer + headerSize;

    // seta o buffer no header para arrumar os ponteiros dos atributos
    _header->setBuffer(_buffer, (headerSize + payloadSize));

    return E_OK;
}

int NetPacket::allocBuffer(unsigned char * payloadBuffer, unsigned int payloadSize)
{
    int ret;
    ret = allocBuffer(payloadSize);
    if (ret == E_OK && payloadSize > 0) {
        copyPayload(payloadBuffer, payloadSize);
    }
    return ret;
}

int NetPacket::deallocBuffer()
{
    // remove o buffer no header para limpar os ponteiros dos atributos
    if (_header) {
        _header->unsetBuffer();
    }

    // calcula o novo tamanho e ponteiro do data
    _payloadPt = NULL;
    _payloadSize = 0;

    if (_buffer) {
        //delete _buffer;
        free(_buffer);
        _buffer = NULL;
    }

    return E_OK;
}

int NetPacket::copyPayload(unsigned char * data, unsigned int dataSize)
{
    if (_payloadPt && dataSize > 0) {
        memcpy(_payloadPt, data, dataSize);
        return E_OK;
    }
    return E_ERROR;
}

unsigned char * NetPacket::getBufferPointer()
{
    return _buffer;
}

unsigned int NetPacket::getSize()
{
    return _payloadSize + _header->getSize();
}

unsigned int NetPacket::getPayloadSize()
{
    return _payloadSize;
}

void NetPacket::setPayloadSize(unsigned int value)
{
    _payloadSize = value;
}

unsigned char * NetPacket::getPayloadPointer()
{
    return _payloadPt;
}

NetHeader * NetPacket::getHeader()
{
    return _header;
}

