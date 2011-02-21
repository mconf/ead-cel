#include <gtest/gtest.h>
#include "gtest_NetStorage.h"
#include <QueueExtraDataAudio.h>


void NetStorageTest::_Compare()
{
    uint8_t * dataRecv;
    uint32_t timestampRecv;
    uint32_t buffersizeRecv;
    QueueExtraData * extraDataRecv;
    int ret;

    ret = queue_dequeue(_consumer, &dataRecv, &buffersizeRecv, &timestampRecv, &extraDataRecv);
    ASSERT_EQ(E_OK, ret);

    // agora compara o que recebeu com o que foi enviado

    EXPECT_EQ(QueueExtraData::EXTRA_DATA_AUDIO, extraDataRecv->getType());
    EXPECT_EQ(NET_TYPE_AUDIO, _header->getAttrAsInt(NetHeader::ATTR_TYPE));
    EXPECT_EQ(((QueueExtraDataAudio *)extraDataRecv)->getBitrate(),
              _header->getAttrAsInt(NetHeaderAudio::ATTR_BITRATE));
    EXPECT_EQ(((QueueExtraDataAudio *)extraDataRecv)->getCodecId(),
              _header->getAttrAsInt(NetHeaderAudio::ATTR_CODEC));
    EXPECT_EQ(((QueueExtraDataAudio *)extraDataRecv)->getAudioFlags(),
              _header->getAttrAsInt(NetHeaderAudio::ATTR_FLAGS));

    unsigned char * payload = _packet->getPayloadPointer();

    EXPECT_EQ(_header->getAttrAsInt(NetHeader::ATTR_FRAMESIZE), buffersizeRecv);
    EXPECT_EQ(_header->getAttrAsInt(NetHeader::ATTR_TIMESTAMP), timestampRecv);
    for (int i = 0; i < PAYLOAD_SIZE; i++) {
        EXPECT_EQ(payload[i], dataRecv[i]);
    }

    queue_free(_consumer);
}


TEST_F(NetStorageTest, AddSinglePacketAndCheckQueue)
{
    int err;
    err = _storage->add(_packet);
    ASSERT_EQ(E_OK, err);

    _Compare();
}

TEST_F(NetStorageTest, DuplicatedPackets)
{
    int err;
    err = _storage->add(_packet);
    ASSERT_EQ(E_OK, err); // sucesso
    err = _storage->add(_packet);
    ASSERT_NE(E_OK, err); // falha

    // tem que ter um dos pacotes na queue e o outros não
    _Compare();
    EXPECT_EQ(0, queue_length(_queue));
}

TEST_F(NetStorageTest, UnorderedPackets)
{
    int err;
    unsigned char * payload = _packet->getPayloadPointer();

    // obs: primeiro pacote deve ser o zero para poder testar melhor, pois
    //      a storage sempre aceita o primeiro pacote, não importa o seqnum
    _header->setAttrAsInt(NetHeader::ATTR_SEQNUM, 0);
    payload[0] = '0';
    err = _storage->add(_packet);
    ASSERT_EQ(E_OK, err);

    _header->setAttrAsInt(NetHeader::ATTR_SEQNUM, 2);
    payload[0] = '2';
    err = _storage->add(_packet);
    ASSERT_EQ(E_OK, err);
    _header->setAttrAsInt(NetHeader::ATTR_SEQNUM, 3);
    payload[0] = '3';
    err = _storage->add(_packet);
    ASSERT_EQ(E_OK, err);
    _header->setAttrAsInt(NetHeader::ATTR_SEQNUM, 1);
    payload[0] = '1';
    err = _storage->add(_packet);
    ASSERT_EQ(E_OK, err);

    // tem que ter os 3 pacotes na storage, mas ordenados
    _header->setAttrAsInt(NetHeader::ATTR_SEQNUM, 0);
    payload[0] = '0';
    _Compare();
    _header->setAttrAsInt(NetHeader::ATTR_SEQNUM, 1);
    payload[0] = '1';
    _Compare();
    _header->setAttrAsInt(NetHeader::ATTR_SEQNUM, 2);
    payload[0] = '2';
    _Compare();
    _header->setAttrAsInt(NetHeader::ATTR_SEQNUM, 3);
    payload[0] = '3';
    _Compare();

    EXPECT_EQ(0, queue_length(_queue));
}

TEST_F(NetStorageTest, IsKillerWorking)
{
    int err;
    unsigned char * payload = _packet->getPayloadPointer();

    err = _storage->start();
    ASSERT_EQ(E_OK, err);

    // adiciona 2 pacotes que não contém o frame inteiro (frame fragmentado)
    _header->setAttrAsInt(NetHeader::ATTR_FRAMESIZE, PAYLOAD_SIZE*3);
    _header->setAttrAsInt(NetHeader::ATTR_SEQNUM, 0);
    err = _storage->add(_packet);
    ASSERT_EQ(E_OK, err);
    _header->setAttrAsInt(NetHeader::ATTR_FRAMESIZE, PAYLOAD_SIZE*2);
    _header->setAttrAsInt(NetHeader::ATTR_SEQNUM, 1);
    err = _storage->add(_packet);
    ASSERT_EQ(E_OK, err);

    // killer ainda não agiu, devem haver 2 frames na storage
    EXPECT_EQ(2, _storage->size());

    // espera um pouco pra thread killer remover o pacote incompleto que já está atrasado
    Milliseconds(1000).sleep();

    // tanto storage quanto queue devem estar vazias
    EXPECT_EQ(0, _storage->size());
    EXPECT_EQ(0, queue_length(_queue));

    err = _storage->stop();
    ASSERT_EQ(E_OK, err);
}



