#include "Icmp.h"

const char* Icmp::ICMP_DATA = "abcdefghijklmnopqrstuvwabcdefghi";

Icmp::Icmp(const IPv4& ip)
    : _ip(ip)
    , _numHops(-1)
    , _numHopsEstimated(-1)
    , _rtt(-1)
    , _reachable(false)
    , _lastRefresh(0)
{
    _reach();
}

void Icmp::_reach()
{
    _reachable = false;

    char echoReply[ICMP_ECHO_SIZE];
    memset(echoReply, 0, ICMP_ECHO_SIZE);
    PICMP_ECHO_REPLY pEchoReply = (PICMP_ECHO_REPLY) echoReply;

    int ret = _send(ICMP_DEFAULT_TTL, pEchoReply);

    if (ret == E_OK && pEchoReply->Status == IP_SUCCESS) {
        _reachable = true;
        _updateRTT(pEchoReply->RoundTripTime);
        _updateNumHopsEstimated(pEchoReply->Options.Ttl);
    }

    _lastRefresh.setTimestamp();
}

void Icmp::_updateRTT(int rtt)
{
    if (_rtt == -1)
        _rtt = rtt;
    else
        _rtt = (875 * _rtt + 125 * rtt) / 1000;
}

void Icmp::_updateNumHopsEstimated(int ttl)
{
    _numHopsEstimated = (ICMP_MULTIPLE_TTL - (ttl % ICMP_MULTIPLE_TTL) + 1) % ICMP_MULTIPLE_TTL;
}

int Icmp::_gentrace()
{
    _numHops = -1;
    _reach();
    if (!isReachable())
        return E_COMMON_UNKNOWN_ERROR;

    char echoReply[ICMP_ECHO_SIZE];
    for (int ttl = 1; ttl < ICMP_MAX_TTL_TRACERT; ++ttl) {
        memset(echoReply, 0, ICMP_ECHO_SIZE);
        PICMP_ECHO_REPLY pEchoReply = (PICMP_ECHO_REPLY) echoReply;

        int ret = _send(ttl, pEchoReply);

        if (ret != E_OK)
            return ret;

        switch (pEchoReply->Status) {
            case IP_SUCCESS:
                if (pEchoReply->Address == inet_addr(_ip.getString().c_str())) {
                    _numHops = ttl;
                    _updateRTT(pEchoReply->RoundTripTime);
                    _updateNumHopsEstimated(pEchoReply->Options.Ttl);
                    return E_OK;
                }else{
                    NEW_ERROR(E_COMMON_UNKNOWN_ERROR,"Echo Reply respondeu sucesso, mas IP não é o destino");
                    return E_COMMON_UNKNOWN_ERROR;
                }
                break;
            case IP_TTL_EXPIRED_TRANSIT:
            case IP_TTL_EXPIRED_REASSEM:
            case IP_REQ_TIMED_OUT:
                break;
            default:
                //ERROR
                NEW_ERROR(E_COMMON_UNKNOWN_ERROR,"Status inválido no Echo Reply");
                return E_COMMON_UNKNOWN_ERROR;
        }
//        Seconds(1).sleep();
    }

    NEW_WARNING(E_COMMON_UNKNOWN_ERROR, "TTL atingiu o limite");
    return E_COMMON_UNKNOWN_ERROR;
}

int Icmp::_send(int ttl, PICMP_ECHO_REPLY pEchoReply)
{
    HANDLE hIP = IcmpCreateFile();
    if (hIP == INVALID_HANDLE_VALUE) {
        NEW_ERROR(E_COMMON_UNKNOWN_ERROR,"Não foi possível criar a mensagem ICMP");
        return E_COMMON_UNKNOWN_ERROR;
    }

    IP_OPTION_INFORMATION iphdr;
    iphdr.Flags = ICMP_IP_FLAGS;
    iphdr.Ttl = ttl;
    iphdr.OptionsSize = 0;
    
    DWORD dwStatus = IcmpSendEcho(hIP, inet_addr(_ip.getString().c_str()), 
        (void*) ICMP_DATA, ICMP_DATA_SIZE, &iphdr, pEchoReply, ICMP_ECHO_SIZE, ICMP_DEFAULT_TIMEOUT);

    IcmpCloseHandle(hIP);

    if (dwStatus == 0){
        ErrorData error(E_COMMON_UNKNOWN_ERROR, Location(AT));
        error << "Erro " << GetLastError() << " ao enviar o PING para o endereço " << _ip.getString();
        error.pushError();
        return E_COMMON_UNKNOWN_ERROR;
    }

    return E_OK;
}
