#include <SocketMulticastSend.h>
#include <string>
#include <iostream>
#include <common.h>
using namespace std;

#define TEST_PORT 12001
#define TEST_IP   "239.8.8.8"


/// \todo Atualizar esse teste de acordo com a última versão

int main()
{
    SocketMulticastSend * socket;
    int i = 0;
    int ret;
    string data;

    common_init();

    try {
        socket = new SocketMulticastSend(TEST_IP, TEST_PORT);
    } catch(SocketException * e) {
        e->printErrorMessage();
        delete e;
        exit(1);
    }

    cout << "Socket criado, vai começar a enviar dados para:" << endl;
    cout << "  IP: " TEST_IP << ", porta: " << TEST_PORT << endl;

    data = "Dados de teste";
    while (true) {
        ret = (*socket) << data;
        if (ret != -1) {
            cout << "Mensagem enviada! (" << i << ") -- " << 
                ret << " bytes" << endl;
        } else {
            cout << "Erro ao enviar mensagem (" << i << "): " <<
                socket->lastError() << ": " << socket->lastErrorMessage() << endl;
        }
        i++;
        common_sleep(100);
    }

    socket->close();
    common_end();

    //int length;
    //char buffer[] = "teste\0" ;
    //SocketMulticastSend * server1 = new SocketMulticastSend("239.1.1.1",1234);
    //common_sleep(4000);
    //length = server1->sendTo(buffer,6,0, (sockaddr *)&server1->end, sizeof(server1->end));
    return 0;
}
