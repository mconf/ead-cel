#include "gtest_NetRecv.h"

/** \todo Testes ainda a serem feitos:
          - testar validator
          - testar redirecionamento
          - receber dados por um tempo e tentar dar um stop no meio pra ver se para mesmo
*/

TEST_F(NetRecvTest, SendSingleIGMPReport)
{
    // teste básico só para verificar se não dá erro na função
    // passando IPs variados
    _net = new NetRecv(NET_TYPE_VIDEO, NULL);
    _net->start(IPv4("239.5.5.5"), 12001);
    EXPECT_EQ(E_OK, _net->sendSingleIGMPReport());
    _net->stop();
    _net->start(IPv4("0.0.0.0"), 12001);
    EXPECT_NE(E_OK, _net->sendSingleIGMPReport());
    _net->stop();
    delete _net;
}


