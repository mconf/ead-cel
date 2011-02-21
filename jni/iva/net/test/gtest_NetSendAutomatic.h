#ifndef _NET_SEND_AUTOMATIC_TEST_H_
#define _NET_SEND_AUTOMATIC_TEST_H_

#include <gtest/gtest.h>
#include <Mutex.h>
#include <Thread.h>
#include <NetSend.h>

class NetSendAutomaticTestProducer
{
private:
    queue_t * _queue;
    Mutex _mutex;
    Thread<NetSendAutomaticTestProducer> * _thread;
    bool _threadRun;
    bool _running;
    int _bufferSize;
    int _sleepTime;

    void * _ThreadFunc(void * param);

public:
    NetSendAutomaticTestProducer(queue_t * queue, int bufferSize, int sleep);
    ~NetSendAutomaticTestProducer();

    void start();
    void stop();
    void setQueue(queue_t * queue);

};

class NetSendAutomaticTest
{
protected:
    queue_t * _queue;
    NetSend * _net;
    IPv4 _ip;
    int _port;
    int _timeout;
    uint32_t _totalSent;
    NetType _type;
    NetSendAutomaticTestProducer * _producer;
    Thread<NetSendAutomaticTest> * _thread;
    bool _running;
    bool _threadRun;
    void * _ThreadFunc(void * param);

public:
    NetSendAutomaticTest(NetType type);
    ~NetSendAutomaticTest();

    void start(IPv4 &ip, int port, int timeout = 0, bool automatic = true);
    void stop();
    bool isRunning();
    uint32_t getTotalSent();
    queue_t * getQueue();

};

#endif
