#include "gtest_icmp.h"

IcmpTest::IcmpTest()
{
}

IcmpTest::~IcmpTest()
{
}

void IcmpTest::SetUp()
{
}

void IcmpTest::TearDown()
{
}

TEST_F(IcmpTest, Far)
{
    IPv4 ip("64.233.163.104");
    Icmp icmp(ip);
    ASSERT_TRUE(icmp.isReachable());
    int numHopsEstimated = icmp.getNumHopsEstimated();
    int numHops = icmp.getNumHops();
    int rtt = icmp.getRTT();
    cout << "numHops: " << numHops << endl;
    cout << "numHopsEstimated: " << numHopsEstimated << endl;
    cout << "rtt: " << rtt << endl;
    ASSERT_NE(0, numHops);
    ASSERT_NE(0, numHopsEstimated);
    ASSERT_NE(0, rtt);
    ASSERT_GE(3, abs(numHops - numHopsEstimated));
}

TEST_F(IcmpTest, Berkeley)
{
    IPv4 ip("169.229.131.81");
    Icmp icmp(ip);
    ASSERT_TRUE(icmp.isReachable());
    int numHopsEstimated = icmp.getNumHopsEstimated();
    int numHops = icmp.getNumHops();
    int rtt = icmp.getRTT();
    cout << "numHops: " << numHops << endl;
    cout << "numHopsEstimated: " << numHopsEstimated << endl;
    cout << "rtt: " << rtt << endl;
    ASSERT_NE(0, numHops);
    ASSERT_NE(0, numHopsEstimated);
    ASSERT_NE(0, rtt);
    ASSERT_GE(3, abs(numHops - numHopsEstimated));
}

TEST_F(IcmpTest, HostNotFound)
{
	IPv4 ip("64.233.163.103");
	Icmp icmp(ip);
    ASSERT_FALSE(icmp.isReachable());
}

TEST_F(IcmpTest, Local)
{
    IPv4 ip("143.54.132.132");
    Icmp icmp(ip);
    ASSERT_TRUE(icmp.isReachable());
    int numHopsEstimated = icmp.getNumHopsEstimated();
    int numHops = icmp.getNumHops();
    int rtt = icmp.getRTT();
    cout << "numHops: " << numHops << endl;
    cout << "numHopsEstimated: " << numHopsEstimated << endl;
    cout << "rtt: " << rtt << endl;
    ASSERT_EQ(1, numHopsEstimated);
    ASSERT_EQ(1, numHops);
    ASSERT_EQ(0, rtt);
    ASSERT_EQ(numHops, numHopsEstimated);
}

TEST_F(IcmpTest, LocalHost)
{
    IPv4 ip("127.0.0.1");
    Icmp icmp(ip);
    ASSERT_TRUE(icmp.isReachable());
    int numHopsEstimated = icmp.getNumHopsEstimated();
    int numHops = icmp.getNumHops();
    int rtt = icmp.getRTT();
    cout << "numHops: " << numHops << endl;
    cout << "numHopsEstimated: " << numHopsEstimated << endl;
    cout << "rtt: " << rtt << endl;
    ASSERT_EQ(1, numHopsEstimated);
    ASSERT_EQ(1, numHops);
    ASSERT_EQ(0, rtt);
    ASSERT_EQ(numHops, numHopsEstimated);
}
