
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif

#include "threadTest.h"

int threadTest(){
    queue_t *q;
    netrecv_struct_t * recv;
    netsend_struct_t * send;

    q = queue_create();

    recv = netrecv_init(q,512*1024,8,NET_CONTENT_TYPE_VIDEO, NET_KILLER_PACKET_WAIT_TIME);
    netrecv_start(recv);
    common_sleep(10);
    netrecv_stop(recv);
    netrecv_end(recv);

    send = netsend_init(q,NET_CONTENT_TYPE_VIDEO);
    netsend_start(send);
    common_sleep(10);
    netsend_stop(send);
    netsend_end(send);

    queue_destroy(&q);
    queue_appFinish();
    return 0;
}