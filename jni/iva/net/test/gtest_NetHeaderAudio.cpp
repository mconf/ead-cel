#include "gtest_NetHeaderAudio.h"

TEST_F(NetHeaderAudioTest, Initialization)
{
    EXPECT_EQ(NET_TYPE_AUDIO, _header->getType());
    EXPECT_NE(0, _header->getSize());
}

TEST_F(NetHeaderAudioTest, AttrInit)
{
    // garante que todos atributos existem e que são nulos
    ASSERT_TRUE(_header->hasAttr(NetHeaderAudio::ATTR_CODEC));
    ASSERT_TRUE(_header->hasAttr(NetHeaderAudio::ATTR_FLAGS));
    ASSERT_TRUE(_header->hasAttr(NetHeaderAudio::ATTR_BITRATE));
}

TEST_F(NetHeaderAudioTest, MassiveSetAttributes)
{
    unsigned char * buffer;
    buffer = (unsigned char *)malloc(sizeof(unsigned char) * BUFFER_SIZE);
    memset(buffer, 0, BUFFER_SIZE);

    // seta o buffer zerado
    _header->setBuffer(buffer, BUFFER_SIZE);

    // primeiro confirma que os atributos existem
    ASSERT_TRUE(_header->hasAttr(NetHeaderAudio::ATTR_CODEC));
    ASSERT_TRUE(_header->hasAttr(NetHeaderAudio::ATTR_FLAGS));
    ASSERT_TRUE(_header->hasAttr(NetHeaderAudio::ATTR_BITRATE));

    Milliseconds ms;
    srand(ms.getTime());

    unsigned int codec, flags, bitrate;
    for (int i = 0; i < 5000; i++) {
        codec = rand() % 256; // codec: 8 bits
        _header->setAttrAsInt(NetHeaderAudio::ATTR_CODEC, codec);
        flags = rand() % 256; // flags: 8 bits
        _header->setAttrAsInt(NetHeaderAudio::ATTR_FLAGS, flags);
        bitrate = rand() % (int)pow(2.0,32.0); // bitrate: 32 bits
        _header->setAttrAsInt(NetHeaderAudio::ATTR_BITRATE, bitrate);

        EXPECT_EQ(NET_TYPE_AUDIO, _header->getAttrAsInt(NetHeader::ATTR_TYPE));
        EXPECT_EQ(NetHeader::IVA_SIGN, _header->getAttrAsInt(NetHeader::ATTR_SIGN));
        EXPECT_EQ(0, _header->getAttrAsInt(NetHeader::ATTR_FRAGNUM));
        EXPECT_EQ(0, _header->getAttrAsInt(NetHeader::ATTR_FRAMESIZE));
        EXPECT_EQ(0, _header->getAttrAsInt(NetHeader::ATTR_SEQNUM));
        EXPECT_EQ(0, _header->getAttrAsInt(NetHeader::ATTR_TIMESTAMP));
        EXPECT_EQ(codec, _header->getAttrAsInt(NetHeaderAudio::ATTR_CODEC));
        EXPECT_EQ(flags, _header->getAttrAsInt(NetHeaderAudio::ATTR_FLAGS));
        EXPECT_EQ(bitrate, _header->getAttrAsInt(NetHeaderAudio::ATTR_BITRATE));
    }
}
