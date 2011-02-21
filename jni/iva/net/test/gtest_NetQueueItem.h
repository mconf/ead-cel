#ifndef _NET_QUEUE_ITEM_TEST_H_
#define _NET_QUEUE_ITEM_TEST_H_

#include <gtest/gtest.h>
#include <NetQueueItem.h>

class NetQueueItemTest : public ::testing::Test
{
protected:
    NetQueueItem * _item;
    static const int FRAME_SIZE = 36000;
    static const int FRAGS = 36;
    static const int FRAG_SIZE = 1024; // 1024 * 35 = 35840

    virtual void SetUp()
    {
        _item = new NetQueueItem(FRAME_SIZE, FRAG_SIZE);
    }

    virtual void TearDown()
    {
        delete _item;
    }

};

#endif
