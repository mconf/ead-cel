#include <errorDefs.h>
#include <QueueExtraDataVideo.h>
#include "gtest_NetQueueItem.h"

TEST_F(NetQueueItemTest, Initialization)
{
    ASSERT_TRUE(_item->getData() != NULL) << "Não inicializou dados";
    EXPECT_EQ(FRAME_SIZE, _item->getDataSize());
    EXPECT_EQ(0, _item->getSequenceNumber());
    EXPECT_EQ(0, Milliseconds(_item->getTimestamp()).getTime());
    EXPECT_EQ(0, Milliseconds(_item->getArriveTime()).getTime());
    EXPECT_EQ(0, _item->getTotalReceived());
    EXPECT_TRUE(_item->getExtraData() == NULL);
    EXPECT_EQ(NetQueueItem::FREE, _item->getStatus());
}

TEST_F(NetQueueItemTest, SettersAndGetters)
{
    QueueExtraDataVideo extra;

    _item->setArriveTime(Milliseconds(5000));
    EXPECT_EQ(5000, Milliseconds(_item->getArriveTime()).getTime());

   _item->setExtraData(&extra);
    EXPECT_EQ(&extra, _item->getExtraData());

    _item->setSequenceNumber(4567);
    EXPECT_EQ(4567, _item->getSequenceNumber());

    _item->setTimestamp(Milliseconds(1234));
    EXPECT_EQ(1234, Milliseconds(_item->getTimestamp()).getTime());

    _item->setTotalReceived(10);
    EXPECT_EQ(10, _item->getTotalReceived());
}

TEST_F(NetQueueItemTest, InsertData)
{
    int frag = 0;
    int i, startPos;
    int dataSize = FRAG_SIZE;
    unsigned char * data = (unsigned char *)malloc(dataSize);
    memset(data, 'a', dataSize);

    // fragmento no inicio
    _item->insertData(data, dataSize, 0);
    for (i = 0; i < dataSize; i++) {
        EXPECT_EQ('a', _item->getData()[i]);
    }
    // fragmento no meio
    _item->insertData(data, dataSize, 10);
    startPos = FRAG_SIZE * 10; // posição inicial do frag no buffer
    for (i = 0; i < dataSize; i++) {
        EXPECT_EQ('a', _item->getData()[startPos + i]);
    }
    // último fragmento
    dataSize = FRAME_SIZE - ((FRAGS - 1) * FRAG_SIZE); // tamanho do último frag
    _item->insertData(data, dataSize, FRAGS - 1);
    startPos = FRAG_SIZE * (FRAGS - 1); // posição inicial do frag no buffer
    for (i = 0; i < dataSize; i++) {
        EXPECT_EQ('a', _item->getData()[startPos + i]);
    }

    free(data);
}

TEST_F(NetQueueItemTest, IsCompleteVerification)
{
    int fragSize = 1000;
    int frameSize = 5000;

    NetQueueItem * item2 = new NetQueueItem(frameSize, fragSize);
    unsigned char * data = (unsigned char *)malloc(fragSize);
    memset(data, '8', fragSize);

    EXPECT_FALSE(item2->isComplete());
    for (int i = 0; i < 5; i++) {
        item2->insertData(data, fragSize, i);
        if (i == 4) {
            EXPECT_TRUE(item2->isComplete());
        } else {
            EXPECT_FALSE(item2->isComplete());
        }
    }

    free(data);
    delete item2;
}

TEST_F(NetQueueItemTest, DuplicationTolerance)
{
    int fragSize = 1000;
    int frameSize = 50000;
    int numFrags = frameSize / fragSize;
    int ret;

    NetQueueItem * item2 = new NetQueueItem(frameSize, fragSize);
    unsigned char * data = (unsigned char *)malloc(fragSize);
    memset(data, '8', fragSize);

    EXPECT_FALSE(item2->isComplete());
    // insere todos menos o último
    for (int i = 0; i < numFrags-1; i++) {
        ret = item2->insertData(data, fragSize, i);
        EXPECT_FALSE(item2->isComplete());
        EXPECT_EQ(E_OK, ret);
    }
    // todos de novo (duplicados) e também o último
    for (int i = 0; i < numFrags; i++) {
        ret = item2->insertData(data, fragSize, i);
        if (i == numFrags-1) {
            EXPECT_TRUE(item2->isComplete());
            EXPECT_EQ(E_OK, ret);
        } else {
            EXPECT_FALSE(item2->isComplete());
            EXPECT_NE(E_OK, ret) << "Deveria ter retornado código de erro";
        }
    }

    free(data);
    delete item2;
}
