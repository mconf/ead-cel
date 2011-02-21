#ifndef _NET_HEADER_H_
#define _NET_HEADER_H_

#include "netDefs.h"
#include <map>
#include <string>
#include <QueueExtraData.h>
#include "NetHeaderAttr.h"
using namespace std;

/** \brief Cabeçalho dos pacotes na net
 *
 * Cabeçalho padrão para todos os tipos de pacotes. Pacotes com tipo definido
 * (áudio, vídeo, etc.) devem herdar essa classe e incluir seus atributos.
 * O cabeçalho é basicamente uma lista de atributos que apontam para um buffer que contém
 * todos os dados do pacote. Cada atributo aponta para a área do buffer em que ele deve estar
 * no cabeçalho. Todos valores dos atributos que são setados e buscados são feitos em cima
 * deste buffer. A lista de atributos é sempre existente, mas antes de um buffer ser setado,
 * todos os atributos apontam para NULL.
 * A ordem dos atributos no cabeçalho é a ordem que eles foram inseridos na lista.
 *
 * Formato do cabeçalho:
 *
 * 0   2   4   6   8   0   2   4   6   8   0   2   4   6   8   0   2
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |v=3|   type    |                   frame size                  |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *          sequence number        |        frag number            |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *                             timestamp                           |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
*             session id           |             NULL               
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 * * Type (1 byte): Tipo do pacote
 *         2 bits: assinatura
 *         6 bits: tipo do pacote
 * * Frame size (3 bytes): Tamanho do frame (soma do tamanho de todos fragmentos)
 * * Sequence number (2 bytes): Número de sequência
 * * Fragment number (2 bytes): Número do fragmento
 * * Timestamp (4 bytes)
 * * Session Id (2 bytes): Identificador da sessão
 * * NULL: É necessário para deixar o cabeçalho 32bit-aligned. Ler comentário abaixo.
 *
 * \note O tamanho dos cabeçalhos deve ser 32bit-aligned, ou seja, múltiplo de 32 bits.
 *       Essa restrição ocorre devido à forma como estão implementadas as funções
 *       setAttr e getAttr, que permitem campos com granularidade de bits e não apenas bytes.
 *
 */
class NetHeader
{
public:
    static const int IVA_SIGN           = 3;  ///< Assinatura dos pacotes do IVA (11 em binário)

    static const int ATTR_SIGN          = 0;  ///< Atributo do cabeçalho: Tipo do pacote
    static const int ATTR_TYPE          = 1;  ///< Atributo do cabeçalho: Tipo do pacote
    static const int ATTR_FRAMESIZE     = 2;  ///< Atributo do cabeçalho: Tamanho total do frame (em bytes)
    static const int ATTR_SEQNUM        = 3;  ///< Atributo do cabeçalho: Número de sequência
    static const int ATTR_FRAGNUM       = 4;  ///< Atributo do cabeçalho: Número do fragmento
    static const int ATTR_TIMESTAMP     = 5;  ///< Atributo do cabeçalho: Timestamp
    static const int ATTR_SESSION_ID    = 6;  ///< Atributo do cabeçalho: ID da sessão
    static const int ATTR_NULL          = 7;  ///< Atributo nulo, apenas para ficar 32bit-aligned
    static const int ATTRS              = 8;  ///< Quantidade de atributos no cabeçalho

private:
    map<int, NetHeaderAttr *> _attrs;         ///< Mapa de atributos. Indexado pela posição dos atributos
    unsigned int _headerSize;                 ///< Tamanho do cabeçalho (em BITS)
    unsigned char * _buffer;                  ///< Ponteiro para o buffer com os dados do cabeçalho

protected:
    void _CreateAttribute(int id, unsigned int size);
    int _SetBuffer(unsigned char * buffer);

    /** \brief Seta os atributos padrão que estão sempre setados (e.g. ATTR_TYPE)
     */
    virtual void _SetDefaultAttrs();

public:
    NetHeader();
    virtual ~NetHeader();

    /** \brief Retorna o tipo do cabeçalho: áudio, vídeo, etc.
     *
     * Deve ser implementado pelas classes descendentes.
     */
    virtual NetType getType();

    /** \brief Retorna o tamanho (em bytes) do cabeçalho
     */
    virtual int getSize();

    /** \brief Monta um objeto QueueExtraData e preenche ele com as informações do cabeçalho
     *
     * Deve ser implementado pelas classes descendentes. No NetHeader, apenas retorna NULL.
     */
    virtual QueueExtraData * createExtraData();

    /** \brief Preenche o cabeçalho com as informações de um objeto QueueExtraData
     *
     * Deve ser implementado pelas classes descendentes, se necessário. No NetHeader não faz nada.
     */
    virtual int setExtraData(QueueExtraData * extra);

    /** \brief Seta o buffer que deve ser usado neste cabeçalho
     *  \param buffer Ponteiro para o buffer
     *  \param bufferSize Tamanho (em bytes) do buffer
     */
    int setBuffer(unsigned char * buffer, unsigned int bufferSize);

    /** \brief Desassocia buffer que estava associado ao cabeçalho
     */
    int unsetBuffer();

    /** \brief Verifica se um atributo existe neste cabeçalho.
     *  \param name Nome do atributo buscado
     */
    bool hasAttr(int id);

    /** \brief Retorna o objeto do atributo buscado
     *  \param name Nome do atributo buscado
     */
    NetHeaderAttr * getAttr(int id);

    /** \brief Seta o valor de um atributo
     *  \param name Nome do atributo buscado
     *  \param value Valor a ser setado
     *
     * Obs: Se não tem um buffer associado ao cabeçalho, valor não é setado.
     */
    //void setAttr(int id, unsigned char * value);

    /** \brief Retorna o atributo buscado como um número inteiro
     *  \param name Nome do atributo buscado
     */
    uint32_t getAttrAsInt(int id);

    /** \brief Seta o valor inteiro a um atributo
     *  \param name Nome do atributo buscado
     *  \param value Valor inteiro a ser setado
     *
     * Obs: Se não tem um buffer associado ao cabeçalho, valor não é setado.
     */
    void setAttrAsInt(int id, uint32_t value);

    void clear();

    void print();

};

#endif

