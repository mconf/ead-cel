#include "storage_test.h"

int net_storage_tester(){
    net_storage_t * storage;
    queue_t * queue;
    queue_consumer_t * consumer;
    net_packet_t * packet;

    printf("\n\nIniciando testes da storage\n\n");

    packet = net_packetNew(50000,NET_CONTENT_TYPE_VIDEO);
    queue = queue_create();
    consumer = queue_registerConsumer(queue);
    storage = net_storage_create(NET_CONTENT_TYPE_VIDEO,queue,5,50000, NET_KILLER_PACKET_WAIT_TIME);


  //  net_packetSetAudioFlags(packet,0);
    net_packetSetBufferSize(packet,3018);
    net_packetSetNumFrag(packet,1);    
    net_packetSetTimestamp(packet,getTimestamp());
    net_packetSetNumSeq(packet,0);
    
    net_storage_add(storage,packet,NET_DEFAULT_PACKSIZE - net_packetGetHeaderSize(packet),NET_DEFAULT_PACKSIZE);    
    
    net_packetSetNumFrag(packet,2);      
    net_storage_add(storage,packet,NET_DEFAULT_PACKSIZE - net_packetGetHeaderSize(packet),NET_DEFAULT_PACKSIZE);  
    
    net_packetSetNumFrag(packet,3);      
    net_storage_add(storage,packet,NET_DEFAULT_PACKSIZE - net_packetGetHeaderSize(packet),NET_DEFAULT_PACKSIZE);    
    
   
    net_packetDestroy(packet);
    queue_destroy(&queue);
    net_storage_destroy(storage);
    
    return 0;
}
