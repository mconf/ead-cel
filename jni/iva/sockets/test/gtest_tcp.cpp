#include "gtest_tcp.h"

tcp::tcp()
{
}

tcp::~tcp()
{
}

void tcp::SetUp()
{
}

void tcp::TearDown()
{
}

#define PORT1       12000
#define PORT2       12001
#define BUFFERSIZE  1024
string sendbuffer;
char recvbuffer[BUFFERSIZE];

TEST_F(tcp, normal_blocking)
{
    SocketTCP* client,* remoteClient,* server;

    ASSERT_NO_THROW(client = new SocketTCP());
    ASSERT_NO_THROW(server = new SocketTCP());

    ASSERT_EQ(E_OK, server->openAsServer(PORT1, true));

    IPv4 ip("127.0.0.1");

    ASSERT_EQ(E_OK, client->openAsClient(ip, PORT1, true));

    ASSERT_TRUE((remoteClient = server->accept()) != NULL);

    sendbuffer = "";
    for (int i = 0; i < BUFFERSIZE; ++i)
        sendbuffer += i % 10;

    ASSERT_EQ(BUFFERSIZE, client->send(sendbuffer.c_str(), BUFFERSIZE));
    ASSERT_EQ(BUFFERSIZE, remoteClient->recv(recvbuffer, BUFFERSIZE));
    ASSERT_TRUE(string(recvbuffer, BUFFERSIZE) == sendbuffer);

    ASSERT_EQ(BUFFERSIZE, remoteClient->send(sendbuffer));
    ASSERT_EQ(BUFFERSIZE, client->recv(recvbuffer, BUFFERSIZE));
    ASSERT_TRUE(string(recvbuffer, BUFFERSIZE) == sendbuffer);

    ASSERT_EQ(BUFFERSIZE, (*client) << sendbuffer);
    ASSERT_EQ(BUFFERSIZE, remoteClient->recv(recvbuffer, BUFFERSIZE));
    ASSERT_TRUE(string(recvbuffer, BUFFERSIZE) == sendbuffer);

    string testbuffer;
    ASSERT_EQ(BUFFERSIZE, (*client) << sendbuffer);
    ASSERT_EQ(BUFFERSIZE, remoteClient->recv(testbuffer, BUFFERSIZE));
    ASSERT_TRUE(testbuffer == sendbuffer);

    delete remoteClient;
    delete client;
    delete server;
}
/*
TEST_F(TCPtest, udp)
{
    SocketUDPSend* sender;
    SocketUDPRecv* receiver;

    ASSERT_NO_THROW(sender = new SocketUDPSend());
    ASSERT_NO_THROW(receiver = new SocketUDPRecv());

    sender->setblocking(true);
    receiver->setblocking(true);

    ASSERT_EQ(E_OK, receiver->connect(PORT));

    sendbuffer = "";
    for (int i = 0; i < BUFFERSIZE; ++i)
        sendbuffer += (i % 10 + 'a');

    ASSERT_EQ(BUFFERSIZE, sender->sendTo(sendbuffer.c_str(), BUFFERSIZE, string("127.0.0.1"), PORT));

    ASSERT_NE(0, receiver->waitRead());

    ASSERT_EQ(BUFFERSIZE, receiver->recvFrom(recvbuffer, BUFFERSIZE));

//    ASSERT_EQ(E_OK, receiver->close());

    ASSERT_EQ(E_OK, receiver->connect(PORT + 20));
    
    ASSERT_EQ(BUFFERSIZE, sender->sendTo(sendbuffer.c_str(), BUFFERSIZE, string("127.0.0.1"), PORT + 20));

    ASSERT_NE(0, receiver->waitRead());

    ASSERT_EQ(BUFFERSIZE, receiver->recvFrom(recvbuffer, BUFFERSIZE));
/*
    ASSERT_EQ(BUFFERSIZE, remoteClient->send(sendbuffer));

    ASSERT_NE(0, client->waitRead());

    ASSERT_EQ(BUFFERSIZE, client->recv(recvbuffer, BUFFERSIZE));

    ASSERT_EQ(BUFFERSIZE, (*client) << sendbuffer);

    ASSERT_NE(0, remoteClient->waitRead());

    ASSERT_EQ(BUFFERSIZE, remoteClient->recv(recvbuffer, BUFFERSIZE));
/
}
*/

TEST_F(tcp, Connecting)
{
    Milliseconds m1;

    IPv4 ip("143.54.132.210");

    ASSERT_NE(E_OK, SocketTCP().openAsClient(ip,12000));
    Milliseconds m2;
    cout << m2.getTime() - m1.getTime() << endl;
    system("pause");

}
