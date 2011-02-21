#ifndef _NET_AUDIO_HEADER_H_
#define _NET_AUDIO_HEADER_H_

#include "NetHeader.h"

/** \brief Estende cabeçalho padrão IVA para incluir dados relacionados ao áudio
 *
 * Formato do cabeçalho:
 *
 * 0   2   4   6   8   0   2   4   6   8   0   2   4   6   8   0   2
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                            bitrate                            |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |     codec     |     flags     |              NULL              
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 */
class NetHeaderAudio : public NetHeader
{
public:
    static const int ATTR_BITRATE   = NetHeader::ATTRS;
    static const int ATTR_CODEC     = NetHeader::ATTRS + 1;
    static const int ATTR_FLAGS     = NetHeader::ATTRS + 2;
    static const int ATTR_NULL      = NetHeader::ATTRS + 3;

    static const int ATTRS          = NetHeader::ATTRS + 4; ///< Quantidade de atributos no cabeçalho

    NetHeaderAudio();
    ~NetHeaderAudio();

    virtual NetType getType();
    virtual QueueExtraData * createExtraData();
    virtual int setExtraData(QueueExtraData * extra);
};

#endif
