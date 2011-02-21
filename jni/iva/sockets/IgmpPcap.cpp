#include "IgmpPcap.h"

Mutex pcap_mutex;

IgmpPcap::IgmpPcap(const IPv4& ip)
    : _ip(ip)
    , _info()
{
}

IgmpPcap::~IgmpPcap(void)
{
}

void IgmpPcap::assemblyMacDestination(PcapInfo& p)
{
    unsigned int addr = inet_addr(_ip.getString().c_str());

    p.packet[0] = 0x01;
    p.packet[1] = 0x00;
    p.packet[2] = 0x5e;
    p.packet[3] = (addr >> 8) & 0x7F;
    p.packet[4] = (addr >> 16) & 0xFF;
    p.packet[5] = (addr >> 24) & 0xFF;
}

void IgmpPcap::assemblyMacSource(PcapInfo& p)
{
    if (p.mac.empty()) {
        for (int i = 6; i < 12; i++) {
            p.packet[i] = 0x00;
        }
    } else {
        for (int i = 6; i < 12; i++) {
            p.packet[i] = p.mac[i-6];
        }
    }
}

void IgmpPcap::assemblyTrailer(PcapInfo& p)
{
    for (int i = 42; i < 60; i++) {
        p.packet[i] = 0x00;
    }
}

void IgmpPcap::assemblyIpDestination(PcapInfo& p)
{
    unsigned int dst = inet_addr(_ip.getString().c_str());

    p.packet[30] = dst & 0xFF;
    p.packet[31] = (dst >> 8) & 0xFF;
    p.packet[32] = (dst >> 16) & 0xFF;
    p.packet[33] = (dst >> 24) & 0xFF;
}

void IgmpPcap::assemblyIpSource(PcapInfo& p)
{
    unsigned int src = inet_addr(p.ip.c_str());

    p.packet[26] = ((char *)&src)[0];
    p.packet[27] = ((char *)&src)[1];
    p.packet[28] = ((char *)&src)[2];
    p.packet[29] = ((char *)&src)[3];
}

void IgmpPcap::assemblyIpMulticast(PcapInfo& p)
{
    unsigned int dst = inet_addr(_ip.getString().c_str());

    p.packet[38] = dst& 0xFF;
    p.packet[39] = (dst >> 8) & 0xFF;
    p.packet[40] = (dst >> 16) & 0xFF;
    p.packet[41] = (dst >> 24) & 0xFF;
}

void IgmpPcap::setChecksum(PcapInfo& p)
{
    //HEADER CHECKSUM - DONE
    p.packet[24] = 0x00;
    p.packet[25] = 0x00;
    //Header Checksum
    p.packet[36] = 0x00;
    p.packet[37] = 0x00;

    p.packet[24] = (unsigned char)((igmpSocketCksum(&(p.packet[14]),20) >> 8) & 0xFF);
    p.packet[25] = (unsigned char)((igmpSocketCksum(&p.packet[14],20)) & 0xFF);
    p.packet[36] = (unsigned char)((igmpSocketCksum(&(p.packet[34]),8) >> 8) & 0xFF);
    p.packet[37] = (unsigned char)((igmpSocketCksum(&p.packet[34],8)) & 0xFF);
}

void IgmpPcap::assemblyGenericOptions(PcapInfo& p)
{
    //TYPE
    p.packet[12] = 0x08;
    p.packet[13] = 0x00;
    //Version
    p.packet[14] = 0x45;
    //Service Field
    p.packet[15] = 0xC0;
    //Total length
    p.packet[16] = 0x00;
    p.packet[17] = 0x1C;
    //Identification - INC
    p.packet[18] = 0x00;
    p.packet[19] = 0x01;
    //FLAGS & Fragment offset
    p.packet[20] = 0x00;
    p.packet[21] = 0x00;
    //Time to live
    p.packet[22] = 0x01;
    //Protocol - IGMP
    p.packet[23] = 0x02;
    //Membership query
//    p.packet[34] = 0x11;
    p.packet[34] = 0x16;
    //Max Response Time
    p.packet[35] = 0x64;  
}

void IgmpPcap::assemblyIGMP(PcapInfo& p)
{
    //Destination MAC
    assemblyMacDestination(p);
    //Source MAC
    assemblyMacSource(p);
    //Generic Options
    assemblyGenericOptions(p);
    //IP Source
    assemblyIpSource(p);
    //IP Destination
    assemblyIpDestination(p);
    //Multicast Address
    assemblyIpMulticast(p);
    //TRAILER
    assemblyTrailer(p);

    setChecksum(p);
}

int IgmpPcap::igmpSocketCksum(unsigned char* packetBuffer, int length)
{
    int checksum = 0;
    for (int i=0; i<length; i+=2) {
        checksum += ((packetBuffer[i]<<8) + packetBuffer[i+1]);
    }

    return ~((checksum >> 16) + (checksum & 0xffff));/* add hi 16 to low 16 */
}

int IgmpPcap::send()
{
    pcap_t *fp;
    pcap_if_t* alldevs;

    pcap_mutex.lock();
    memset(_errbuf, '\0', PCAP_ERRBUF_SIZE);
    int r = pcap_findalldevs(&alldevs, _errbuf);
    if (r != 0) {
        pcap_mutex.unlock();
        ErrorData e(E_COMMON_UNKNOWN_ERROR, Location(AT));
        e << "Falha ao encontrar os dispositivos do PCap: \"" << _errbuf << "\"";
        e.pushError();
        return E_COMMON_DEVICE_ERROR;
    }

    for(; alldevs; alldevs = alldevs->next) {
        memset(_errbuf, '\0', PCAP_ERRBUF_SIZE);

#ifdef _MSC_VER
        fp = pcap_open(alldevs->name, 100, PCAP_OPENFLAG_PROMISCUOUS, 1000, NULL, _errbuf);
#else
        fp = pcap_open_live(alldevs->name, 100, PCAP_WARNING, 1000, _errbuf);
#endif

        if (!fp) {
            ErrorData e(E_COMMON_UNKNOWN_ERROR, Location(AT));
            e << "Falha ao abrir um dispositivo do PCap: \"" << _errbuf << "\"";
            e.pushWarning();
            continue;
        }

        PcapInfo p;
        p.name = alldevs->name;
        p.descriptor = fp;
        p.ip = _info.getIpAddress(p.name);
        p.mac = _info.getMacAddress(p.name);

        if (!p.ip.empty() && !p.mac.empty()) {
            memset(p.packet, '\0', 60);
            assemblyIGMP(p);
            if (pcap_sendpacket(p.descriptor, p.packet, 60) != 0) {
                NEW_ERROR(E_SOCKET_SEND, "Falha ao enviar um pacote IGMP");
            }
        }
        pcap_close(fp);
    }
    pcap_freealldevs(alldevs);
    pcap_mutex.unlock();

    return E_OK;
}

