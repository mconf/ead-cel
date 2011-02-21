#include <SocketUDPRecv.h>
#include "SocketException.h"

#define PORT 27014

/// \todo atualizar esse teste de acordo com a última versão

int main()
{
    SocketUDPRecv * socket;
    string data;
    int ret, i = 0;

    common_init();

    try {
        socket = new SocketUDPRecv(PORT);
    } catch(SocketException * e) {
        e->printErrorMessage();
        delete e;
        exit(1);
    }

    cout << "Vai receber dados UDP na porta " << PORT << endl;
    while (true) {
        // fica esperando chegar algo
        while (socket->waitRead(0, 100000) <= 0);

        // chegou, busca os dados no socket
        ret = (*socket) >> data;
        if (ret != -1) {
            cout << "Mensagem recebida! (" << i << "): " <<
                data << endl;
        } else {
            cout << "Erro ao receber mensagem (" << i << "): " <<
                socket->lastError() << ": " << socket->lastErrorMessage() << endl;
        }
        i++;
    }

    socket->close();
    common_end();

    return 0;
}

