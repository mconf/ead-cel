#include "gtest_igmp.h"

IgmpTest::IgmpTest()
{
}

IgmpTest::~IgmpTest()
{
}

void IgmpTest::SetUp()
{
}

void IgmpTest::TearDown()
{
}

TEST_F(IgmpTest, WinPcap)
{
    IPv4 ip("239.199.199.199");
    IgmpPcap igmp(ip);
    igmp.send();
}

TEST_F(IgmpTest, Sender)
{
    IPv4 ip("239.69.69.69");
    IgmpSender sender(1);
    sender.start(ip);

    system("pause");

    sender.pause();
}