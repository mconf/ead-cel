#include <gtest/gtest.h>
#include <iostream>
#include <errno.h>
#include <SocketUDP.h>

using namespace std;

namespace {

  class SocketUDPTest :
    public ::testing::Test
  {

  protected:
    
    SocketUDPTest()
    {
    }

    virtual ~SocketUDPTest()
    {
    }
    
    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }

  };

};

TEST_F(SocketUDPTest, Test)
{
    SocketUDP* socket;
    ASSERT_NO_THROW(socket = new SocketUDP());

    ASSERT_EQ(E_OK, socket->openAsReceiver("239.99.99.99", 12000, false));

    system("pause");

    ASSERT_EQ(E_OK, socket->close());
    delete socket;    
}

int main(int argc, char **argv) {

	::testing::InitGoogleTest(&argc, argv);

    if (RUN_ALL_TESTS() != 0){}
        system("PAUSE");

	return 0;
}