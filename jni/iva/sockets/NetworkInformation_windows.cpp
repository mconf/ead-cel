#include "NetworkInformation.h"

void NetworkInformation::getSystemData()
{
    string device;
    IP_ADAPTER_INFO AdapterInfo[16];
    DWORD dwBufLen = sizeof(AdapterInfo);

    DWORD dwStatus = GetAdaptersInfo(      // Call GetAdapterInfo
        AdapterInfo,                       // [out] buffer to receive data
        &dwBufLen);                        // [in] size of receive data buffer

    // percorre todos adaptadores e vai guardando nas listas internas
    PIP_ADAPTER_INFO pAdapterInfo = AdapterInfo;
    while (pAdapterInfo) {
        device = string(strchr(pAdapterInfo->AdapterName,'{'));
        _networkDevices.push_back(device);
        _deviceIp.insert(pair<string,string>(
            device, string(pAdapterInfo->IpAddressList.IpAddress.String)
            ));
        _deviceMac.insert(pair<string,string>(
            device,string((char *)pAdapterInfo->Address, 8)
            ));
        pAdapterInfo = pAdapterInfo->Next;
    }
}

