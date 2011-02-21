#include <CommonLeaks.h>
#include "netDefs.h"
#include "NetStatistics.h"
#include <CommonLeaksCpp.h>

NetStatistics::NetStatistics()
    : _stats(NUM_ATTR, 0)
{
}

int NetStatistics::getAttr(int name, bool clear)
{
    int value = _stats.at(name);
    if (clear)
        clearAttr(name);
    return value;
}

int NetStatistics::clearAttr(int name)
{
    setAttr(name, 0);
    return E_OK;
}

void NetStatistics::setAttr(int name, int value)
{
    _stats.at(name) = value;
}

void NetStatistics::increment(int name, int value)
{
    _stats.at(name) += value;
}

void NetStatistics::zeroAll()
{
    for (vector<int>::iterator it = _stats.begin(); it != _stats.end(); ++it)
        *it = 0;
}

string NetStatistics::getAttrName(int name)
{
    switch(name) {
        case ATTR_RECEIVED_PACKETS: return "ATTR_RECEIVED_PACKETS";
        case ATTR_RECEIVED_FRAMES: return "ATTR_RECEIVED_FRAMES";
        case ATTR_RECEIVED_BYTES: return "ATTR_RECEIVED_BYTES";
        case ATTR_SENT_PACKETS: return "ATTR_SENT_PACKETS";
        case ATTR_SENT_FRAMES: return "ATTR_SENT_FRAMES";
        case ATTR_SENT_BYTES: return "ATTR_SENT_BYTES";
        case ATTR_DISCARDED_FRAMES: return "ATTR_DISCARDED_FRAMES";
        case ATTR_DISCARDED_BYTES: return "ATTR_DISCARDED_BYTES";
        case ATTR_LOST_PACKETS: return "ATTR_LOST_PACKETS";
        case ATTR_REDIRECTED_PACKETS: return "ATTR_REDIRECTED_PACKETS";
        case ATTR_REDIRECTED_BYTES: return "ATTR_REDIRECTED_BYTES";
        case ATTR_LAST_TIMESTAMP: return "ATTR_LAST_TIMESTAMP";
        default: return "ATTR_UNKNOWN";
    }
}