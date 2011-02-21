#ifndef _NET_DEFS_H_
#define _NET_DEFS_H_

#include <common.h>

typedef uint16_t net_seqnum_t;

/** \brief Define os tipos (de pacotes, cabeçalhos, etc.) possíveis na net.
 *
 * Esses tipos são utilizados para identificar o tipo dos pacotes, dos cabeçalhos,
 * dos dados gerais sendo recebidos (NetRecv) ou enviados (NetSend), entre outros.
 * São utilizados no campo "type" dos pacotes, que tem 6 bits. Por isso devem
 * estar no intervalo [0,64)
 */
enum NetType {
    NET_TYPE_NONE = 0,
    NET_TYPE_VIDEO,
    NET_TYPE_AUDIO
};


#endif

