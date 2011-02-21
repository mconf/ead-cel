#include "NetworkInformation.h"

NetworkInformation::NetworkInformation()
    : _networkDevices()
    , _deviceIp()
    , _deviceMac()
{
    getSystemData();
}

NetworkInformation::~NetworkInformation()
{
}

string NetworkInformation::getIpAddress(const std::string& device) const
{
    const char * pos = strchr(device.c_str(), '{');
    if (pos) {
        map<string, string>::const_iterator ipAddress;
        ipAddress = _deviceIp.find(string(pos));
        if (ipAddress != _deviceIp.end()) {
            return ipAddress->second;
        }
    }
    return "";
}

string NetworkInformation::getMacAddress(const std::string& device) const
{
    const char * pos = strchr(device.c_str(), '{');
    if (pos) {
        map<string, string>::const_iterator macAddress;
        macAddress = _deviceMac.find(string(pos));
        if (macAddress != _deviceMac.end()) {
            return macAddress->second;
        }
    }
    return "";
}
