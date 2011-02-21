#ifndef _NET_RECV_TEST_H_
#define _NET_RECV_TEST_H_

#include <gtest/gtest.h>
#include <NetRecv.h>

class NetRecvTest : public ::testing::Test
{
protected:
    NetRecv * _net;

    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }
};

#endif
