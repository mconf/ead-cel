#include "gtest_NetHeaderVideo.h"

TEST_F(NetHeaderVideoTest, Initialization)
{
    EXPECT_EQ(NET_TYPE_VIDEO, _header->getType());
    EXPECT_NE(0, _header->getSize());
}

TEST_F(NetHeaderVideoTest, AttrInit)
{
    // garante que todos atributos existem e que são nulos
    ASSERT_TRUE(_header->hasAttr(NetHeaderVideo::ATTR_CODEC));
    ASSERT_TRUE(_header->hasAttr(NetHeaderVideo::ATTR_FPS));
    ASSERT_TRUE(_header->hasAttr(NetHeaderVideo::ATTR_BITRATE));
    ASSERT_TRUE(_header->hasAttr(NetHeaderVideo::ATTR_WIDTH));
    ASSERT_TRUE(_header->hasAttr(NetHeaderVideo::ATTR_HEIGHT));
}

TEST_F(NetHeaderVideoTest, SetBufferAndAttributes)
{
#define BUFFER_SIZE 1024

    unsigned char * buffer;
    buffer = (unsigned char *)malloc(sizeof(unsigned char) * BUFFER_SIZE);

    // seta o buffer
    _header->setBuffer(buffer, BUFFER_SIZE);

#undef BUFFER_SIZE

    // verifica se os atributos estão ok
    ASSERT_TRUE(_header->hasAttr(NetHeaderVideo::ATTR_WIDTH));

    // mesma coisa mas agora usando as funções que tratam ints direto
    _header->setAttrAsInt(NetHeaderVideo::ATTR_WIDTH, 720);
    EXPECT_EQ(720, (int)_header->getAttrAsInt(NetHeaderVideo::ATTR_WIDTH));
}
TEST_F(NetHeaderVideoTest, MassiveSetAttributes)
{
    unsigned char * buffer;
    buffer = (unsigned char *)malloc(sizeof(unsigned char) * BUFFER_SIZE);
    memset(buffer, 0, BUFFER_SIZE);

    // seta o buffer zerado
    _header->setBuffer(buffer, BUFFER_SIZE);

    // primeiro confirma que os atributos existem
    ASSERT_TRUE(_header->hasAttr(NetHeaderVideo::ATTR_CODEC));
    ASSERT_TRUE(_header->hasAttr(NetHeaderVideo::ATTR_FPS));
    ASSERT_TRUE(_header->hasAttr(NetHeaderVideo::ATTR_WIDTH));
    ASSERT_TRUE(_header->hasAttr(NetHeaderVideo::ATTR_HEIGHT));
    ASSERT_TRUE(_header->hasAttr(NetHeaderVideo::ATTR_BITRATE));

    Milliseconds ms;
    srand(ms.getTime());

    unsigned int codec, fps, width, height, bitrate;
    for (int i = 0; i < 5000; i++) {
        codec = rand() % 256; // codec: 8 bits
        _header->setAttrAsInt(NetHeaderVideo::ATTR_CODEC, codec);
        fps = rand() % 256; // fps: 8 bits
        _header->setAttrAsInt(NetHeaderVideo::ATTR_FPS, fps);
        width = rand() % (int)pow(2.0,16.0); // width: 16 bits
        _header->setAttrAsInt(NetHeaderVideo::ATTR_WIDTH, width);
        height = rand() % (int)pow(2.0,16.0); // height: 16 bits
        _header->setAttrAsInt(NetHeaderVideo::ATTR_HEIGHT, height);
        bitrate = rand() % (int)pow(2.0,32.0); // bitrate: 32 bits
        _header->setAttrAsInt(NetHeaderVideo::ATTR_BITRATE, bitrate);

        EXPECT_EQ(NET_TYPE_VIDEO, _header->getAttrAsInt(NetHeader::ATTR_TYPE));
        EXPECT_EQ(NetHeader::IVA_SIGN, _header->getAttrAsInt(NetHeader::ATTR_SIGN));
        EXPECT_EQ(0, _header->getAttrAsInt(NetHeader::ATTR_FRAGNUM));
        EXPECT_EQ(0, _header->getAttrAsInt(NetHeader::ATTR_FRAMESIZE));
        EXPECT_EQ(0, _header->getAttrAsInt(NetHeader::ATTR_SEQNUM));
        EXPECT_EQ(0, _header->getAttrAsInt(NetHeader::ATTR_TIMESTAMP));
        EXPECT_EQ(codec, _header->getAttrAsInt(NetHeaderVideo::ATTR_CODEC));
        EXPECT_EQ(fps, _header->getAttrAsInt(NetHeaderVideo::ATTR_FPS));
        EXPECT_EQ(width, _header->getAttrAsInt(NetHeaderVideo::ATTR_WIDTH));
        EXPECT_EQ(height, _header->getAttrAsInt(NetHeaderVideo::ATTR_HEIGHT));
        EXPECT_EQ(bitrate, _header->getAttrAsInt(NetHeaderVideo::ATTR_BITRATE));
    }
}

