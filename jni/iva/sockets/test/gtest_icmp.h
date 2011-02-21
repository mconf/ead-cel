#ifndef _GTEST_ICMP_H
#define _GTEST_ICMP_H

#include <Icmp.h>

#include <gtest/gtest.h>
#include <iostream>
#include <errno.h>
#include <string>

using namespace std;

namespace 
{
  class IcmpTest :
    public ::testing::Test
  {

  protected:
    
    IcmpTest();

    virtual ~IcmpTest();
    
    virtual void SetUp();

    virtual void TearDown();

  };


};

#endif /* _GTEST_ICMP_H */