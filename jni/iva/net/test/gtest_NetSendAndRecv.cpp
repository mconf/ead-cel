#include <QueueExtraDataAudio.h>
#include <QueueExtraDataVideo.h>
#include <NetRedir.h>
#include "gtest_NetSendAndRecv.h"
#include "gtest_NetSendAutomatic.h"
#include "gtest_NetRecvAutomatic.h"

#define LOCAL_IP     IPv4("127.0.0.1")
#define LOCAL_PORT   12001



/** \file gtest_NetSendAndRecv
 * Este arquivo contém os testes que precisam tanto da NetSend quanto da NetRecv para
 * funcionarem. Como o envio e recebimento de pacotes, o redirecionamento, o NetRecvValidator, etc.
 */

void NetSendAndRecvTest::_ReceiveAndCompare(uint32_t buffersize, uint32_t timestamp, uint8_t * data,
                                            QueueExtraData * extraData, queue_consumer_t * consumer)
{
    uint8_t * dataRecv;
    uint32_t timestampRecv;
    uint32_t buffersizeRecv;
    QueueExtraData * extraDataRecv;
    int ret;

    // fica esperando ter um item na queue
    do {
        Milliseconds(2).sleep();
        ret = queue_dequeue(consumer, &dataRecv, &buffersizeRecv, &timestampRecv, &extraDataRecv);
    } while (ret != E_OK);

    // agora compara o que recebeu com o que foi enviado

    EXPECT_EQ(extraData->getType(), extraDataRecv->getType());
    if (extraData->getType() == QueueExtraData::EXTRA_DATA_AUDIO) {
        EXPECT_EQ(((QueueExtraDataAudio *)extraData)->getAudioFlags(),
                  ((QueueExtraDataAudio *)extraDataRecv)->getAudioFlags());
        EXPECT_EQ(((QueueExtraDataAudio *)extraData)->getBitrate(),
                  ((QueueExtraDataAudio *)extraDataRecv)->getBitrate());
        EXPECT_EQ(((QueueExtraDataAudio *)extraData)->getCodecId(),
                  ((QueueExtraDataAudio *)extraDataRecv)->getCodecId());
    } else if (extraData->getType() == QueueExtraData::EXTRA_DATA_VIDEO) {
        EXPECT_EQ(((QueueExtraDataVideo *)extraData)->getBitrate(),
                  ((QueueExtraDataVideo *)extraDataRecv)->getBitrate());
        EXPECT_EQ(((QueueExtraDataVideo *)extraData)->getCodecId(),
                  ((QueueExtraDataVideo *)extraDataRecv)->getCodecId());
        EXPECT_EQ(((QueueExtraDataVideo *)extraData)->getFps(),
                  ((QueueExtraDataVideo *)extraDataRecv)->getFps());
        EXPECT_EQ(((QueueExtraDataVideo *)extraData)->getWidth(),
                  ((QueueExtraDataVideo *)extraDataRecv)->getWidth());
        EXPECT_EQ(((QueueExtraDataVideo *)extraData)->getHeight(),
                  ((QueueExtraDataVideo *)extraDataRecv)->getHeight());
    }
    EXPECT_EQ(buffersize, buffersizeRecv);
    EXPECT_EQ(timestamp, timestampRecv);
    for (int i = 0; i < DATA_SIZE; i++) {
        EXPECT_EQ(data[i], dataRecv[i]);
    }
    queue_free(consumer);
}

TEST_F(NetSendAndRecvTest, SendAndRecvOneAudioPacketCorrectly)
{
    uint32_t timestamp;
    uint32_t buffersize;
    QueueExtraDataAudio extraData;

    _recvA->start(LOCAL_IP, LOCAL_PORT);
    _sendA->start(LOCAL_IP, LOCAL_PORT);
    Milliseconds(400).sleep(); // para as threads iniciarem

    // monta os dados de envio e zera os de recebimento
    buffersize = DATA_SIZE_AUDIO;
    timestamp = 50;
    memset(_data, 'a', DATA_SIZE_AUDIO/2);
    memset(_data+2500, '8', DATA_SIZE_AUDIO/2);
    extraData.setAudioFlags(QueueExtraDataAudio::AUDIO_ID_3);
    extraData.setBitrate(128);
    extraData.setCodecId(COMMON_CODEC_AUDIO_MP2);

    // coloca dado na queue de envio e dorme um pouco pra ele ser enviado
    queue_enqueue(_qSendA, _data, buffersize, timestamp, &extraData);

    // espera chegar na de recebimento e compara os dados
    _ReceiveAndCompare(buffersize, timestamp, _data, &extraData, _qRecvACons);

    // recebeu os dados, pode parar as nets
    _sendA->stop();
    _recvA->stop();
}

TEST_F(NetSendAndRecvTest, SendAndRecvOneVideoPacketCorrectly)
{
    uint32_t timestamp;
    uint32_t buffersize;
    QueueExtraDataVideo extraData;

    _recvV->start(LOCAL_IP, LOCAL_PORT);
    _sendV->start(LOCAL_IP, LOCAL_PORT);
    Milliseconds(400).sleep(); // para as threads iniciarem

    // monta os dados de envio e zera os de recebimento
    buffersize = DATA_SIZE;
    timestamp = 50;
    memset(_data, 'a', DATA_SIZE/2);
    memset(_data+2500, '8', DATA_SIZE/2);
    extraData.setBitrate(128);
    extraData.setCodecId(COMMON_CODEC_VIDEO_MPEG4);
    extraData.setFps(COMMON_VIDEO_DEFAULT_FPS);
    extraData.setWidth(COMMON_VIDEO_DEFAULT_WIDTH);
    extraData.setHeight(COMMON_VIDEO_DEFAULT_HEIGHT);

    // coloca dado na queue de envio e dorme um pouco pra ele ser enviado
    queue_enqueue(_qSendV, _data, buffersize, timestamp, &extraData);

    // espera chegar na de recebimento e compara os dados
    _ReceiveAndCompare(buffersize, timestamp, _data, &extraData, _qRecvVCons);

    // recebeu os dados, pode parar as nets
    _sendV->stop();
    _recvV->stop();
}


TEST_F(NetSendAndRecvTest, SendAndRecvSeveralBytes)
{
    NetRecvAutomaticTest * receiver = new NetRecvAutomaticTest(NET_TYPE_AUDIO);
    NetSendAutomaticTest * sender = new NetSendAutomaticTest(NET_TYPE_AUDIO);

    receiver->start(LOCAL_IP, LOCAL_PORT, 3000);
    while (!receiver->isRunning()) {
        Milliseconds(1).sleep();
    }
    sender->start(LOCAL_IP, LOCAL_PORT, 2000);
    while (!sender->isRunning()) {
        Milliseconds(1).sleep();
    }

    Milliseconds(500).sleep(); // dá tempo para a as threads começarem

    while (sender->isRunning() || receiver->isRunning()) {
        Milliseconds(10).sleep();
    }

    printf("# Total received: %d \n", receiver->getTotalReceived());
    printf("# Total sent: %d \n", sender->getTotalSent());
    ASSERT_EQ(receiver->getTotalReceived(), sender->getTotalSent());

    delete sender;
    delete receiver;
}

TEST_F(NetSendAndRecvTest, TestRedirect)
{
    queue_t * queueR1, * queueR2, * queueR3;
    uint32_t timestamp;
    uint32_t buffersize;
    queue_consumer_t * consumerR1, * consumerR2, * consumerR3;
    QueueExtraDataAudio extraData;
    NetRecv * receiverRedir1, * receiverRedir2, * receiverRedir3;
    NetRedirItem * redir;

    queueR1 = queue_create();
    queueR2 = queue_create();
    queueR3 = queue_create();
    consumerR1 = queue_registerConsumer(queueR1);
    consumerR2 = queue_registerConsumer(queueR2);
    consumerR3 = queue_registerConsumer(queueR3);

    // redireciona para o ip local mas para 2 portas diferentes da padrão
    NetRedir * redirs;
    redirs = new NetRedir();
    redir = redirs->add(LOCAL_IP, LOCAL_PORT + 1);
    redirs->enable(redir);
    redir = redirs->add(LOCAL_IP, LOCAL_PORT + 2);
    redirs->enable(redir);
    redir = redirs->add(LOCAL_IP, LOCAL_PORT + 4); // é +4 de propósito, pra ninguém receber
    redirs->enable(redir);

    // receiver vai receber os dados e redirecionar para 2 outras portas
    _recvA->start(LOCAL_IP, LOCAL_PORT);
    _recvA->setRedirect(redirs);
    _sendA->start(LOCAL_IP, LOCAL_PORT);

    // monta as nets que vão receber os dados redirecionados
    receiverRedir1 = new NetRecv(NET_TYPE_AUDIO, queueR1);
    receiverRedir1->start(LOCAL_IP, LOCAL_PORT + 1);
    receiverRedir2 = new NetRecv(NET_TYPE_AUDIO, queueR2);
    receiverRedir2->start(LOCAL_IP, LOCAL_PORT + 2);
    // e uma que não deve receber nada
    receiverRedir3 = new NetRecv(NET_TYPE_AUDIO, queueR3);
    receiverRedir3->start(LOCAL_IP, LOCAL_PORT + 3); // é +3 para não receber nada!

    Milliseconds(400).sleep(); // para as threads das nets iniciarem

    // monta os dados de envio e zera os de recebimento
    buffersize = DATA_SIZE;
    timestamp = 50;
    memset(_data, 'a', DATA_SIZE/2);
    memset(_data+2500, '8', DATA_SIZE/2);
    extraData.setAudioFlags(QueueExtraDataAudio::AUDIO_ID_3);
    extraData.setBitrate(128);
    extraData.setCodecId(COMMON_CODEC_AUDIO_MP2);

    // coloca dado na queue de envio e espera um pouco pra ele ser enviado
    queue_enqueue(_qSendA, _data, buffersize, timestamp, &extraData);

    // verifica se dados estão ok na NetRecv padrão
    _ReceiveAndCompare(buffersize, timestamp, _data, &extraData, _qRecvACons);

    // verifica se os dados chegaram na net do redir 1
    _ReceiveAndCompare(buffersize, timestamp, _data, &extraData, consumerR1);

    // verifica se os dados chegaram na net do redir 2
    _ReceiveAndCompare(buffersize, timestamp, _data, &extraData, consumerR2);

    // garante que a net do redir 3 não recebeu nada
    // e que as outras só receberam 1 (já retirado delas acima)
    EXPECT_EQ(0, queue_length(queueR1));
    EXPECT_EQ(0, queue_length(queueR2));
    EXPECT_EQ(0, queue_length(queueR3));

    // recebeu os dados, pode parar as nets
    _sendA->stop();
    _recvA->stop();

    receiverRedir1->stop();
    delete receiverRedir1;
    receiverRedir2->stop();
    delete receiverRedir2;
    receiverRedir3->stop();
    delete receiverRedir3;

    queue_unregisterConsumer(&consumerR1);
    queue_unregisterConsumer(&consumerR2);
    queue_unregisterConsumer(&consumerR3);
    queue_destroy(&queueR1);
    queue_destroy(&queueR2);
    queue_destroy(&queueR3);
    delete redirs;
}


/**
 * Envia alguns pacotes e cria um NetRecvValidator que deve descartar alguns
 * desses pacotes. Verifica se realmente foram descartados.
 * Usa o NetAudioFlagValidator existente na net.
 */
TEST_F(NetSendAndRecvTest, NetRecvValidatorTest)
{
    uint32_t timestamp;
    uint32_t buffersize;
    QueueExtraDataAudio extraData;
    NetRecvValidator * validator;

    uint8_t buffer[DATA_SIZE];
    memset(buffer, 'a', DATA_SIZE/2);
    memset(buffer+2500, '8', DATA_SIZE/2);

    // descartará pacotes com flag de áudio == AUDIO_ID_5
    validator = new NetAudioFlagValidator(QueueExtraDataAudio::AUDIO_ID_5);

    _recvA->start(LOCAL_IP, LOCAL_PORT);
    _recvA->setPacketValidator(validator);
    _sendA->start(LOCAL_IP, LOCAL_PORT);
    Milliseconds(400).sleep(); // para as threads iniciarem

    // monta os dados de envio e zera os de recebimento
    buffersize = DATA_SIZE;
    timestamp = 50;
    extraData.setBitrate(128);
    extraData.setCodecId(COMMON_CODEC_AUDIO_MP2);

    // coloca dados na queue de envio

    extraData.setAudioFlags(QueueExtraDataAudio::AUDIO_ID_3);
    //_data = (uint8_t *)queue_malloc(DATA_SIZE);
    memcpy(_data, buffer, DATA_SIZE);
    queue_enqueue(_qSendA, _data, buffersize, timestamp, &extraData);

    extraData.setAudioFlags(QueueExtraDataAudio::AUDIO_ID_4 | QueueExtraDataAudio::AUDIO_ID_1);
    _data = (uint8_t *)queue_malloc(DATA_SIZE);
    memcpy(_data, buffer, DATA_SIZE);
    queue_enqueue(_qSendA, _data, buffersize, timestamp, &extraData);

    extraData.setAudioFlags(QueueExtraDataAudio::AUDIO_ID_5);
    _data = (uint8_t *)queue_malloc(DATA_SIZE);
    memcpy(_data, buffer, DATA_SIZE);
    queue_enqueue(_qSendA, _data, buffersize, timestamp, &extraData);

    extraData.setAudioFlags(QueueExtraDataAudio::AUDIO_ID_2);
    _data = (uint8_t *)queue_malloc(DATA_SIZE);
    memcpy(_data, buffer, DATA_SIZE);
    queue_enqueue(_qSendA, _data, buffersize, timestamp, &extraData);

    extraData.setAudioFlags(QueueExtraDataAudio::AUDIO_ID_5 | QueueExtraDataAudio::AUDIO_ID_2);
    _data = (uint8_t *)queue_malloc(DATA_SIZE);
    memcpy(_data, buffer, DATA_SIZE);
    queue_enqueue(_qSendA, _data, buffersize, timestamp, &extraData);

    common_sleep(500); // pra dar tempo suficiente pro killer agir

    // vai aceitar 2 frames e descartar 2 outros

    extraData.setAudioFlags(QueueExtraDataAudio::AUDIO_ID_3);
    _ReceiveAndCompare(buffersize, timestamp, buffer, &extraData, _qRecvACons);

    extraData.setAudioFlags(QueueExtraDataAudio::AUDIO_ID_4 | QueueExtraDataAudio::AUDIO_ID_1);
    _ReceiveAndCompare(buffersize, timestamp, buffer, &extraData, _qRecvACons);

    extraData.setAudioFlags(QueueExtraDataAudio::AUDIO_ID_2);
    _ReceiveAndCompare(buffersize, timestamp, buffer, &extraData, _qRecvACons);

    // frames já foram tirados da queue acima, então queue tem que estar vazia
    EXPECT_EQ(0, queue_lengthCons(_qRecvACons));

    // recebeu os dados, pode parar as nets
    _sendA->stop();
    _recvA->stop();
}


/**
 * Testa a validação dos pacotes conforme o ID da sessão.
 */
TEST_F(NetSendAndRecvTest, NetSessionIDValidation)
{
    uint32_t timestamp;
    uint32_t buffersize;
    QueueExtraDataAudio extraData;
    NetRecvValidator * validator;

    uint8_t buffer[DATA_SIZE];
    memset(buffer, 'a', DATA_SIZE/2);
    memset(buffer+2500, '8', DATA_SIZE/2);

    _recvA->start(LOCAL_IP, LOCAL_PORT);
    _sendA->start(LOCAL_IP, LOCAL_PORT);
    Milliseconds(400).sleep(); // para as threads iniciarem

    // monta os dados de envio e zera os de recebimento
    buffersize = DATA_SIZE;
    timestamp = 50;


    ////// ETAPA 1: sessionIds iguais

    _recvA->setSessionId(2);
    _sendA->setSessionId(2);

    // coloca dados na queue de envio
    memcpy(_data, buffer, DATA_SIZE);
    queue_enqueue(_qSendA, _data, buffersize, timestamp, NULL);
    _data = (uint8_t *)queue_malloc(DATA_SIZE);
    memcpy(_data, buffer, DATA_SIZE);
    queue_enqueue(_qSendA, _data, buffersize, timestamp, NULL);
    _data = (uint8_t *)queue_malloc(DATA_SIZE);
    memcpy(_data, buffer, DATA_SIZE);
    queue_enqueue(_qSendA, _data, buffersize, timestamp, NULL);

    common_sleep(500);

    // deve ter recebido todos os pacotes, pois as nets têm o mesmo sessionId
    _ReceiveAndCompare(buffersize, timestamp, buffer, &extraData, _qRecvACons);
    _ReceiveAndCompare(buffersize, timestamp, buffer, &extraData, _qRecvACons);
    _ReceiveAndCompare(buffersize, timestamp, buffer, &extraData, _qRecvACons);
    // frames já foram tirados da queue acima, então queue tem que estar vazia
    EXPECT_EQ(0, queue_lengthCons(_qRecvACons));


    ////// ETAPA 2: sessionIds diferentes

    _recvA->setSessionId(1);
    _sendA->setSessionId(2);

    // coloca dados na queue de envio
    memcpy(_data, buffer, DATA_SIZE);
    queue_enqueue(_qSendA, _data, buffersize, timestamp, NULL);
    _data = (uint8_t *)queue_malloc(DATA_SIZE);
    memcpy(_data, buffer, DATA_SIZE);
    queue_enqueue(_qSendA, _data, buffersize, timestamp, NULL);
    _data = (uint8_t *)queue_malloc(DATA_SIZE);
    memcpy(_data, buffer, DATA_SIZE);
    queue_enqueue(_qSendA, _data, buffersize, timestamp, NULL);

    // não pode ter recebido nenhum dado. todos descartados pois o sessionId é diferente
    EXPECT_EQ(0, queue_lengthCons(_qRecvACons));

    common_sleep(500);

    EXPECT_EQ(0, queue_lengthCons(_qRecvACons));


    // finalização
    _sendA->stop();
    _recvA->stop();
}

