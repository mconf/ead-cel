#ifndef _NET_RECV_VALIDATOR_H_
#define _NET_RECV_VALIDATOR_H_

#include "NetPacket.h"

/** \brief Classe base para validador de pacotes
 *
 * Usado pela NetRecv para validar pacotes. Para usá-lo, basta criar uma classe
 * que herda de NetRecvValidator e implementar o operador "()". A função recebe
 * um NetPacket* como parâmetro. Se retornar 'true', o pacote é válido. Se retornar
 * 'false' o pacote é inválido, e é descartado pela NetRecv.
 * Obs: Isso é atualmente usado para verificar as flags de áudio e descartar os pacotes
 * já na NetRecv, sem nem colocá-los na queue.
 */
class NetRecvValidator : unary_function<NetPacket *, bool>
{
public:
    virtual bool operator() (NetPacket * value) = 0;
};


/** \brief Validador de pacotes de áudio conforme o campo "audio flags"
 *
 * Recebe uma flag de áudio como parâmetro na construção e descarta todos pacotes
 * de áudio que possuam esta flag setada no campo "audio flags".
 */
class NetAudioFlagValidator : public NetRecvValidator
{
private:
    uint8_t _flag;
public:
    NetAudioFlagValidator(uint8_t flag);
    bool operator() (NetPacket * value);

    void setFlag(uint8_t flag);
};



#endif

