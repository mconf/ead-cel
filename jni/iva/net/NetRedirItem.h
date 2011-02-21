#ifndef _NET_REDIR_ITEM_H_
#define _NET_REDIR_ITEM_H_

#include "netDefs.h"
#include <SocketUDP.h>
#include <string>
#include "NetPacket.h"
using namespace std;

class NetRedirItem
{
    int _id;                                 ///< Identificador do item
    bool _enabled;                           ///< Redireção habilitada?
    unsigned int _port;                      ///< Porta para transmissão
    IPv4 _ipv4;                              ///< IP para onde os dados são redirecionados
    SocketUDP _socketSend;                   ///< Socket usado para enviar dados

    void _CloseSocket();
    void _OpenSocket();

public:
    NetRedirItem(int id, bool enabled, const IPv4& ipv4, unsigned int port);
    ~NetRedirItem();

    int send(NetPacket * packet);

    int getId() const;
    bool getEnabled() const;
    bool getMulticast() const;
    unsigned int getPort() const;
    const IPv4& getIp() const;

    void setId(int value);
    void setEnabled(bool value);
    void setPort(unsigned int value);
    void setIp(const IPv4& value);
};

#endif
