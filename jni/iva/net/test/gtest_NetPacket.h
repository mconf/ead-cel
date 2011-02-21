#ifndef _NET_PACKET_TEST_H_
#define _NET_PACKET_TEST_H_

#include <gtest/gtest.h>
#include <NetPacket.h>

class NetPacketTest : public ::testing::Test
{
protected:
    NetPacket * _packetAudio;
    NetPacket * _packetVideo;

    virtual void SetUp()
    {
        _packetAudio = new NetPacket(NET_TYPE_AUDIO);
        _packetVideo = new NetPacket(NET_TYPE_VIDEO);
    }

    virtual void TearDown()
    {
        delete _packetAudio;
        delete _packetVideo;
    }

};

#endif
