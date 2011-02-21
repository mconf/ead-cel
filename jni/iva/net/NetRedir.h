#ifndef _NET_REDIR_H_
#define _NET_REDIR_H_

#include "netDefs.h"
#include <map>
#include <Mutex.h>
#include "NetRedirItem.h"

class NetRedir
{
private:
    map<int, NetRedirItem *> _redirs;
    Mutex _mutex;
    int _lastId;

    int _NextId();
    int _SetEnabled(int id, bool value);

public:
    NetRedir();
    ~NetRedir();

    /** \brief Envia um pacote de dados usando os items de redirecionamento existentes
     *  \param packet Pacote a ser enviado
     */
    int send(NetPacket * packet);

    /** \brief Cria um novo NetRedirItem e o insere na lista
     *  \param ip IP do redirecionamento
     *  \param port Porta do redirecionamento
     */
    NetRedirItem * add(IPv4 &ip, unsigned int port);

    /** \brief Remove o item da lista e delete o objeto
     *  \param id Id do item a ser removido
     */
    int remove(int id);

    /** \brief Remove o item da lista e delete o objeto
     *  \param item Item a ser removido
     */
    int remove(NetRedirItem * item);

    /** \brief Remove todos os items da lista e deleta os objetos
     */
    int removeAll();

    /** \brief Habilita um item da lista de redirecionamentos
     *  \param id Id do item a ser habilitado
     */
    int enable(int id);

    /** \brief Habilita um item da lista de redirecionamentos
     *  \param item Item a ser habilitado
     */
    int enable(NetRedirItem * item);

    /** \brief Habilita todos os items da lista
     */
    int enableAll();

    /** \brief Desabilita um item da lista de redirecionamentos
     *  \param id Id do item a ser desabilitado
     */
    int disable(int id);

    /** \brief Desabilita um item da lista de redirecionamentos
     *  \param item Item a ser desabilitado
     */
    int disable(NetRedirItem * item);

    /** \brief Desabilita todos os items da lista
     */
    int disableAll();

    /** \brief Retorna o objeto de um item de redirecionamento
     *  \param id Id do item procurado
     */
    NetRedirItem * get(int id);
};

#endif
