#ifndef _NET_RECV_AUTOMATIC_TEST_H_
#define _NET_RECV_AUTOMATIC_TEST_H_

#include <gtest/gtest.h>
#include <NetRecv.h>

class NetRecvAutomaticTest
{
protected:
    queue_t * _queue;
    NetRecv * _net;
    IPv4 _ip;
    int _port;
    int _timeout;
    uint32_t _totalReceived;
    NetType _type;
    Thread<NetRecvAutomaticTest> * _thread;
    bool _threadRun;
    bool _running;
    void * _ThreadFunc(void * param);

public:
    NetRecvAutomaticTest(NetType type);
    ~NetRecvAutomaticTest();

    void start(IPv4 &ip, int port, int timeout = 0);
    void stop();
    bool isRunning();
    uint32_t getTotalReceived();
    queue_t * getQueue();

};

#endif
