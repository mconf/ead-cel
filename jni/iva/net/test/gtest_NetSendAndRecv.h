#ifndef _NET_SEND_AND_RECV_TEST_H_
#define _NET_SEND_AND_RECV_TEST_H_

#include <common.h>
#include <NetRecv.h>
#include <NetSend.h>
#include <gtest/gtest.h>

class NetSendAndRecvTest : public ::testing::Test
{
protected:
    queue_consumer_t * _qRecvACons, * _qRecvVCons;
    queue_t * _qSendA, * _qRecvA;
    queue_t * _qSendV, * _qRecvV;
    NetRecv * _recvA, * _recvV;
    NetSend * _sendA, * _sendV;
    uint8_t * _data;
    static const int DATA_SIZE = 50000;
    static const int DATA_SIZE_AUDIO = 500;

    void _ReceiveAndCompare(uint32_t buffersize, uint32_t timestamp, uint8_t * data,
                            QueueExtraData * extraData, queue_consumer_t * consumer);

    virtual void SetUp()
    {
        _qSendA = queue_create();
        _qRecvA = queue_create();
        _qRecvACons = queue_registerConsumer(_qRecvA);
        _recvA = new NetRecv(NET_TYPE_AUDIO, _qRecvA);
        _sendA = new NetSend(NET_TYPE_AUDIO, _qSendA);

        _qSendV = queue_create();
        _qRecvV = queue_create();
        _qRecvVCons = queue_registerConsumer(_qRecvV);
        _recvV = new NetRecv(NET_TYPE_VIDEO, _qRecvV);
        _sendV = new NetSend(NET_TYPE_VIDEO, _qSendV);

        _data = (uint8_t *)queue_malloc(DATA_SIZE);
    }

    virtual void TearDown()
    {
        //queue_dealloc(_data);

        delete _sendV;
        delete _recvV;
        queue_unregisterConsumer(&_qRecvVCons);
        queue_destroy(&_qRecvV);
        queue_destroy(&_qSendV);

        delete _sendA;
        delete _recvA;
        queue_unregisterConsumer(&_qRecvACons);
        queue_destroy(&_qRecvA);
        queue_destroy(&_qSendA);
    }

};

#endif
