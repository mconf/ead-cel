#ifndef _NET_TEST_STORAGE_SEQNUM_H_
#define _NET_TEST_STORAGE_SEQNUM_H_


#include "../net.h"
#include "../net_storage.h"
#include "../net_packet.h"

int testStorageSeqnum();
net_packet_t * testStorageSeqnum_newPacket(uint32_t seqnum);
net_packet_t * testStorageSeqnum_newPacketBig(uint32_t seqnum);



#endif // _NET_TEST_STORAGE_SEQNUM_H_

