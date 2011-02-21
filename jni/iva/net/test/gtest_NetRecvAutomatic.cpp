#include "gtest_NetRecvAutomatic.h"

NetRecvAutomaticTest::NetRecvAutomaticTest(NetType type) :
    _ip("127.0.0.1")
{
    _totalReceived = 0;
    _thread = NULL;
    _threadRun = false;
    _queue = queue_create();
    _net = new NetRecv(type, _queue);
}

NetRecvAutomaticTest::~NetRecvAutomaticTest()
{
    stop();
    delete _net;
    queue_destroy(&_queue);
}

queue_t * NetRecvAutomaticTest::getQueue()
{
    return _queue;
}

void NetRecvAutomaticTest::start(IPv4 &ip, int port, int timeout)
{
    if (!_thread) {
        _ip = ip;
        _port = port;
        _timeout = timeout;
        _threadRun = true;
        _thread = new Thread<NetRecvAutomaticTest>(this, &NetRecvAutomaticTest::_ThreadFunc);
        _thread->run(NULL, true);
    }
}

void NetRecvAutomaticTest::stop()
{
    if (_thread) {
        _threadRun = false;
        if (_thread->isRunning()) {
            _thread->join(NULL);
        }
        delete _thread;
        _thread = NULL;
    }
}

void * NetRecvAutomaticTest::_ThreadFunc(void * param)
{
    Interval ts, startTs, lastPrint;
    int ret, received;
    uint8_t * buffer;
    uint32_t bufferSize, timestamp;
    queue_consumer_t * consumer;
    QueueExtraData * extraData;
    bool timeout;

    _running = true;
    timeout = false;

    ts.setTimestamp();
    startTs = ts;
    lastPrint = ts;

    _net->start(_ip, _port);
    consumer = queue_registerConsumer(_queue);
    while (_threadRun && !timeout) {

        ret = queue_dequeue(consumer, &buffer, &bufferSize, &timestamp, &extraData);

        ts.setTimestamp();
        Milliseconds diff = ts - startTs;
        if (_timeout && diff.getTime() > _timeout) {
            timeout = true;
        }

        diff = ts - lastPrint;
        if (diff.getTime() > 500) {
            received = _net->getStatistics().getAttr(NetStatistics::ATTR_RECEIVED_BYTES);
            _totalReceived += received;

            cout << "Bytes recebidos nos ultimos 500 ms: " << received << endl;
            lastPrint = ts;
        }

        if (ret != E_OK) {
            Milliseconds(2).sleep();
            continue;
        }
        queue_enqueue(_queue, buffer, bufferSize, timestamp, extraData);
        //queue_free(consumer);
    }
    _net->stop();

    received = _net->getStatistics().getAttr(NetStatistics::ATTR_RECEIVED_BYTES);
    _totalReceived += received;
    cout << "Bytes recebidos no final: " << received << endl;

    queue_unregisterConsumer(&consumer);
    _running = false;

    return NULL;
}

bool NetRecvAutomaticTest::isRunning()
{
    return _running;
}

uint32_t NetRecvAutomaticTest::getTotalReceived()
{
    return _totalReceived;
}


