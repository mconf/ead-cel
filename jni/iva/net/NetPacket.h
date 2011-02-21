#ifndef _NET_PACKET_H_
#define _NET_PACKET_H_

#include "netDefs.h"
#include "NetHeader.h"
#include "NetHeaderAudio.h"
#include "NetHeaderVideo.h"

/** \brief Classe que representa um pacote na lib net
 *
 * O pacote contém um buffer que pode ser alocado internamente ou pode ser setado
 * externamente. Este buffer contém o cabeçalho do pacote e também os dados (payload).
 * Há uma estrutura NetHeader que controla o cabeçalho, mas ela apenas aponta para posições
 * no buffer setado nela, que é o buffer criado aqui na NetPacket. Ou seja, todos os 
 * dados estão neste buffer, e o NetHeader é utilizado para controle do cabeçalho.
 * Todos os pacotes são do tipo NetPacket
 */
class NetPacket
{
public:
    static const int DEFAULT_PACKSIZE = 1024;           ///< Tamanho padrão (em bytes) para usar em pacotes
    static const int MAX_PACKSIZE = 1500;               ///< Tamanho máximo (em bytes) dos pacotes
    static const int FRAME_SIZE = 512 * MAX_PACKSIZE;   ///< Tamanho máximo (em bytes) de um frame (áudio, vídeo)

protected:
    NetType _type;                  ///< Tipo do pacote (áudio, vídeo, etc.)
    unsigned char * _buffer;        ///< Buffer onde os dados do pacote estão
    unsigned char * _payloadPt;     ///< Ponteiro para a área de dados
    unsigned int _payloadSize;      ///< Tamanho (em bytes) dos dados '_payload'
    NetHeader * _header;            ///< Estrutura de ponteiros para os atributos do header

public:
    NetPacket(NetType type);
    ~NetPacket();

    /** \brief Retorna o tamanho (em bytes) do pacote (cabeçalho + dados)
     */
    unsigned int getSize();

    /** \brief Aloca um novo buffer para dados e header do pacote
     *  \param payloadSize Tamanho (em bytes) dos DADOS do pacote (sem contar header)
     *
     * O buffer é alocado internamente e conterá o cabeçalho e os dados do pacote.
     * O cabeçalho é manipulado pelo objeto retornado em getHeader() e os dados
     * devem ser obtidos com getDataPointer().
     */
    int allocBuffer(unsigned int payloadSize);

    int allocBuffer(unsigned char * payloadBuffer, unsigned int payloadSize);

    /** \brief Limpa o buffer de dados interno (cabeçalho e dados)
     *
     * Se o buffer de dados havia sido alocado com allocBuffer(), ele é desalocado. Se ele havia
     * sido setado externamente com setBuffer(), apenas seta o ponteiro para NULL. Tudo que havia
     * no cabeçalho e nos dados do pacote será apagado com esta função.
     */
    int deallocBuffer();

    /** \brief Copia um buffer para a área de dados do pacote
     *  \param data Dados a serem copiados para o pacote
     */
    int copyPayload(unsigned char * data, unsigned int dataSize);

    /** \brief Retorna um ponteiro para o buffer geral do pacote
     */
    unsigned char * getBufferPointer();

    /** \brief Retorna o tamanho (em bytes) da área de dados do pacote
     *
     * Obs: Se o buffer não foi setado ou alocado, retornará sempre 0.
     */
    unsigned int getPayloadSize();
    void setPayloadSize(unsigned int value);

    /** \brief Retorna um ponteiro para a área de dados do pacote
     *
     * Obs: Se o buffer não foi setado ou alocado, retornará sempre NULL.
     */
    unsigned char * getPayloadPointer();

    /** \brief Retorna um ponteiro para o objeto que controla o cabeçalho do pacote
     *
     * Obs: Cabeçalho sempre existe, mas se não foi setado ou alocado o buffer do pacote,
     * o cabeçalho não possuirá nenhum dado.
     */
    NetHeader * getHeader();

};

#endif
