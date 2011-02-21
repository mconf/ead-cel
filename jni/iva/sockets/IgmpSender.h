#ifndef _IGMP_SENDER_H_
#define _IGMP_SENDER_H_

#include "Igmp.h"

#ifndef ANDROID
#include "IgmpPcap.h"
#endif

class IgmpSender: protected Runnable
{
private:
    static const int SLEEP_INTERVAL = 200;  ///< Intervalo entre sleeps na thread de envio de IGMP

    int _interval;                          ///< Intervalo entre envio de IGMPs
    AbstractIgmp* _igmpPacket;
    bool _stopThread;                       ///< Flag para indicar parada da thread de envio

    void threadFunction();
public:
    /**
     *  Construtor padrão
     *  \param ip Endereço IP do grupo multicast
     *  \param interval Intervalo entre envios, em segundos
     */
    IgmpSender(int interval = 60);
    virtual ~IgmpSender();

    void start(const IPv4& ip);
    void pause();

};

#endif
