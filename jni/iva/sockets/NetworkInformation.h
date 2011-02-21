#ifndef _NETWORK_INFORMATION_H_
#define _NETWORK_INFORMATION_H_

//#include <pcap.h>
//#include <ws2tcpip.h>
#include <list>
#include <map>
#include <string>
#include "SocketWrapper.h"
using namespace std;

class NetworkInformation
{
private:
    list<string> _networkDevices;       ///< Código dos dispositivos
    map<string, string> _deviceIp;      ///< Dispositivo | Endereço Ip
    map<string, string> _deviceMac;     ///< Dispositivo | Endereço Mac


    void getSystemData();


public: 
    NetworkInformation();
    virtual ~NetworkInformation();
    
    string getIpAddress(const string& device) const;
    string getMacAddress(const string& device) const;
    list<string>& getListDevices() { return _networkDevices; }
};

#endif

