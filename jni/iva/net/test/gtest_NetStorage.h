#ifndef _NET_STORAGE_TEST_H_
#define _NET_STORAGE_TEST_H_

#include <gtest/gtest.h>
#include <NetStorage.h>
#include <NetPacket.h>
#include <QueueExtraDataAudio.h>


class NetStorageTest : public ::testing::Test
{
protected:
    static const int PAYLOAD_SIZE = 1000;

    queue_t * _queue;
    NetStorage * _storage;
    NetType _type;
    NetPacket * _packet;
    NetHeader * _header;
    queue_consumer_t * _consumer;
    QueueExtraDataAudio _extraData;

    virtual void SetUp()
    {
        Milliseconds ts;

        _type = NET_TYPE_AUDIO;
        _queue = queue_create();
        _consumer = queue_registerConsumer(_queue);

        _storage = new NetStorage(_queue, 100);

        _extraData.setAudioFlags(QueueExtraDataAudio::AUDIO_ID_1);
        _extraData.setBitrate(1500);
        _extraData.setCodecId(COMMON_AUDIO_DEFAULT_CODEC);

        _packet = new NetPacket(_type);
        _packet->allocBuffer(PAYLOAD_SIZE);
        _header = _packet->getHeader();
        _header->setAttrAsInt(NetHeader::ATTR_FRAGNUM, 0);
        _header->setAttrAsInt(NetHeader::ATTR_FRAMESIZE, PAYLOAD_SIZE);
        _header->setAttrAsInt(NetHeader::ATTR_SEQNUM, 0);
        ts.setTimestamp();
        _header->setAttrAsInt(NetHeader::ATTR_TIMESTAMP, ts.getTime());
        _header->setExtraData(&_extraData);
    }

    virtual void TearDown()
    {
        delete _storage;
        delete _packet;
        queue_unregisterConsumer(&_consumer);
        queue_destroy(&_queue);
    }

    void _Compare();

};

#endif
