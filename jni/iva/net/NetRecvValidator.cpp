#include <CommonLeaks.h>
#include "NetRecvValidator.h"
#include <CommonLeaksCpp.h>

NetAudioFlagValidator::NetAudioFlagValidator(uint8_t flag)
{
    _flag = flag;
}

bool NetAudioFlagValidator::operator() (NetPacket * value)
{
    if (value->getHeader()->getType() == NET_TYPE_AUDIO) {
        NetHeaderAudio * h = (NetHeaderAudio *)value->getHeader();
        uint8_t flag = h->getAttrAsInt(NetHeaderAudio::ATTR_FLAGS);
        if (flag & _flag) { // bloqueia apenas os que possuem esta flag
            return false;
        }
    }
    return true;
}

void NetAudioFlagValidator::setFlag(uint8_t flag)
{
    _flag = flag;
}
