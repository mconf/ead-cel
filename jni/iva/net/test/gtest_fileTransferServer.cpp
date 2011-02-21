#include <stdio.h>
#include <stdlib.h>
#include "../net.h"
#include "../net_packet.h"
#include "../net_recv.h"
#include "queue.h"


int main(){
    FILE * arquivo = NULL;
    long lSize;
  
    char caminho[256];
    char ip[18];
    int porta=0;
    queue_t * queue;
    netrecv_struct_t * receiver;

    queue_consumer_t * consumidor;
    uint8_t * buffer;
    uint32_t buffersize,timestamp;
  
    

    queue_extraData_t data;
    int retorno;


    queue = queue_create();
    consumidor = queue_registerConsumer(queue);
    
    receiver = netrecv_init(queue,1024,2,NET_CONTENT_TYPE_VIDEO, NET_KILLER_PACKET_WAIT_TIME);

    printf("SERVIDOR ESPERANDO UM ARQUIVO\n\n\n");
    while(arquivo == NULL){
        printf("Digite o caminho do arquivo a ser recebido pelo servidor:\n");
        scanf("%s",caminho);
        arquivo = fopen(caminho, "w+b");
        if(!arquivo)
            printf("Digite um caminho válido para o arquivo!\n\n");
    }
    
    netrecv_packetSize(receiver, 1024);
    printf("Digite a porta:\n");
    scanf("%d",&porta);
    netrecv_setDest(receiver, "127.0.0.1", porta);
    netrecv_start(receiver);

    while(queue_dequeueCond(consumidor,&buffer,&buffersize,&timestamp,&data)!=E_OK);
    printf("size=%d\n",buffersize);
    fwrite(buffer,1,buffersize,arquivo);
    netrecv_stop(receiver);
    netrecv_end(receiver);
    queue_appFinish();
    printf("Arquivo recebido com sucesso!\n");
    fclose(arquivo);
    getchar();

    return 0;
};