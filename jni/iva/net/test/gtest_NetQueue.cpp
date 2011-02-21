#include <errorDefs.h>
#include "gtest_NetQueue.h"

TEST_F(NetQueueTest, Initialization)
{
    ASSERT_TRUE(_q->isEmpty());
    ASSERT_FALSE(_q->isFull());
    ASSERT_TRUE(_q->first() == NULL);
    ASSERT_TRUE(_q->last() == NULL);
    ASSERT_EQ(0, _q->size());
}

TEST_F(NetQueueTest, BasicEnqueueAndDequeue)
{
     NetQueueItem * item;

    item = _q->enqueue(_pAud);
    ASSERT_TRUE(item != NULL);
    ASSERT_TRUE(_q->first() != NULL);
    ASSERT_TRUE(_q->last() != NULL);

    _q->dequeue();
    ASSERT_TRUE(_q->first() == NULL);
    ASSERT_TRUE(_q->last() == NULL);

    _q->clear(); // pra "esquecer" que já recebeu um pacote antes

    item = _q->enqueue(_pVid);
    ASSERT_TRUE(item != NULL);
    ASSERT_TRUE(_q->first() != NULL);
    ASSERT_TRUE(_q->last() != NULL);

    _q->dequeue();
    ASSERT_TRUE(_q->first() == NULL);
    ASSERT_TRUE(_q->last() == NULL);
}

TEST_F(NetQueueTest, EnqueueAndClear)
{
    NetQueueItem * item;

    _hAud->setAttrAsInt(NetHeaderAudio::ATTR_SEQNUM, 0);
    item = _q->enqueue(_pAud);
    ASSERT_TRUE(item != NULL);
    ASSERT_EQ(1, _q->size());

    _hAud->setAttrAsInt(NetHeaderAudio::ATTR_SEQNUM, 1);
    item = _q->enqueue(_pAud);
    ASSERT_TRUE(item != NULL);
    ASSERT_EQ(2, _q->size());

    _q->clear();
    ASSERT_EQ(0, _q->size());
    ASSERT_TRUE(_q->first() == NULL);
    ASSERT_TRUE(_q->last() == NULL);
}

TEST_F(NetQueueTest, LimitMaxNumberOfItems)
{
    NetQueueItem * item;

    for (int i = 0; i < NetQueue::DEFAULT_MAX_SIZE*2; i++) {
        _hAud->setAttrAsInt(NetHeaderAudio::ATTR_SEQNUM, i);
        item = _q->enqueue(_pAud);
        if (i < NetQueue::DEFAULT_MAX_SIZE) {
            ASSERT_TRUE(item != NULL);
        } else {
            ASSERT_TRUE(item == NULL);
        }
        ASSERT_TRUE(_q->first() != NULL);
        ASSERT_TRUE(_q->last() != NULL);
    }
    // garante que último seqnum e tamanho da queue estão certos
    ASSERT_EQ(NetQueue::DEFAULT_MAX_SIZE - 1, _q->last()->getSequenceNumber());
    ASSERT_EQ(NetQueue::DEFAULT_MAX_SIZE, _q->size());
}

TEST_F(NetQueueTest, StoreOneFragmentedFrame)
{
    NetQueueItem * item;

    int numFrags = (int)(floor(PACK_VIDEO_FRAMESIZE / (float)PACK_VIDEO_DATASIZE));
    if ( PACK_VIDEO_FRAMESIZE / (float)PACK_VIDEO_DATASIZE  > numFrags) {
        numFrags++;
    }

    for (int i = 0; i < numFrags; i++) {
        if (i == numFrags - 1) { // ajusta tamanho do último fragmento
            _MountVideoPacket(PACK_VIDEO_FRAMESIZE - PACK_VIDEO_DATASIZE*i);
        }
        _hVid->setAttrAsInt(NetHeaderVideo::ATTR_FRAGNUM, i);
        item = _q->enqueue(_pVid);
        ASSERT_TRUE(item != NULL);
        ASSERT_TRUE(_q->first() != NULL);
        ASSERT_TRUE(_q->last() != NULL);
        ASSERT_EQ(1, _q->size());
        if (i == numFrags - 1) {
            ASSERT_TRUE(_q->first()->isComplete());
        } else {
            ASSERT_FALSE(_q->first()->isComplete());
        }
    }
}

TEST_F(NetQueueTest, StoreSeveralFragmentedFramesIntercalated)
{
    NetQueueItem * item;

    int numFrags = (int)(floor(PACK_VIDEO_FRAMESIZE / (float)PACK_VIDEO_DATASIZE));
    if ( PACK_VIDEO_FRAMESIZE / (float)PACK_VIDEO_DATASIZE  > numFrags) {
        numFrags++;
    }

    // um fragmento de cada frame até completar todos
    for (int i = 0; i < numFrags; i++) {
        if (i == numFrags - 1) { // ajusta tamanho do último fragmento
            _MountVideoPacket(PACK_VIDEO_FRAMESIZE - PACK_VIDEO_DATASIZE*i);
        }
        _hVid->setAttrAsInt(NetHeaderVideo::ATTR_FRAGNUM, i);

        // para todos os frames...
        for (int j = 0; j < NetQueue::DEFAULT_MAX_SIZE; j++) {
            _hVid->setAttrAsInt(NetHeaderAudio::ATTR_SEQNUM, j);
            item = _q->enqueue(_pVid);
            ASSERT_TRUE(item != NULL);
            ASSERT_TRUE(_q->first() != NULL);
            ASSERT_TRUE(_q->last() != NULL);
            if (i == numFrags - 1) {
                ASSERT_TRUE(_q->first()->isComplete());
            } else {
                ASSERT_FALSE(_q->first()->isComplete());
            }
        }
        ASSERT_EQ(NetQueue::DEFAULT_MAX_SIZE, _q->size());
    }
}

TEST_F(NetQueueTest, CheckIfDataIsCorrectInsideBuffers)
{
    NetQueueItem * item;

    int packVideoDatasizeOriginal = PACK_VIDEO_DATASIZE;
    int numFrags = (int)(floor(PACK_VIDEO_FRAMESIZE / (float)PACK_VIDEO_DATASIZE));
    if ( PACK_VIDEO_FRAMESIZE / (float)PACK_VIDEO_DATASIZE  > numFrags) {
        numFrags++;
    }

    // um fragmento de cada frame até completar todos
    for (int i = 0; i < numFrags; i++) {
        if (i == numFrags - 1) { // ajusta tamanho do último fragmento
            _MountVideoPacket(PACK_VIDEO_FRAMESIZE - PACK_VIDEO_DATASIZE*i);
        }
        unsigned char * pVidData = _pVid->getPayloadPointer();
        memset(pVidData, '8', PACK_VIDEO_DATASIZE); // seta o buffer do pacote

        _hVid->setAttrAsInt(NetHeaderVideo::ATTR_FRAGNUM, i);
        item = _q->enqueue(_pVid);
        ASSERT_TRUE(item != NULL);
        ASSERT_TRUE(_q->first() != NULL);
        ASSERT_TRUE(_q->last() != NULL);

        // garante que dados no item são iguais do pacote
        // e que estão na posição certa conforme o fragmento inserido
        unsigned char * itemData = item->getData();
        for (int j = 0; j < PACK_VIDEO_DATASIZE; j++) {
            ASSERT_EQ('8', itemData[i*packVideoDatasizeOriginal + j]);
        }
    }
}

TEST_F(NetQueueTest, DiscardPacketsTooLate)
{
    NetQueueItem * item;

    // insere 10 items começando no seqnum 50
    for (int i = 50; i < 60; i++) {
        _hAud->setAttrAsInt(NetHeaderAudio::ATTR_SEQNUM, i);
        item = _q->enqueue(_pAud);
        ASSERT_TRUE(item != NULL);
    }

    // tenta inserir outros pacotes com seqnum menor
    _hAud->setAttrAsInt(NetHeaderAudio::ATTR_SEQNUM, 10);
    item = _q->enqueue(_pAud);
    ASSERT_TRUE(item == NULL);
    _hAud->setAttrAsInt(NetHeaderAudio::ATTR_SEQNUM, 49);
    item = _q->enqueue(_pAud);
    ASSERT_TRUE(item == NULL);

    ASSERT_EQ(10, _q->size());
}

TEST_F(NetQueueTest, DiscardPacketsTooEarly)
{
    NetQueueItem * item;

    // insere 10 items começando no seqnum 10 ate 20
    for (int i = 10; i < 20; i++) {
        _hAud->setAttrAsInt(NetHeaderAudio::ATTR_SEQNUM, i);
        item = _q->enqueue(_pAud);
        ASSERT_TRUE(item != NULL);
    }

    // tenta inserir outros pacotes com seqnum maior que o limite da queue
    _hAud->setAttrAsInt(NetHeaderAudio::ATTR_SEQNUM, NetQueue::DEFAULT_MAX_SIZE + 50);
    item = _q->enqueue(_pAud);
    ASSERT_TRUE(item == NULL);
    _hAud->setAttrAsInt(NetHeaderAudio::ATTR_SEQNUM, NetQueue::DEFAULT_MAX_SIZE + 20);
    item = _q->enqueue(_pAud);
    ASSERT_TRUE(item == NULL);

    ASSERT_EQ(10, _q->size());
}

void NetQueueTest::_MountAudioPacket(int dataSize)
{
    Milliseconds ts;
    int size;

    _pAud = new NetPacket(NET_TYPE_AUDIO);
    _hAud = (NetHeaderAudio *)_pAud->getHeader();
    if (dataSize <= 0) {
        size = NetPacket::DEFAULT_PACKSIZE - _hAud->getSize();
    } else {
        size = dataSize;
    }
    _pAud->allocBuffer(size);
    _hAud->setAttrAsInt(NetHeaderAudio::ATTR_BITRATE, 128000);
    _hAud->setAttrAsInt(NetHeaderAudio::ATTR_FLAGS, 0);
    _hAud->setAttrAsInt(NetHeaderAudio::ATTR_CODEC, COMMON_AUDIO_DEFAULT_CODEC);
    _hAud->setAttrAsInt(NetHeaderAudio::ATTR_FRAGNUM, 0);
    _hAud->setAttrAsInt(NetHeaderAudio::ATTR_FRAMESIZE, size);
    _hAud->setAttrAsInt(NetHeaderAudio::ATTR_SEQNUM, 0);
    ts.setTimestamp();
    _hAud->setAttrAsInt(NetHeaderAudio::ATTR_TIMESTAMP, ts.getTime());
}

void NetQueueTest::_MountVideoPacket(int dataSize)
{
    Milliseconds ts;
    ts.setTimestamp();

    if (_pVid) delete _pVid;

    _pVid = new NetPacket(NET_TYPE_VIDEO);
    _hVid = (NetHeaderVideo *)_pVid->getHeader();
    if (dataSize <= 0) {
        PACK_VIDEO_DATASIZE = NetPacket::DEFAULT_PACKSIZE - _hVid->getSize();
    } else {
        PACK_VIDEO_DATASIZE = dataSize;
    }
    _pVid->allocBuffer(PACK_VIDEO_DATASIZE);
    _hVid->setAttrAsInt(NetHeaderVideo::ATTR_FRAMESIZE, PACK_VIDEO_FRAMESIZE);
    _hVid->setAttrAsInt(NetHeaderVideo::ATTR_SEQNUM, 0);
    _hVid->setAttrAsInt(NetHeaderVideo::ATTR_FRAGNUM, 0);
    _hVid->setAttrAsInt(NetHeaderVideo::ATTR_TIMESTAMP, ts.getTime());
    _hVid->setAttrAsInt(NetHeaderVideo::ATTR_WIDTH, 720);
    _hVid->setAttrAsInt(NetHeaderVideo::ATTR_HEIGHT, 480);
    _hVid->setAttrAsInt(NetHeaderVideo::ATTR_FPS, 30);
    _hVid->setAttrAsInt(NetHeaderVideo::ATTR_CODEC, COMMON_VIDEO_DEFAULT_CODEC);
    _hVid->setAttrAsInt(NetHeaderVideo::ATTR_BITRATE, 140000);
    ASSERT_EQ(140000, _hVid->getAttrAsInt(NetHeaderVideo::ATTR_BITRATE));
    ASSERT_EQ(720, _hVid->getAttrAsInt(NetHeaderVideo::ATTR_WIDTH));
    ASSERT_EQ(480, _hVid->getAttrAsInt(NetHeaderVideo::ATTR_HEIGHT));
    ASSERT_EQ(30, _hVid->getAttrAsInt(NetHeaderVideo::ATTR_FPS));
    ASSERT_EQ(COMMON_VIDEO_DEFAULT_CODEC, _hVid->getAttrAsInt(NetHeaderVideo::ATTR_CODEC));
    ASSERT_EQ(0, _hVid->getAttrAsInt(NetHeaderVideo::ATTR_FRAGNUM));
    ASSERT_EQ(PACK_VIDEO_FRAMESIZE, _hVid->getAttrAsInt(NetHeaderVideo::ATTR_FRAMESIZE));
    ASSERT_EQ(0, _hVid->getAttrAsInt(NetHeaderVideo::ATTR_SEQNUM));
    ASSERT_EQ(ts.getTime(), _hVid->getAttrAsInt(NetHeaderVideo::ATTR_TIMESTAMP));
}

