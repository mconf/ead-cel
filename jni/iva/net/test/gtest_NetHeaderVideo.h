#ifndef _NET_VIDEO_HEADER_TEST_H_
#define _NET_VIDEO_HEADER_TEST_H_

#include <gtest/gtest.h>
#include <NetHeaderVideo.h>

class NetHeaderVideoTest : public ::testing::Test
{
protected:
    NetHeaderVideo * _header;
    static const int BUFFER_SIZE = 1024;

    virtual void SetUp()
    {
        _header = new NetHeaderVideo();
    }

    virtual void TearDown()
    {
        delete _header;
    }

};

#endif
