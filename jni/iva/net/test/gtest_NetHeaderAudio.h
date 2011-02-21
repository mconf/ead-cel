#ifndef _NET_AUDIO_HEADER_TEST_H_
#define _NET_AUDIO_HEADER_TEST_H_

#include <gtest/gtest.h>
#include <NetHeaderAudio.h>

class NetHeaderAudioTest : public ::testing::Test
{
protected:
    NetHeaderAudio * _header;
    static const int BUFFER_SIZE = 1024;

    virtual void SetUp()
    {
        _header = new NetHeaderAudio();
    }

    virtual void TearDown()
    {
        delete _header;
    }

};

#endif
