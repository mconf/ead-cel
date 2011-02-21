#include "IgmpSender.h"

IgmpSender::IgmpSender(int interval)
    : _interval(interval)
    , _stopThread(false)
    , _igmpPacket(NULL)
{
}

IgmpSender::~IgmpSender()
{
}

void IgmpSender::start(const IPv4& ip)
{
    if (!isRunning()) {

#ifdef ANDROID // android usa versão simples, sem pcap
        _igmpPacket = new Igmp(ip);
#else
        _igmpPacket = new IgmpPcap(ip);
#endif

        _stopThread = false;
        run(true);
    }
}

void IgmpSender::pause()
{
    if (isRunning()) {
        _stopThread = true;
        join();
        delete _igmpPacket;
    }
}

void IgmpSender::threadFunction()
{
    Milliseconds sleepTime(SLEEP_INTERVAL);
    while (!_stopThread) {
        Milliseconds before;

        _igmpPacket->send();

        Milliseconds after;

        after = after - before;

        int slept = after.getTime();
        while (!_stopThread && slept < _interval * 1000) {
            sleepTime.sleep();
            slept += SLEEP_INTERVAL;
        }
    }
}
