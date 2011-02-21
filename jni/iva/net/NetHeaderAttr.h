#ifndef _NET_HEADER_ATTR_H_
#define _NET_HEADER_ATTR_H_

#include "netDefs.h"
#include <string>
using namespace std;

/** \brief Atributos do cabeçalho dos pacotes na net
 *
 */
class NetHeaderAttr
{
private:
    pair<unsigned int, int> _pair;

public:
    NetHeaderAttr(unsigned int size, int pointer);
    virtual ~NetHeaderAttr();

    /** \brief Seta o ponteiro (dados) do atributo
     *  \param value Valor do ponteiro
     *
     * Apenas guarda o ponteiro, não copia dados nem aloca memória nenhuma.
     */
    void setPointer(int value);

    void setSize(unsigned int value);

    unsigned int getSize();
    int getPointer();

    /** \brief Copia os dados passados para dentro da área apontada pelo atributo
     *  \param data Dados que serão copiados
     *
     * Se houver um ponteiro no atributo, copia os dados apontados por 'data' para
     * a área de memória apontada por este ponteiro.
     */
    //void copyData(unsigned char * data);

    /** \brief Copia os dados (inteiro) passados para dentro da área apontada pelo atributo
     *  \param data Dados que serão copiados
     *
     * Se houver um ponteiro no atributo, copia o número inteiro 'data' para
     * a área de memória apontada por este ponteiro.
     */
    void setData(unsigned char * buffer, uint32_t data);

    void clearData(unsigned char * buffer);

    uint32_t getData(unsigned char * buffer);

};

#endif

