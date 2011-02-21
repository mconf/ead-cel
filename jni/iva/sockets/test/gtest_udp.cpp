#include "gtest_udp.h"

udp::udp()
{
#ifdef _MSC_VER
    common_init();
#endif
}

udp::~udp()
{
#ifdef _MSC_VER
    common_end();
#endif
}

void udp::SetUp()
{
}

void udp::TearDown()
{
}

#define PORT1       12000
#define PORT2       12001
#define BUFFERSIZE  1024
string sendbuffer;
char recvbuffer[BUFFERSIZE];

const string multicast("239.5.6.7");
const string localhost("127.0.0.1");

TEST_F(udp, normal_blocking_unicast)
{
    SocketUDP* sender,* receiver;

    ASSERT_NO_THROW(sender = new SocketUDP());
    ASSERT_NO_THROW(receiver = new SocketUDP());

    ASSERT_EQ(E_OK, sender->openAsSender(localhost, PORT1, true));
    ASSERT_EQ(E_OK, receiver->openAsReceiver(PORT1, true));

    sendbuffer = "";
    for (int i = 0; i < BUFFERSIZE; ++i)
        sendbuffer += i % 10 + 'a';

    ASSERT_EQ(BUFFERSIZE, sender->send(sendbuffer));
    ASSERT_EQ(BUFFERSIZE, receiver->recv(recvbuffer, BUFFERSIZE));

    ASSERT_EQ(BUFFERSIZE, sender->send(sendbuffer.c_str(), BUFFERSIZE));
    ASSERT_EQ(BUFFERSIZE, receiver->recv(sendbuffer));

    ASSERT_EQ(BUFFERSIZE, (*sender) << sendbuffer);
    ASSERT_EQ(BUFFERSIZE, (*receiver) >> sendbuffer);

    delete receiver;
    delete sender;
}

TEST_F(udp, normal_nonblocking_multicast)
{
    SocketUDP* sender,* receiver;

    ASSERT_NO_THROW(sender = new SocketUDP());
    ASSERT_NO_THROW(receiver = new SocketUDP());

    ASSERT_EQ(E_OK, sender->openAsSender(multicast, PORT1, false));
    ASSERT_EQ(E_OK, receiver->openAsReceiver(multicast, PORT1, false));

    sendbuffer = "";
    for (int i = 0; i < BUFFERSIZE; ++i)
        sendbuffer += i % 10 + 'a';

    ASSERT_EQ(BUFFERSIZE, sender->send(sendbuffer));
    ASSERT_NE(0, receiver->waitRead());
    ASSERT_EQ(BUFFERSIZE, receiver->recv(recvbuffer, BUFFERSIZE));

    ASSERT_EQ(BUFFERSIZE, sender->send(sendbuffer.c_str(), BUFFERSIZE));
    ASSERT_NE(0, receiver->waitRead());
    ASSERT_EQ(BUFFERSIZE, receiver->recv(recvbuffer, BUFFERSIZE));

    ASSERT_EQ(BUFFERSIZE, (*sender) << sendbuffer);
    ASSERT_NE(0, receiver->waitRead());
    ASSERT_EQ(BUFFERSIZE, (*receiver) >> sendbuffer);

    // deve dar erro pois não é bloqueante e ninguém enviou nada
    ASSERT_EQ(SOCKET_ERROR, receiver->recv(recvbuffer, BUFFERSIZE));

    ASSERT_EQ(E_OK, receiver->setblocking(true));
    ASSERT_EQ(E_OK, receiver->setblocking(false));

    ASSERT_EQ(0, receiver->waitRead());
    ASSERT_EQ(SOCKET_ERROR, receiver->recv(recvbuffer, BUFFERSIZE));

    delete receiver;
    delete sender;
}

TEST_F(udp, inverting)
{
    SocketUDP* sender,* receiver;

    ASSERT_NO_THROW(sender = new SocketUDP());
    ASSERT_NO_THROW(receiver = new SocketUDP());

    ASSERT_EQ(E_OK, sender->openAsSender(localhost, PORT1, true));
    ASSERT_EQ(E_OK, receiver->openAsReceiver(PORT1, true));

    sendbuffer = "";
    for (int i = 0; i < BUFFERSIZE; ++i)
        sendbuffer += i % 10 + 'a';

    ASSERT_EQ(BUFFERSIZE, sender->send(sendbuffer));
    ASSERT_EQ(BUFFERSIZE, receiver->recv(recvbuffer, BUFFERSIZE));
/*
    ASSERT_EQ(E_OK, sender->close());
    ASSERT_EQ(E_OK, receiver->close());
*/
    ASSERT_EQ(E_OK, receiver->openAsSender(localhost, PORT1, true));
    ASSERT_EQ(E_OK, sender->openAsReceiver(PORT1, true));

    ASSERT_EQ(BUFFERSIZE, receiver->send(sendbuffer));
    ASSERT_EQ(BUFFERSIZE, sender->recv(recvbuffer, BUFFERSIZE));

    ASSERT_EQ(BUFFERSIZE, receiver->send(sendbuffer.c_str(), BUFFERSIZE));
    ASSERT_EQ(BUFFERSIZE, sender->recv(sendbuffer));

    ASSERT_EQ(BUFFERSIZE, (*receiver) << sendbuffer);
    ASSERT_EQ(BUFFERSIZE, (*sender) >> sendbuffer);

    delete receiver;
    delete sender;
}
