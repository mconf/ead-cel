#ifndef _NET_VIDEO_HEADER_TEST_H_
#define _NET_VIDEO_HEADER_TEST_H_

#include <gtest/gtest.h>
#include <NetHeaderAttr.h>

class NetHeaderAttrTest : public ::testing::Test
{
protected:
    NetHeaderAttr * _attr;

    virtual void SetUp()
    {
        _attr = new NetHeaderAttr(4, NULL);
    }

    virtual void TearDown()
    {
        delete _attr;
    }

};

#endif
