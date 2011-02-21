#ifndef _NET_STATISTICS_TEST_H_
#define _NET_STATISTICS_TEST_H_

#include <gtest/gtest.h>
#include <NetStatistics.h>

class NetStatisticsTest : public ::testing::Test
{
protected:
    NetStatistics * _stats;

    void _SetAndCheckRandomValue(string param, bool clear = false);

    virtual void SetUp()
    {
        srand((unsigned int)time(NULL));
        _stats = new NetStatistics();
    }

    virtual void TearDown()
    {
        delete _stats;
    }

};

#endif
