#ifndef _NET_QUEUE_ITEM_H_
#define _NET_QUEUE_ITEM_H_

#include "netDefs.h"
#include <vector>
using namespace std;
#include <queue.h>

/** \brief Item da queue da net: guarda dados de um frame
 *
 * O NetQueueItem aloca e gerencia um buffer para guardar um frame de dados, seja frame
 * de áudio ou frame de vídeo.
 * Frame pode estar separado em diversos fragmentos. Fragmentos devem ser do mesmo tamanho,
 * exceto o último fragmento do frame que pode ser menor.
 * O item mantém uma lista de fragmentos recebidos para saber se já recebeu o frame todo
 * e para evitar duplicação de dados.
 */
class NetQueueItem
{
public:
    enum NetQueueItemStatus { 
        FREE, ///< Item está livre (está criado mas não possiu nenhum dado ainda)
        BUSY  ///< Item está ocupado (possui algum dado, não necessariamente todos)
    };

private:
    vector<char> _fragList;                 ///< Lista de controle dos fragmentos recebidos
    int _fragCount;                         ///< Número de fragmentos (para frames particionados)
    int _fragSize;                          ///< Tamanho dos fragmentos
    unsigned char *_data;                   ///< Ponteiro para a região de dados
    unsigned int _dataSize;                 ///< Tamanho da região de dados

    net_seqnum_t _seqnum;                   ///< Número de sequencia do frame
    Milliseconds _timestamp;                ///< Timestamp do pacote
    Milliseconds _arriveTime;               ///< Momento em que o frame chegou
    unsigned int _totalReceived;            ///< Total recebido até então
    QueueExtraData * _extraData;            ///< Dados extra da queue para este item
    NetQueueItemStatus _status;             ///< FREE, BUSY ou WAIT

    /** \brief Limpa as variáveis internas. Não limpa o buffer de dados.
     *
     * Limpa tudo, menos o buffer de dados em \p _data, o tamanho do buffer
     * \p _dataSize e o número de fragmentos \p _fragCount
     */
    void _Clear();

public:
    NetQueueItem();
    NetQueueItem(unsigned int frameSize, int fragSize = 0);
    ~NetQueueItem();

    /** \brief Aloca o buffer de dados. Se já estava alocado, desaloca e aloca um novo.
     *  \param frameSize Tamanho (em bytes) do frame
     *  \param fragSize Tamanho dos fragmentos. Se 0, frame não está fragmentado.
     *
     * \note Todos dados internos também são zerados (timestamp, _extraData, etc.)
     */
    int allocData(unsigned int frameSize, int fragSize = 0);

    /** \brief Desaloca o buffer de dados.
     *
     * \note Todos dados internos também são zerados (timestamp, _extraData, etc.)
     */
    int deallocData();

    void setSequenceNumber(net_seqnum_t value);
    void setTimestamp(const Interval &value);
    void setArriveTime(const Interval &value);
    void setTotalReceived(unsigned int value);
    void setExtraData(QueueExtraData * value);

    unsigned int getDataSize();
    net_seqnum_t getSequenceNumber();
    const Interval getTimestamp();
    const Interval getArriveTime();
    unsigned int getTotalReceived();
    unsigned char * getData();
    QueueExtraData * getExtraData();
    NetQueueItemStatus getStatus();

    string getFragListStr();

    /** \brief Indica se o frame está completo (se recebeu todos fragmentos)
     *  \return \p true se já recebeu todos os fragmentos do frame. \p false
     *          caso contrário.
     *
     */
    bool isComplete();

    /** \brief Insere um bloco de dados no buffer do NetQueueItem
     *  \param data Dados que serão inseridos (copiados)
     *  \param size Tamanho dos dados em \p data
     *  \param fragNum Número do fragmento, para saber em que posição do buffer
     *         os dados são inseridos
     *  \return E_OK ou o código de erro gerado
     *
     * \note Os dados são copiados para dentro do buffer.
     */
    int insertData(unsigned char * data, unsigned int size, int fragNum = 0);

};

#endif

