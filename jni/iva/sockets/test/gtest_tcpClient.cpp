#include <common.h>
#include <error.h>
#include <SocketTCP.h>
#include "SocketException.h"

//#define SOCK_BLOCKING

#define PORT 27014


/// \todo - é preciso atualizar esse teste de acordo com a última versão

int main()
{
    SocketTCP * c;
    int ret;
    string received;

#ifdef _MSC_VER
    common_init();
#endif

    try {
        c = new SocketTCP();
    } catch(SocketException * e) {
        e->printErrorMessage();
        delete e;
        exit(1);
    }

    string ip = "127.0.0.1";
    cout << "Conectando ao IP " << ip << endl;

    // para sockets bloqueantes
#ifdef SOCK_BLOCKING
    c->setblocking(true);
    while (c->connect(ip, (unsigned int)PORT) != E_OK) {
        cout << "Falha na tentativa de conexao: " << c->lastError() <<
            ": " << c->lastErrorMessage() << endl;
        common_sleep(1000);
    }
#else
    // para sockets NÃO bloqueantes

    IvaString str(ip);

    c->setblocking(false);
    while (c->connect(str, (unsigned int)PORT) != E_OK) {


#ifdef _MSC_VER
        if (c->lastError() == WSAEISCONN) { // retornou erro indicando que já está conectado
            break;
        }
#else
        if (c->lastError() == EISCONN) { // retornou erro indicando que já está conectado
            break;
        }
#endif
        cout << "Falha na tentativa de conexao: " << c->lastError() <<
            ": " << c->lastErrorMessage() << endl;

        /*cout << "Esperando o socket estar disponivel..." << endl;
        ret = c->waitWrite();
        if (ret > 0) { // conexão finalizada
            break;
        }*/
#ifdef _MSC_VER
        common_sleep(1000);
#endif
        //}
    }
#endif

    cout << "Cliente estah conectado!" << endl;

    cout << "======= enviando =======" << endl;
    ret = (*c) << "Este eh um teste.\0";
    cout << "Foram enviados " << ret << " bytes" << endl;

    cout << "======= recebendo ======" << endl;
    cout << "Aguardando mensagens..." << endl;
    while (c->waitRead() <= 0);
    ret = (*c) >> received;
    cout << "Foram recebidos " << ret << " bytes" << endl;
    cout << "Dados recebidos: " << received << endl;

    c->shutdown();
    c->close();

#ifdef _MSC_VER
    common_end();
#endif

    return 0;
}

