#pragma once

#include <common.h>

#ifndef ANDROID // android não tem pcap
#include <pcap.h>
#endif

#ifdef _MSC_VER
#include <Iphlpapi.h>
#endif
#include "NetworkInformation.h"
#include "AbstractIgmp.h"

class PcapInfo
{
public:
    string name;
    pcap_t* descriptor;
    string mac;
    string ip;
    unsigned char packet[60];
};

class IgmpPcap: public AbstractIgmp
{
protected:
    IPv4 _ip;
    NetworkInformation _info;               ///< Informações sobre a rede
    char _errbuf[PCAP_ERRBUF_SIZE];
    
    void assemblyMacDestination(PcapInfo& p);
    void assemblyMacSource(PcapInfo& p);
    void assemblyTrailer(PcapInfo& p);
    void assemblyIpDestination(PcapInfo& p);
    void assemblyIpSource(PcapInfo& p);
    void assemblyIpMulticast(PcapInfo& p);
    void setChecksum(PcapInfo& p);
    void assemblyGenericOptions(PcapInfo& p);
    void assemblyIGMP(PcapInfo& p);
    int igmpSocketCksum(unsigned char* packetBuffer, int length);

public:
    IgmpPcap(const IPv4& ip);
    virtual ~IgmpPcap();

    int send();
};
