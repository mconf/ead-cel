#ifndef _NET_VIDEO_HEADER_H_
#define _NET_VIDEO_HEADER_H_

#include "NetHeader.h"

/** \brief Estende cabeçalho padrão IVA para incluir dados relacionados ao vídeo
 *
 * Formato do cabeçalho:
 *
 * 0   2   4   6   8   0   2   4   6   8   0   2   4   6   8   0   2
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                            bitrate                            |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |             width             |             height            |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |     codec     |      fps      |            video id           |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 */
class NetHeaderVideo : public NetHeader
{
public:
    static const int ATTR_BITRATE   = NetHeader::ATTRS;
    static const int ATTR_WIDTH     = NetHeader::ATTRS + 1;
    static const int ATTR_HEIGHT    = NetHeader::ATTRS + 2;
    static const int ATTR_CODEC     = NetHeader::ATTRS + 3;
    static const int ATTR_FPS       = NetHeader::ATTRS + 4;
    static const int ATTR_VIDEO_ID  = NetHeader::ATTRS + 5;

    static const int ATTRS          = NetHeader::ATTRS + 6; ///< Quantidade de atributos no cabeçalho

    NetHeaderVideo();
    ~NetHeaderVideo();

    virtual NetType getType();
    virtual QueueExtraData * createExtraData();
    virtual int setExtraData(QueueExtraData * extra);
};

#endif

