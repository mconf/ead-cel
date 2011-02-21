#ifndef _SOCKET_UDP_H_
#define _SOCKET_UDP_H_

#include "Socket.h"
#include "IgmpSender.h"

class SocketUDP : public Socket
{
public:
    static const int MAX_UDP_MESSAGE_SIZE = 8 * 1024;
private:
    static const int _family = AF_INET;
    static const int _type = SOCK_DGRAM;
    static const int _protocol = IPPROTO_UDP;

    IPv4 _ip;
    IgmpSender _igmpSender;
    char _recvbuf[MAX_UDP_MESSAGE_SIZE];
    struct ip_mreq _mreq;
    bool _leaveGroup;

    virtual int joinGroup(const IPv4& ip);
    virtual int leaveGroup();

public:
    SocketUDP() throw(SocketException*);
    virtual ~SocketUDP();

    virtual int openAsSender(const string& ip, int port, bool blocking);
    virtual int openAsReceiver(const string& ip, int port, bool blocking);
    virtual int openAsReceiver(int port, bool blocking);

    virtual int close();

    /** \brief Envia um buffer de dados para um endereço especificado
     *  \param buffer Dados que serão enviados
     *  \param len Tamanho, em bytes, dos dados em 'buffer'
     *  \param flags Flags adicionais. Consultar função 'sendto' dos sockets.
     *  \param to Endereço do destinatário
     *  \param tolen Tamanho, em bytes, do endereço em 'to'
     *  \return Retorna o número de bytes enviados em caso de sucesso. Em caso de erro
     *          retorna -1 e o erro específico é guardado internamente.
     *          Para pegá-lo usar a função lastError().
     */
    virtual int send(const char* buf, int len);
    virtual int send(const string& buf);
    virtual int operator<<(const string& buf);

    /** \brief Recebe um buffer de dados e guarda o endereço de quem o enviou
     *  \param buffer Buffer onde serão guardados os dados recebidos
     *  \param len Tamanho, em bytes, do buffer em 'buffer'
     *  \param flags Flags adicionais. Consultar função 'recv' dos sockets
     *  \param from Estrutura que irá guardar o endereço de quem enviou os dados
     *  \param fromlen Tamanho, em bytes, da estrutura em 'from'
     *  \return Retorna o número de bytes recebidos em caso de sucesso. Caso a conexão
     *          tenha sido fechada "amigavelmente", retorna zero. Em caso de erro
     *          retorna -1 e o erro específico é guardado internamente.
     *          Para pegá-lo usar a função lastError().
     */
    virtual int recv(char* buf, int len);
    virtual int recv(string& buf, int len = MAX_UDP_MESSAGE_SIZE);
    virtual int operator>>(string& buf);

};

#endif
