#include <NetHeader.h>
#include "gtest_NetPacket.h"

TEST_F(NetPacketTest, HeaderInitialization)
{
    NetHeader * header;

    // garante que tem um header e está bem inicializado
    header = _packetAudio->getHeader();
    ASSERT_TRUE(header != NULL);
    EXPECT_EQ(NET_TYPE_AUDIO, header->getType()) << "Pacote inicializou o header com o tipo errado";
    header = _packetVideo->getHeader();
    ASSERT_TRUE(header != NULL);
    EXPECT_EQ(NET_TYPE_VIDEO, header->getType()) << "Pacote inicializou o header com o tipo errado";
}

TEST_F(NetPacketTest, DataInitialization)
{
    // ponteiros e tamanho do data tem que estar zerados
    EXPECT_TRUE(_packetAudio->getPayloadPointer() == NULL);
    EXPECT_EQ(0, _packetAudio->getPayloadSize());
    EXPECT_TRUE(_packetVideo->getPayloadPointer() == NULL);
    EXPECT_EQ(0, _packetVideo->getPayloadSize());
}

TEST_F(NetPacketTest, Initialization)
{
    NetHeader * header;

    // tamanho dos pacotes tem que ser só o tamanho do header
    header = _packetAudio->getHeader();
    EXPECT_EQ(header->getSize(), _packetAudio->getSize());
    header = _packetVideo->getHeader();
    EXPECT_EQ(header->getSize(), _packetVideo->getSize());
}

TEST_F(NetPacketTest, BufferAllocation)
{
#define BUFFER_SIZE 1024

    // aloca novo buffer
    _packetAudio->allocBuffer(BUFFER_SIZE);
    ASSERT_TRUE(_packetAudio->getPayloadPointer() != NULL);
    EXPECT_EQ(BUFFER_SIZE, _packetAudio->getPayloadSize());

    // limpa o buffer
    _packetAudio->deallocBuffer();
    ASSERT_TRUE(_packetAudio->getPayloadPointer() == NULL);
    EXPECT_EQ(0, _packetAudio->getPayloadSize());

#undef BUFFER_SIZE
}

TEST_F(NetPacketTest, BufferAssigning)
{
#define BUFFER_SIZE 1024

    // aloca um buffer
    unsigned char * buffer;
    buffer = (unsigned char *)malloc(sizeof(unsigned char) * BUFFER_SIZE);

    /// \todo Colocar alguns dados nesse buffer e ver se vão aparecer no buffer do pacote.

    // atribui o buffer para o pacote
    _packetAudio->allocBuffer(buffer, BUFFER_SIZE);
    ASSERT_TRUE(_packetAudio->getPayloadPointer() != NULL);
    EXPECT_EQ(BUFFER_SIZE, _packetAudio->getPayloadSize());

    // limpa o buffer
    _packetAudio->deallocBuffer();
    ASSERT_TRUE(_packetAudio->getPayloadPointer() == NULL);
    EXPECT_EQ(0, _packetAudio->getPayloadSize());

#undef BUFFER_SIZE
}

