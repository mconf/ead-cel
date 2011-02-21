#ifndef _GTEST_UDP_H_
#define _GTEST_UDP_H_

#include <SocketUDP.h>

#include <gtest/gtest.h>
#include <iostream>
#include <errno.h>
#include <string>

using namespace std;


namespace {

  class udp :
    public ::testing::Test
  {

  protected:
    
    udp();

    virtual ~udp();
    
    virtual void SetUp();

    virtual void TearDown();

  };

};

#endif

