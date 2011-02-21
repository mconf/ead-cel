#ifndef _NET_QUEUE_TEST_H_
#define _NET_QUEUE_TEST_H_

#include <gtest/gtest.h>
#include <NetQueue.h>
#include <NetPacket.h>

class NetQueueTest : public ::testing::Test
{
public:
    static const int PACK_VIDEO_FRAMESIZE = 25000;

protected:
    NetPacket * _pAud;
    NetPacket * _pVid;
    NetHeaderAudio * _hAud;
    NetHeaderVideo * _hVid;
    NetQueue * _q;
    int PACK_VIDEO_DATASIZE;

    void _MountVideoPacket(int dataSize = 0);
    void _MountAudioPacket(int dataSize = 0);

    virtual void SetUp()
    {
        _q = new NetQueue(NetQueue::DEFAULT_MAX_SIZE);
        _pVid = NULL;
        _pAud = NULL;
        _MountVideoPacket();
        _MountAudioPacket();
    }

    virtual void TearDown()
    {
        delete _pVid;
        delete _pAud;
        delete _q;
    }

};

#endif
