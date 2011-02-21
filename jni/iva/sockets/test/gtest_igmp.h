#ifndef _GTEST_IGMP_H_
#define _GTEST_IGMP_H_

#include <Igmp.h>
#include <IgmpPcap.h>
#include <IgmpSender.h>

#include <gtest/gtest.h>
#include <iostream>
#include <errno.h>
#include <string>

using namespace std;


namespace {

  class IgmpTest :
    public ::testing::Test
  {

  protected:
    
    IgmpTest();

    virtual ~IgmpTest();
    
    virtual void SetUp();

    virtual void TearDown();

  };

};

#endif

