#include <NetHeader.h>
#include "gtest_NetHeader.h"
#include <QueueExtraData.h>
#include <QueueExtraDataAudio.h>
#include <QueueExtraDataVideo.h>

TEST_F(NetHeaderTest, Initialization)
{
    EXPECT_EQ(NET_TYPE_NONE, _header->getType());
    EXPECT_NE(0, _header->getSize());
}

TEST_F(NetHeaderTest, AttrInit)
{
    // garante que todos atributos existem e que são nulos
    ASSERT_TRUE(_header->hasAttr(NetHeader::ATTR_FRAGNUM));
    ASSERT_TRUE(_header->hasAttr(NetHeader::ATTR_SEQNUM));
    ASSERT_TRUE(_header->hasAttr(NetHeader::ATTR_TIMESTAMP));
    ASSERT_TRUE(_header->hasAttr(NetHeader::ATTR_FRAMESIZE));
    ASSERT_TRUE(_header->hasAttr(NetHeader::ATTR_TYPE));
}

TEST_F(NetHeaderTest, SetAttrWhenBufferNull)
{
    // tenta setar atributos enquanto o buffer é nulo
    _header->setAttrAsInt(NetHeader::ATTR_TYPE, 0);
    ASSERT_TRUE(_header->hasAttr(NetHeader::ATTR_TYPE));
    EXPECT_EQ(0, _header->getAttrAsInt(NetHeader::ATTR_TYPE));

    // tenta setar atributos enquanto o buffer é nulo
    _header->setAttrAsInt(NetHeader::ATTR_SEQNUM, 123);
    ASSERT_TRUE(_header->hasAttr(NetHeader::ATTR_SEQNUM));
    EXPECT_EQ(0, _header->getAttrAsInt(NetHeader::ATTR_SEQNUM));
}

TEST_F(NetHeaderTest, MassiveSetAttributes)
{
    unsigned char * buffer;
    buffer = (unsigned char *)malloc(sizeof(unsigned char) * BUFFER_SIZE);
    memset(buffer, 0, BUFFER_SIZE);

    // seta o buffer zerado
    _header->setBuffer(buffer, BUFFER_SIZE);

    // primeiro confirma que os atributos existem
    ASSERT_TRUE(_header->hasAttr(NetHeader::ATTR_TYPE));
    ASSERT_TRUE(_header->hasAttr(NetHeader::ATTR_FRAGNUM));
    ASSERT_TRUE(_header->hasAttr(NetHeader::ATTR_SEQNUM));
    ASSERT_TRUE(_header->hasAttr(NetHeader::ATTR_TIMESTAMP));
    ASSERT_TRUE(_header->hasAttr(NetHeader::ATTR_FRAMESIZE));

    Milliseconds ms;
    srand(ms.getTime());

    unsigned int type, framesize, seqnum, fragnum, timestamp;

    for (int i = 0; i < 5000; i++) {
        type = rand() % 64; // type: 6 bits
        _header->setAttrAsInt(NetHeader::ATTR_TYPE, type);
        framesize = rand() % (int)pow(2.0,24.0); // framesize: 24 bits
        _header->setAttrAsInt(NetHeader::ATTR_FRAMESIZE, framesize);
        seqnum = rand() % (int)pow(2.0,16.0); // seqnum: 16 bits
        _header->setAttrAsInt(NetHeader::ATTR_SEQNUM, seqnum);
        fragnum = rand() % (int)pow(2.0,16.0); // frag num: 16 bits
        _header->setAttrAsInt(NetHeader::ATTR_FRAGNUM, fragnum);
        timestamp = rand() % (int)pow(2.0,32.0); // timestamp: 32 bits
        _header->setAttrAsInt(NetHeader::ATTR_TIMESTAMP, timestamp);

        EXPECT_EQ(type, _header->getAttrAsInt(NetHeader::ATTR_TYPE));
        EXPECT_EQ(framesize, _header->getAttrAsInt(NetHeader::ATTR_FRAMESIZE));
        EXPECT_EQ(seqnum, _header->getAttrAsInt(NetHeader::ATTR_SEQNUM));
        EXPECT_EQ(fragnum, _header->getAttrAsInt(NetHeader::ATTR_FRAGNUM));
        EXPECT_EQ(timestamp, _header->getAttrAsInt(NetHeader::ATTR_TIMESTAMP));
    }
}
