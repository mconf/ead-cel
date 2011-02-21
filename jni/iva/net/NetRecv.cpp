#include <CommonLeaks.h>
#include <SocketUDP.h>
#include "NetRecv.h"
#include <CommonLeaksCpp.h>

NetRecv::NetRecv(NetType type, queue_t * queue,
                 uint16_t sessionId,
                 unsigned int maxPacketWait,
                 unsigned int bufferSize) :
    _outQueue(queue), _bufferSize(bufferSize),
    _contentType(type), _maxPacketWait(maxPacketWait),
    _redir(NULL), _validator(NULL),
    _thread(NULL), _threadRun(false),
    _ip("0.0.0.0"), _sessionId(sessionId)
{
    // valida os tipos suportados
    if (_contentType != NET_TYPE_AUDIO &&
        _contentType != NET_TYPE_VIDEO) {
            throw E_NET_INVALID_TYPE;
    }
    if (_maxPacketWait == 0) {
        switch (_contentType) {
            case NET_TYPE_AUDIO:
                _maxPacketWait = MAX_PACKET_WAIT_AUDIO;
                break;
            case NET_TYPE_VIDEO:
                _maxPacketWait = MAX_PACKET_WAIT_VIDEO;
                break;
        }
    }
    _storage = new NetStorage(_outQueue, _maxPacketWait);
    _storage->setStatistics(&_stats);
}

NetRecv::~NetRecv()
{
    stop();
    delete _storage;
}

NetType NetRecv::getType()
{
    return _contentType;
}

int NetRecv::start(const IPv4 &ip, unsigned int port)
{
    stop();

    _mutexSocket.lock();

    // abre o socket como receptor
    int ret = _socket.openAsReceiver(ip.getString(), port, false);
    if (ret != E_OK) {
        _mutexSocket.unlock();
        return ret;
    }
    _socket.setblocking(false);

    _ip = ip;

    _storage->start();

    // cria a thread de recebimento
    _threadRun = true;
    _thread = new Thread<NetRecv>(this, &NetRecv::_RecvThread);
    _thread->run(NULL, true);

    _mutexSocket.unlock();

    return E_OK;
}

int NetRecv::stop()
{
    _mutexSocket.lock();

    // para a thread de recebimento
    if (_thread) {
        _threadRun = false;
        if (_thread->isRunning()) {
            _thread->join(NULL);
        }
        delete _thread;
        _thread = NULL;
    }
    // finaliza o socket
    _socket.close();

    // limpa os dados da storage
    _storage->stop();
    _storage->clear();

    _ip = IPv4("0.0.0.0");

    _mutexSocket.unlock();

    return E_OK;
}

void NetRecv::setMaxPacketWait(unsigned int value)
{
    _maxPacketWait = value;
}

void NetRecv::setRedirect(NetRedir * value)
{
    _redir = value;
}

void NetRecv::setPacketValidator(NetRecvValidator * value)
{
    _validator = value;
}

NetStatistics & NetRecv::getStatistics()
{
    return _stats;
}

uint16_t NetRecv::getSessionId()
{
    return _sessionId;
}

void NetRecv::setSessionId(uint16_t value)
{
    _sessionId = value;
}

int NetRecv::sendSingleIGMPReport()
{
    if (_ip.getType() == IPv4::TYPE_MULTICAST) {
        return (Igmp(_ip).send() > 0) ? E_OK : E_ERROR;
    }
    return E_ERROR;
}

int NetRecv::_RecvThread_WaitPacket(NetPacket * packet)
{
    int ret;

    // fica esperando chegar algo
    do {
        ret = _socket.waitRead(100);
    } while (_threadRun && ret < 0);

    // se fechou a thread ou o socket foi finalizado
    if (!_threadRun || ret == 0) {
        return -1;
    }

    // cria o novo pacote e recebe os dados
    packet->deallocBuffer();
    packet->allocBuffer(NetPacket::MAX_PACKSIZE);
    ret = _socket.recv((char *)packet->getBufferPointer(), NetPacket::MAX_PACKSIZE);

    // atualiza tamanho dos dados pro tamanho que realmente foi recebido
    if (ret > 0) {
        packet->setPayloadSize(ret - packet->getHeader()->getSize());
    }

    return ret;
}

void * NetRecv::_RecvThread(void *)
{
    Milliseconds ts;
    int received;
    NetPacket * packet = NULL;
    int lastSeqNum = -1;

    while (_threadRun) {

        // tenta receber um pacote
        packet = new NetPacket(_contentType);
        received = _RecvThread_WaitPacket(packet);
        if (received <= 0) {
        	delete packet;
            continue;
        }

        NetHeader * header = packet->getHeader();

        // valida a assinatura e o tipo do pacote
        if (header->getAttrAsInt(NetHeader::ATTR_SIGN) != NetHeader::IVA_SIGN ||
            header->getAttrAsInt(NetHeader::ATTR_TYPE) != _contentType ) {

        	ErrorData err(E_ERROR, Location(AT));

            err << "Recebeu pacote com assinatura ou tipo inválido, descartando. Sign: ";
            err << header->getAttrAsInt(NetHeader::ATTR_SIGN);
            err << ", Type: ";
            err << header->getAttrAsInt(NetHeader::ATTR_TYPE);
            err.pushWarning();
            delete packet;
            continue;
        }

#ifndef ANDROID
        // valida o identificador da sessão do pacote
        if (header->getAttrAsInt(NetHeader::ATTR_SESSION_ID) != _sessionId) {
        	ErrorData err(E_ERROR, Location(AT));
            err << "Recebeu pacote com ID da sessão inválido, descartando. ID no pacote: ";
            err << header->getAttrAsInt(NetHeader::ATTR_SESSION_ID);
            err << ", ID esperado: ";
            err << _sessionId;
            err.pushWarning();
            delete packet;
            continue;
        }
#endif

        // atualiza as estatísticas
        ts.setTimestamp();
        _stats.setAttr(NetStatistics::ATTR_LAST_TIMESTAMP, ts.getTime());
        _stats.increment(NetStatistics::ATTR_RECEIVED_PACKETS);
        _stats.increment(NetStatistics::ATTR_RECEIVED_BYTES, received);

        // se tem redirecionamentos, chama função para envio
        if (_redir) {
            _redir->send(packet);
            _stats.increment(NetStatistics::ATTR_REDIRECTED_PACKETS);
            _stats.increment(NetStatistics::ATTR_REDIRECTED_BYTES, received);
            /// \todo Incrementa só 1 pacote, mesmo que redirecione ele para vários IPs. Não deveria contar todos?
        }

        /** \todo testes do tamanho do pacote recebido. se é muito pequeno, grande
                  ou se só tem cabeçalho*/
        //if (ret > NetPacket::DEFAULT_PACKSIZE) {
            //continue;
        //}

        // validação externa do pacote
        if (_validator) {
            if (!(*_validator)(packet)) {
            	delete packet;
                continue;
            }
        }

        // adiciona o pacote na storage

		#ifdef ANDROID
        if(queue_length(_outQueue) < 5){
       			_storage->add(packet);
               }
		#else
        _storage->add(packet);

		#endif

        if (lastSeqNum == -1)
            lastSeqNum = header->getAttrAsInt(NetHeader::ATTR_SEQNUM);
        else {
            int diff = header->getAttrAsInt(NetHeader::ATTR_SEQNUM) - lastSeqNum;
            lastSeqNum = header->getAttrAsInt(NetHeader::ATTR_SEQNUM);
            // se diff == 1, então tá tudo OK, não perdeu nenhum pacote anterior a esse
            if (diff > 1)
                _stats.increment(NetStatistics::ATTR_LOST_PACKETS, diff - 1);
        }

       delete packet;
    }

    return NULL;
}
