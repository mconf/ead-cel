#ifndef _IGMP_H_
#define _IGMP_H_

#include "SocketRaw.h"
#include "AbstractIgmp.h"

class Igmp: public AbstractIgmp
{
private:
    static const int IGMP_BUFFER_SIZE = 8;
    static const int IGMP_V2_MEMBERSHIP_REPORT = 0x16;

    SocketRaw _socket;
    IPv4 _ip;
    string _buffer;

    void _fillChecksum();
    void _constructBuffer(const IPv4& ip);

public:
    Igmp(const IPv4& ip);
    virtual ~Igmp();

    int send();
};

#endif
