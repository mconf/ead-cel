#include <SocketUDPSend.h>

#define PORT 27014

/// \todo atualizar esse teste de acordo com a última versão

int main()
{
    SocketUDPSend * socket;
    int i = 0;
    int ret;
    string data;

    common_init();

    try {
        socket = new SocketUDPSend("127.0.0.1", PORT);
    } catch(SocketException * e) {
        e->printErrorMessage();
        delete e;
        exit(1);
    }

    cout << "Socket criado, vai começar a enviar dados..." << endl;

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

    return 0;
}
