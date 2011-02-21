#include <time.h>
#include <NetHeader.h>
#include "gtest_NetStatistics.h"

TEST_F(NetStatisticsTest, Initialization)
{
    // garante que tudo inicia zerado
    EXPECT_EQ(0, _stats->getAttr(NetStatistics::ATTR_RECEIVED_PACKETS));
    EXPECT_EQ(0, _stats->getAttr(NetStatistics::ATTR_RECEIVED_FRAMES));
    EXPECT_EQ(0, _stats->getAttr(NetStatistics::ATTR_RECEIVED_BYTES));
    EXPECT_EQ(0, _stats->getAttr(NetStatistics::ATTR_RECEIVED_AV_BYTES));
    EXPECT_EQ(0, _stats->getAttr(NetStatistics::ATTR_SENT_PACKETS));
    EXPECT_EQ(0, _stats->getAttr(NetStatistics::ATTR_SENT_FRAMES));
    EXPECT_EQ(0, _stats->getAttr(NetStatistics::ATTR_SENT_BYTES));
    EXPECT_EQ(0, _stats->getAttr(NetStatistics::ATTR_DISCARDED_FRAMES));
    EXPECT_EQ(0, _stats->getAttr(NetStatistics::ATTR_DISCARDED_BYTES));
    EXPECT_EQ(0, _stats->getAttr(NetStatistics::ATTR_REDIRECTED_PACKETS));
    EXPECT_EQ(0, _stats->getAttr(NetStatistics::ATTR_REDIRECTED_BYTES));
    EXPECT_EQ(0, _stats->getAttr(NetStatistics::ATTR_LAST_TIMESTAMP));
}

TEST_F(NetStatisticsTest, SetAndGetAttrs)
{
    for (int i = 0; i < 50; i++) {
        _SetAndCheckRandomValue(NetStatistics::ATTR_RECEIVED_PACKETS);
        _SetAndCheckRandomValue(NetStatistics::ATTR_RECEIVED_FRAMES);
        _SetAndCheckRandomValue(NetStatistics::ATTR_RECEIVED_BYTES);
        _SetAndCheckRandomValue(NetStatistics::ATTR_SENT_PACKETS);
        _SetAndCheckRandomValue(NetStatistics::ATTR_SENT_FRAMES);
        _SetAndCheckRandomValue(NetStatistics::ATTR_SENT_BYTES);
        _SetAndCheckRandomValue(NetStatistics::ATTR_DISCARDED_BYTES);
        _SetAndCheckRandomValue(NetStatistics::ATTR_REDIRECTED_PACKETS);
        _SetAndCheckRandomValue(NetStatistics::ATTR_REDIRECTED_BYTES);
        _SetAndCheckRandomValue(NetStatistics::ATTR_LAST_TIMESTAMP);
    }
}

void NetStatisticsTest::_SetAndCheckRandomValue(string param, bool clear)
{
    int iRand = rand() % 10000;
    _stats->setAttr(param, iRand);
    EXPECT_EQ(iRand, _stats->getAttr(param));
    if (clear) {
        _stats->clearAttr(param);
        EXPECT_EQ(0, _stats->getAttr(param));
    }
}

TEST_F(NetStatisticsTest, ClearAttr)
{
    _SetAndCheckRandomValue(NetStatistics::ATTR_RECEIVED_PACKETS, true);
    _SetAndCheckRandomValue(NetStatistics::ATTR_RECEIVED_FRAMES, true);
    _SetAndCheckRandomValue(NetStatistics::ATTR_RECEIVED_BYTES, true);
    _SetAndCheckRandomValue(NetStatistics::ATTR_SENT_PACKETS, true);
    _SetAndCheckRandomValue(NetStatistics::ATTR_SENT_FRAMES, true);
    _SetAndCheckRandomValue(NetStatistics::ATTR_SENT_BYTES, true);
    _SetAndCheckRandomValue(NetStatistics::ATTR_DISCARDED_BYTES, true);
    _SetAndCheckRandomValue(NetStatistics::ATTR_REDIRECTED_PACKETS, true);
    _SetAndCheckRandomValue(NetStatistics::ATTR_REDIRECTED_BYTES, true);
    _SetAndCheckRandomValue(NetStatistics::ATTR_LAST_TIMESTAMP, true);
}

TEST_F(NetStatisticsTest, ZeroAll)
{
    // seta valores quaisquer
    _SetAndCheckRandomValue(NetStatistics::ATTR_RECEIVED_PACKETS);
    _SetAndCheckRandomValue(NetStatistics::ATTR_RECEIVED_FRAMES);
    _SetAndCheckRandomValue(NetStatistics::ATTR_RECEIVED_BYTES);
    _SetAndCheckRandomValue(NetStatistics::ATTR_SENT_PACKETS);
    _SetAndCheckRandomValue(NetStatistics::ATTR_SENT_FRAMES);
    _SetAndCheckRandomValue(NetStatistics::ATTR_SENT_BYTES);
    _SetAndCheckRandomValue(NetStatistics::ATTR_DISCARDED_BYTES);
    _SetAndCheckRandomValue(NetStatistics::ATTR_REDIRECTED_PACKETS);
    _SetAndCheckRandomValue(NetStatistics::ATTR_REDIRECTED_BYTES);
    _SetAndCheckRandomValue(NetStatistics::ATTR_LAST_TIMESTAMP);

    _stats->zeroAll();

    // todos devem estar zerados
    EXPECT_EQ(0, _stats->getAttr(NetStatistics::ATTR_RECEIVED_PACKETS));
    EXPECT_EQ(0, _stats->getAttr(NetStatistics::ATTR_RECEIVED_FRAMES));
    EXPECT_EQ(0, _stats->getAttr(NetStatistics::ATTR_RECEIVED_BYTES));
    EXPECT_EQ(0, _stats->getAttr(NetStatistics::ATTR_SENT_PACKETS));
    EXPECT_EQ(0, _stats->getAttr(NetStatistics::ATTR_SENT_FRAMES));
    EXPECT_EQ(0, _stats->getAttr(NetStatistics::ATTR_SENT_BYTES));
    EXPECT_EQ(0, _stats->getAttr(NetStatistics::ATTR_DISCARDED_BYTES));
    EXPECT_EQ(0, _stats->getAttr(NetStatistics::ATTR_REDIRECTED_PACKETS));
    EXPECT_EQ(0, _stats->getAttr(NetStatistics::ATTR_REDIRECTED_BYTES));
    EXPECT_EQ(0, _stats->getAttr(NetStatistics::ATTR_LAST_TIMESTAMP));
}

