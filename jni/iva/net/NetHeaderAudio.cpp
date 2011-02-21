#include <CommonLeaks.h>
#include <QueueExtraDataAudio.h>
#include "netDefs.h"
#include "NetHeaderAudio.h"
#include <CommonLeaksCpp.h>

NetHeaderAudio::NetHeaderAudio()
    : NetHeader()
{
    _CreateAttribute(ATTR_BITRATE, 32);
    _CreateAttribute(ATTR_CODEC, 8);
    _CreateAttribute(ATTR_FLAGS, 8);
    _CreateAttribute(ATTR_NULL, 16);
}

NetHeaderAudio::~NetHeaderAudio()
{
}

NetType NetHeaderAudio::getType()
{
    return NET_TYPE_AUDIO;
}

QueueExtraData * NetHeaderAudio::createExtraData()
{
    QueueExtraDataAudio * dataAudio = new QueueExtraDataAudio();
    dataAudio->setCodecId((uint8_t)getAttrAsInt(ATTR_CODEC));
    dataAudio->setAudioFlags((uint8_t)getAttrAsInt(ATTR_FLAGS));
    dataAudio->setBitrate((uint32_t)getAttrAsInt(ATTR_BITRATE));
    return dataAudio;
}

int NetHeaderAudio::setExtraData(QueueExtraData * extra)
{
    int ret = E_ERROR;
    if (extra && extra->getType() == QueueExtraData::EXTRA_DATA_AUDIO) {
        QueueExtraDataAudio * audio = (QueueExtraDataAudio *)extra;
        setAttrAsInt(ATTR_CODEC, audio->getCodecId());
        setAttrAsInt(ATTR_FLAGS, audio->getAudioFlags());
        setAttrAsInt(ATTR_BITRATE, audio->getBitrate());
        ret = E_OK;
    }
    return ret;
}

