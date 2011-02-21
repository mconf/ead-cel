#ifndef _ICMP_H
#define _ICMP_H

#include <common.h>

#ifdef _MSC_VER
#include <iphlpapi.h>
#include <icmpapi.h>
#endif

class Icmp
{
private:
    static const char* ICMP_DATA;
    static const int ICMP_DATA_SIZE = 32;
    static const int ICMP_DEFAULT_TTL = 128;
    /**
     *  The flags setted on IP Packet
     *  IP_FLAG_REVERSE : This value causes the IP packet to add in an IP routing header with the source.
     *  This value is only applicable on Windows Vista and later.
     *  IP_FLAG_DF : This value indicates that the packet should not be fragmented.
     */
    static const int ICMP_IP_FLAGS = 0;     
    static const int ICMP_MAX_TTL_TRACERT = 30;
    static const int ICMP_ECHO_SIZE = sizeof(ICMP_ECHO_REPLY) + ICMP_DATA_SIZE;
    static const int ICMP_DEFAULT_TIMEOUT = 1000; //ms
    static const int ICMP_MULTIPLE_TTL = 64;

    IPv4 _ip;
    int _numHops;
    int _numHopsEstimated;
    int _rtt;
    bool _reachable;
    Milliseconds _lastRefresh;
    
    /** \brief Send an ICMP Echo Request for a host and get teh reply
     *  \param ttl The Time to Live of ICMP Echo Request Packet
     *  \param pEchoReply Structute ICMP_ECHO_REPLY that contains the information about ICMP Echo Reply
     *  \return E_OK  The packet was sended and received with success
     *  \return E_COMMON_UNKNOWN_ERROR se algo der errado
     */
    int _send(int ttl, PICMP_ECHO_REPLY pEchoReply);
    void _reach();
    int _gentrace();
    void _updateRTT(int rtt);
    void _updateNumHopsEstimated(int ttl);
    
public:
    Icmp(const IPv4& ip);

    bool isReachable() const { return _reachable; }

    int getNumHops() 
    {
        if (_numHops == -1)
            _gentrace();
        return _numHops; 
    }

    int getRTT()
    { 
        _reach();
        return _rtt; 
    }

    int getNumHopsEstimated() 
    {
        _reach();
        return _numHopsEstimated; 
    }
};

#endif /* _ICMP_H */
