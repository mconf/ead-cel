#include <CommonLeaks.h>
#include <QueueExtraDataVideo.h>
#include "netDefs.h"
#include "NetHeaderVideo.h"
#include <CommonLeaksCpp.h>

NetHeaderVideo::NetHeaderVideo()
    : NetHeader()
{
    _CreateAttribute(ATTR_BITRATE, 32);
    _CreateAttribute(ATTR_WIDTH, 16);
    _CreateAttribute(ATTR_HEIGHT, 16);
    _CreateAttribute(ATTR_CODEC, 8);
    _CreateAttribute(ATTR_FPS, 8);
    _CreateAttribute(ATTR_VIDEO_ID, 16);
}

NetHeaderVideo::~NetHeaderVideo()
{
}

NetType NetHeaderVideo::getType()
{
    return NET_TYPE_VIDEO;
}

QueueExtraData * NetHeaderVideo::createExtraData()
{
    QueueExtraDataVideo * dataVideo = new QueueExtraDataVideo();
    dataVideo->setCodecId((uint8_t)getAttrAsInt(ATTR_CODEC));
    dataVideo->setFps((uint8_t)getAttrAsInt(ATTR_FPS));
    dataVideo->setWidth((uint16_t)getAttrAsInt(ATTR_WIDTH));
    dataVideo->setHeight((uint16_t)getAttrAsInt(ATTR_HEIGHT));
    dataVideo->setBitrate((uint32_t)getAttrAsInt(ATTR_BITRATE));
    dataVideo->setVideoId((uint16_t)getAttrAsInt(ATTR_VIDEO_ID));
    return dataVideo;
}

int NetHeaderVideo::setExtraData(QueueExtraData * extra)
{
    int ret = E_ERROR;
    if (extra && extra->getType() == QueueExtraData::EXTRA_DATA_VIDEO) {
        QueueExtraDataVideo * video = (QueueExtraDataVideo *)extra;
        setAttrAsInt(ATTR_CODEC, video->getCodecId());
        setAttrAsInt(ATTR_FPS, video->getFps());
        setAttrAsInt(ATTR_WIDTH, video->getWidth());
        setAttrAsInt(ATTR_HEIGHT, video->getHeight());
        setAttrAsInt(ATTR_BITRATE, video->getBitrate());
        setAttrAsInt(ATTR_VIDEO_ID, video->getVideoId());
        ret = E_OK;
    }
    return ret;
}
