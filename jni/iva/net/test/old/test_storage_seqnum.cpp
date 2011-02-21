#include "test_storage_seqnum.h"


int testStorageSeqnum()
{
//    net_storage_t *storage;
    net_packet_t *packet;
    queue_t *q;
    uint32_t seqnum = 0;
    int loop = 0;
    int changePhase = 0;
    int incSeqnum = 1;
    int bigPacketCnt = 0;

    q = queue_create();
//    storage = net_storage_create(10, q, NET_CONTENT_TYPE_VIDEO, NET_FRAME_MAX_SIZE);  ///\todo pegar esse 10 de 'netrecvPt'
    int cont = 0;
    while (cont < 100) {
        cont++;

        loop++;
        incSeqnum = 1;

        if (changePhase == 3) {
            packet = testStorageSeqnum_newPacketBig(NET_MAX_SEQNUM-2);
            changePhase++;
        } else if (changePhase == 4) {
            packet = testStorageSeqnum_newPacketBig(NET_MAX_SEQNUM-1);
            changePhase++;
        } else if (changePhase == 5) {
            packet = testStorageSeqnum_newPacketBig(NET_MAX_SEQNUM);
            changePhase = 0;
        } else {
        // colocar um maior na fila 2 posições antes de "virar" o numseq
        if (seqnum >= NET_MAX_SEQNUM-2 || changePhase) {
            packet = testStorageSeqnum_newPacketBig(seqnum);
            changePhase++;
        } else {
            packet = testStorageSeqnum_newPacket(seqnum);
        }
        }

        // 1 pacotes depois de virar, preenche esse maior pra liberar os com seqnum antigo
        // aqui que deve fazer o reorganize do seqnum e completar a "virada"
        /*} else if (changePhase) {
            if (bigPacketCnt == 0) {
                seqnum += 2;
                packet = testStorageSeqnum_newPacket(seqnum);
                seqnum++;
            } else if (bigPacketCnt == 1 || bigPacketCnt == 2) {
                packet = testStorageSeqnum_newPacketBig(NET_MAX_SEQNUM-2);
                net_packetSetNumFrag(packet, bigPacketCnt+1);
            } else if (bigPacketCnt == 3) {
                packet = testStorageSeqnum_newPacket(seqnum);
                changePhase = 0;
                //seqnum += 2;
            }
            bigPacketCnt++;

        // adicionando pacote na ordem do seqnum normal
        } else {*/
            //packet = testStorageSeqnum_newPacket(seqnum);
        //}
        printf("adicionando pacote seqnum %d ...\n", net_packetGetNumSeq(packet));
//        net_storage_add(storage, packet, NET_DEFAULT_PACKSIZE - NET_HEADER_SIZE,
                    //    NET_DEFAULT_PACKSIZE);
        printf("... adicionado! \n");

        //if (!changePhase) {
            seqnum++;
            if (seqnum > NET_MAX_SEQNUM) {
                changePhase = 1;
                seqnum = 0;
            }
        //}

        //net_storageSeqnumCheck(storage, packet);

//        net_storagePrint(storage);

        net_packetDestroy(packet);



        if (loop >= NET_MAX_SEQNUM-1) {
        printf("sleeping... \n");
        printf("loop %d... \n", loop);
        //common_sleep(500);
        system("pause");
        }
    }

//    net_storage_destroy(storage);
    queue_destroy(&q);
    queue_appFinish();
    return 0;
}

net_packet_t * testStorageSeqnum_newPacketBig(uint32_t seqnum)
{
    net_packet_t *packet;
    packet = net_packetNew(NET_DEFAULT_PACKSIZE,NET_CONTENT_TYPE_VIDEO);
    net_packetSetBufferSize(packet, (NET_DEFAULT_PACKSIZE - net_packetGetHeaderSize(packet))*2);
    net_packetSetNumSeq(packet, seqnum);
    net_packetSetNumFrag(packet, 1);
    return packet;
}

net_packet_t * testStorageSeqnum_newPacket(uint32_t seqnum)
{
    net_packet_t *packet;
    packet = net_packetNew(NET_DEFAULT_PACKSIZE,NET_CONTENT_TYPE_VIDEO);
    net_packetSetBufferSize(packet, net_packetGetHeaderSize(packet) - net_packetGetHeaderSize(packet));
    net_packetSetNumSeq(packet, seqnum);
    net_packetSetNumFrag(packet, 1);
    return packet;
}

