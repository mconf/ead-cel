#pragma once
#include "Socket.h"

class SocketRaw :
    public Socket
{
private:
    static const int _family = AF_INET;
    static const int _type = SOCK_RAW;
    int _protocol;

public:
    SocketRaw(int protocol);
    virtual ~SocketRaw(void);

    int openAsSender(const IPv4& ip, bool blocking);

    virtual int send(const char* buf, int len);
    virtual int send(const string& buf);
    virtual int operator<<(const string& buf);
};
