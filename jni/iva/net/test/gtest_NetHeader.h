#ifndef _NET_HEADER_TEST_H_
#define _NET_HEADER_TEST_H_

#include <gtest/gtest.h>
#include <NetHeader.h>

class NetHeaderTest : public ::testing::Test
{
protected:
    NetHeader * _header;
    static const int BUFFER_SIZE = 1024;

    virtual void SetUp()
    {
        _header = new NetHeader();
    }

    virtual void TearDown()
    {
        delete _header;
    }

};

#endif
