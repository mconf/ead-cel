#include <CommonLeaks.h>
#include <SocketUDP.h>
#include "NetSend.h"
#include <CommonLeaksCpp.h>

NetSend::NetSend(NetType type, queue_t * queue,
                 uint16_t sessionId):
    _queue(queue), _contentType(type), _seqnum(0),
    _thread(NULL), _threadRun(false), _sessionId(sessionId)
{
    // valida os tipos suportados
    if (_contentType != NET_TYPE_AUDIO &&
        _contentType != NET_TYPE_VIDEO) {
            throw E_NET_INVALID_TYPE;
    }
}

NetSend::~NetSend()
{
    stop();
}

NetStatistics * NetSend::getStatistics()
{
    return &_stats;
}

NetType NetSend::getType()
{
    return _contentType;
}

uint16_t NetSend::getSessionId()
{
    return _sessionId;
}

void NetSend::setSessionId(uint16_t value)
{
    _sessionId = value;
}

int NetSend::start(const IPv4 &ip, unsigned int port)
{
    stop();

    _mutex.lock();

    // abre o socket como transmissor
    int ret = _socket.openAsSender(ip.getString(), port, false);
    if (ret != E_OK) {
        _mutex.unlock();
        return ret;
    }

    // cria a thread de envio
    _threadRun = true;
    _thread = new Thread<NetSend>(this, &NetSend::_SendThread);
    _thread->run(NULL, true);

    _mutex.unlock();

    return E_OK;
}

int NetSend::stop()
{
    _mutex.lock();

    // para a thread de envio
    if (_thread) {
        _threadRun = false;
        queue_broadcast(_queue);
        if (_thread->isRunning()) {
            _thread->join(NULL);
        }
        delete _thread;
        _thread = NULL;
    }
    // finaliza o socket
    _socket.close();

    _mutex.unlock();

    return E_OK;
}

void NetSend::_FillDefaultPacket(NetPacket * packet, uint32_t dataSize, uint32_t frameSize,
                                 uint32_t timestamp, uint16_t seqnum, QueueExtraData * extraData)
{
    packet->allocBuffer(dataSize);
    NetHeader * header = packet->getHeader();
    header->clear();
    header->setAttrAsInt(NetHeader::ATTR_TYPE, _contentType);
    header->setAttrAsInt(NetHeader::ATTR_SEQNUM, seqnum);
    header->setAttrAsInt(NetHeader::ATTR_TIMESTAMP, timestamp);
    header->setAttrAsInt(NetHeader::ATTR_FRAMESIZE, frameSize);
    header->setAttrAsInt(NetHeader::ATTR_SESSION_ID, _sessionId);
    header->setAttrAsInt(NetHeader::ATTR_NULL, 0);
    header->setExtraData(extraData); // configura os dados adicionais de áudio, ou vídeo, etc.
}

int NetSend::_SendPacket(NetPacket * packet)
{
    int ret = _socket.send((const char *)packet->getBufferPointer(), packet->getSize());
    if (ret > 0) {
        _stats.increment(NetStatistics::ATTR_SENT_PACKETS);
        _stats.increment(NetStatistics::ATTR_SENT_BYTES, ret);
    }
    return ret;
}

void * NetSend::_SendThread(void *)
{
    int ret;
    NetPacket * packet;
    queue_consumer_t * consumer;
    uint8_t * buffer;
    uint32_t bufferSize, timestamp;
    QueueExtraData * extraData;
    int bufferSent;
    int fragment;

    consumer = queue_registerConsumer(_queue);

    while (_threadRun) {

        ret = queue_dequeueCond(consumer, &buffer, &bufferSize, &timestamp, &extraData);
        if (ret != E_OK) {
            continue;
        }

        bufferSent = 0;
        fragment = 0;

        // cria o pacote para envio e pega seu cabeçalho
        packet = new NetPacket(_contentType);
        NetHeader * header = packet->getHeader();

        // se os dados cabem em apenas um pacote
        // (inclui o caso em que não há dados, apenas cabeçalho)
        uint32_t defaultDataSize = NetPacket::DEFAULT_PACKSIZE - header->getSize();
        if (bufferSize < defaultDataSize) {

            // preenche o pacote
            _seqnum++;
            _FillDefaultPacket(packet, bufferSize, bufferSize, timestamp, _seqnum, extraData);
            packet->copyPayload(buffer, bufferSize);

            bufferSent = _SendPacket(packet); // envia

        // tem mais dados, inicia particionamento e envio...
        } else {

            // preenche o pacote padrão
            _seqnum++;
            _FillDefaultPacket(packet, defaultDataSize, bufferSize, timestamp, _seqnum, extraData);

            // vai particionando os dados em pacotes de tamanho padrão até enviar tudo
            while ((uint32_t)bufferSent < bufferSize) {

                // se os dados que faltam são menores que o tamanho padrão de um pacote,
                // tem que realocar o buffer do pacote para o novo tamanho
                uint32_t bufferLeft = bufferSize - bufferSent;
                if (bufferLeft < defaultDataSize && bufferLeft != packet->getPayloadSize()) {
                    packet->deallocBuffer();
                    _FillDefaultPacket(packet, bufferLeft, bufferSize, timestamp, _seqnum, extraData);
                    header = packet->getHeader();
                }

                // seta o payload
                packet->copyPayload(buffer + bufferSent, packet->getPayloadSize());

                // seta os atributos específicos pra este fragmento
                header->setAttrAsInt(NetHeader::ATTR_FRAGNUM, fragment);

                ret = _SendPacket(packet); // envia

                fragment++;
                bufferSent += packet->getPayloadSize();
            }
        }

        if (bufferSent > 0) {
            _stats.increment(NetStatistics::ATTR_SENT_FRAMES);
        }
        delete packet;
        queue_free(consumer);

    }

    queue_unregisterConsumer(&consumer);

    return NULL;
}
