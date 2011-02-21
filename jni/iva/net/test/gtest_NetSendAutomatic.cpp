#include "gtest_NetSendAutomatic.h"

NetSendAutomaticTestProducer::NetSendAutomaticTestProducer(queue_t * queue, int bufferSize, int sleep)
{
    _queue = queue;
    _bufferSize = bufferSize;
    _threadRun = false;
    _thread = NULL;
    _sleepTime = sleep;
    _running = false;
    start();
}

NetSendAutomaticTestProducer::~NetSendAutomaticTestProducer()
{
    stop();
}

void NetSendAutomaticTestProducer::setQueue(queue_t * queue)
{
    _mutex.lock();
    _queue = queue;
    _mutex.unlock();
}

void NetSendAutomaticTestProducer::start()
{
    _mutex.lock();
    if (!_thread) {
        _threadRun = true;
        _thread = new Thread<NetSendAutomaticTestProducer>(this, &NetSendAutomaticTestProducer::_ThreadFunc);
        _thread->run(NULL, true);
    }
    _mutex.unlock();
}

void NetSendAutomaticTestProducer::stop()
{
    _mutex.lock();
    if (_thread) {
        _threadRun = false;
        if (_thread->isRunning()) {
            _thread->join(NULL);
        }
        delete _thread;
        _thread = NULL;
    }
    _mutex.unlock();
}

void * NetSendAutomaticTestProducer::_ThreadFunc(void * param)
{
    Milliseconds ts;

    while (_threadRun) {
        int size = queue_length(_queue);
        if (size < 10) { // pra não estourar a fila
            uint8_t * buffer = (uint8_t *)queue_malloc(_bufferSize);
            ts.setTimestamp();
            int ret = queue_enqueue(_queue, buffer, _bufferSize, ts.getTime(), NULL);
            if (ret != E_OK) {
                queue_dealloc(buffer);
            }
        }
        Milliseconds(_sleepTime).sleep();
    }
    return NULL;
}

NetSendAutomaticTest::NetSendAutomaticTest(NetType type) :
    _ip("127.0.0.1")
{
    _totalSent = 0;
    _thread = NULL;
    _producer = NULL;
    _threadRun = false;
    _queue = queue_create();
    _net = new NetSend(type, _queue);
}

NetSendAutomaticTest::~NetSendAutomaticTest()
{
    stop();
    delete _net;
    queue_destroy(&_queue);
}

queue_t * NetSendAutomaticTest::getQueue()
{
    return _queue;
}

void NetSendAutomaticTest::start(IPv4 &ip, int port, int timeout, bool automatic)
{
    if (!_thread) {
        _ip = ip;
        _port = port;
        _timeout = timeout;
        if (automatic) {
            _producer = new NetSendAutomaticTestProducer(_queue, 3000, 5);
        }
        _threadRun = true;
        _thread = new Thread<NetSendAutomaticTest>(this, &NetSendAutomaticTest::_ThreadFunc);
        _thread->run(NULL, true);
    }
}

void NetSendAutomaticTest::stop()
{
    if (_thread) {
        _threadRun = false;
        if (_thread->isRunning()) {
            _thread->join(NULL);
        }
        delete _thread;
        _thread = NULL;
        if (_producer) {
            delete _producer;
            _producer = NULL;
        }
    }
}

void * NetSendAutomaticTest::_ThreadFunc(void * param)
{
    Milliseconds ts, tsStart, tsDiff;
    bool timeout;
    int sent;

    _running = true;
    timeout = false;
    tsStart.setTimestamp();

    _net->start(_ip, _port);
    while (_threadRun && !timeout) {
        Milliseconds(500).sleep();
        sent = _net->getStatistics()->getAttr(NetStatistics::ATTR_SENT_BYTES);
        _totalSent += sent;
        cout << "Bytes enviados nos ultimos 500 ms: " << sent << endl;

        ts.setTimestamp();
        tsDiff = ts - tsStart;
        if (_timeout && tsDiff.getTime() > _timeout) {
            timeout = true;
        }
    }
    _net->stop();

    sent = _net->getStatistics()->getAttr(NetStatistics::ATTR_SENT_BYTES);
    _totalSent += sent;
    cout << "Bytes enviados no final: " << sent << endl;

    _running = false;

    return NULL;
}

bool NetSendAutomaticTest::isRunning()
{
    return _running;
}

uint32_t NetSendAutomaticTest::getTotalSent()
{
    return _totalSent;
}

