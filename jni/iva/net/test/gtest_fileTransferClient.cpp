#include <stdio.h>
#include <stdlib.h>
#include "../net.h"
#include "../net_packet.h"
#include "../net_send.h"
#include "queue.h"


int main(){
    FILE * arquivo = NULL;
    long lSize;
    char * buffer;
    char caminho[256];
    char ip[18];
    int porta=0;
    queue_t * queue;
    netsend_struct_t * sender;
    int retorno;


    queue = queue_create();
    sender = netsend_init(queue,NET_CONTENT_TYPE_VIDEO);
    netsend_packetSize(sender,1024,128);

    printf("CUIDADO - PROGRAMA CARREGA TODO O ARQUIVO PARA A MEMÓRIA RAM ANTES DE ENVIAR\n\n\n");
    while(arquivo == NULL){
        printf("Digite o caminho do arquivo a ser transferido para o servidor:\n");
        scanf("%s",caminho);
        arquivo = fopen(caminho, "rb");
        if(!arquivo)
            printf("Digite um caminho válido para o arquivo!\n\n");
    }
    //tamanho
    fseek (arquivo, 0 , SEEK_END);
    lSize = ftell(arquivo);
    rewind (arquivo);
    
    buffer = (char *)queue_malloc(sizeof(char)*lSize);
    if(!buffer)
        printf("Seu sistema não possui memória livre sufiente para carregar o arquivo para memória!");
    fread (buffer,1,lSize,arquivo);    

    printf("Digite o IP do servidor:\n");
    scanf("%s",ip);
    printf("Digite a porta do servidor:\n");
    scanf("%d",&porta);
    
    netsend_setDest(sender, ip, porta);
    netsend_start(sender);
    retorno = queue_enqueue(queue,(uint8_t *)buffer,lSize,getTimestamp(),NULL);
    while(queue_length(queue)>0){
        common_sleep(1000);
        };
    netsend_stop(sender);
    netsend_end(sender);
    queue_appFinish();
    printf("Arquivo enviado com sucesso!\n");
    getchar();
    return 0;
};