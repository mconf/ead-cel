#include "Igmp.h"

Igmp::Igmp(const IPv4& ip)
    : _socket(IPPROTO_IGMP)
    , _ip(ip)
    , _buffer()
{
    _socket.openAsSender(_ip, true);
    _constructBuffer(_ip);


}

Igmp::~Igmp()
{
}

void Igmp::_constructBuffer(const IPv4& ip)
{
    _buffer.resize(IGMP_BUFFER_SIZE);

    // Type
    _buffer[0] = IGMP_V2_MEMBERSHIP_REPORT;
    // Code
    _buffer[1] = 0x00;
    // Checksum
    _buffer[2] = 0x00;
    _buffer[3] = 0x00;
    // Address
    uint32_t tmp = inet_addr(_ip.getString().c_str());
    _buffer[4] =  tmp        & 0xFF;
    _buffer[5] = (tmp >> 8)  & 0xFF;
    _buffer[6] = (tmp >> 16) & 0xFF;
    _buffer[7] = (tmp >> 24) & 0xFF;

    _fillChecksum();
}

void Igmp::_fillChecksum()
{
    int checksum = 0;
    string hdr(_buffer);

    for (int i = 0; i < IGMP_BUFFER_SIZE; i += 2) {
        checksum += ((hdr[i]<<8)+hdr[i+1]);
    }

    checksum = (checksum >> 16) + (checksum & 0xffff);    /* add hi 16 to low 16 */
    checksum = ~checksum - 1;

    _buffer[2] = (checksum >> 8) & 0xFF;
    _buffer[3] = checksum & 0xFF;
}

int Igmp::send()
{
//    Log("Enviando um IGMP");
    return _socket.send(_buffer);
}
