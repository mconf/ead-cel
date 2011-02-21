#include <SocketTCPServer.h>

#define PORT 27014

/// \todo atualizar esse teste de acordo com a última versão

int main()
{
    SocketTCPServer * s;
    Socket * c;
    int ret;
    string received;

    common_init();

    try {
        s = new SocketTCPServer(PORT);
    } catch(SocketException * e) {
        e->printErrorMessage();
        delete e;
        exit(1);
    }

    s->listen(SOMAXCONN);

    cout << "Socket criado, aguardando conexoes..." << endl;
    c = s->accept(NULL, NULL);
    s->close();
    cout << "Cliente conectado!" << endl;

    cout << "======= recebendo ======" << endl;
    cout << "Aguardando mensagens..." << endl;
    while (c->waitRead() <= 0);
    ret = (*c) >> received;
    cout << "Foram recebidos " << ret << " bytes" << endl;
    cout << "Dados recebidos: " << received << endl;

    cout << "======= enviando =======" << endl;
    ret = (*c) << "Este eh um teste.\0";
    cout << "Foram enviados " << ret << " bytes" << endl;

    c->shutdown(SD_SEND);
    c->close();

    common_end();

    return 0;
}
