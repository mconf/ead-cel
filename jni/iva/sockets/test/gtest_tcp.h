#ifndef _GTEST_TCP_H_
#define _GTEST_TCP_H_

#include <SocketTCP.h>

#include <gtest/gtest.h>
#include <iostream>
#include <errno.h>
#include <string>

using namespace std;


namespace {

  class tcp :
    public ::testing::Test
  {

  protected:
    
    tcp();

    virtual ~tcp();
    
    virtual void SetUp();

    virtual void TearDown();

  };

};

#endif

