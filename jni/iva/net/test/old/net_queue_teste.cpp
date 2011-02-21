#include "net_queue_test.h"

int test_net_queue(){
    uint32_t tamanho = 5;
    uint32_t i;
    net_queue_t* queue;
    net_queue_item_t * item,*item1;
    int erro;
    net_packet_t * packet;

    
    
    printf("\nCriando a Net Queue: ");
    queue = net_queue_create(tamanho,512*1024);
    if(queue != NULL)
        printf("OK.\n");
    else
        printf("Erro.\n");

    printf("Testando isEmpty: ");    
    if(net_queue_isEmpty(queue))
        printf("OK.\n");
    else
        printf("Erro.\n");

    printf("Inserindo um elemento e testando isEmpty: ");    
    net_queue_enqueue(queue);
    if(!net_queue_isEmpty(queue))
        printf("OK.\n");
    else
        printf("Erro.\n");
    net_queue_dequeue(queue);

    printf("Dando um dequeue quando está empty - tem que dar erro: ");
      if(net_queue_dequeue(queue) == E_ERROR)
        printf("OK.\n");
    else
        printf("Erro.\n");

    printf("Testando isFull: ");  
    for(i=0; i<tamanho; i++)
        net_queue_enqueue(queue);
    if(net_queue_isFull(queue))
        printf("OK.\n");
    else
        printf("Erro.\n");

       printf("Teste do enqueue quando está Full - tem que dar erro: ");
    if(net_queue_enqueue(queue) == NULL)
        printf("OK.\n");
    else
        printf("Erro.\n");

    printf("Esvaziando lista e verificando se está empty: ");    
    for(i=0; i<tamanho; i++)
         net_queue_dequeue(queue);
    if(net_queue_isEmpty(queue))
        printf("OK.\n");
    else
        printf("Erro.\n");

    printf("Verificando net_queue_first quando a lista está vazia: ");       
    item = net_queue_first(queue);
    if(item == NULL)
        printf("OK.\n");
    else
        printf("Erro.\n");
    

    printf("Verificando net_queue_first quando a lista tem um item: ");       
    item1 = net_queue_enqueue(queue);
    item = net_queue_first(queue);
    if(item1 == item)
        printf("OK.\n");
    else
        printf("Erro.\n");    
    net_queue_dequeue(queue);

    printf("Verificando a queue total: ");         
    if(net_queue_total(queue) == tamanho)
        printf("OK.\n");
    else
        printf("Erro.\n");    
    
    erro = 0;
    printf("Verificando a queue size: ");         
    for(i=0; i<net_queue_total(queue);i++){
        if(net_queue_size(queue) != i){
            erro = 1;
            break;
        };
        net_queue_enqueue(queue);            
    }
    if(net_queue_size(queue)!=tamanho)
        erro = 1;

    if(!erro)
        printf("OK.\n");
    else
        printf("Erro.\n");    

    for(i=0; i<net_queue_total(queue);i++)
        net_queue_dequeue(queue);
    
    
    printf("Testando at index (Simples):");
    if(net_queue_at_index(queue,0) == NULL)
        printf("OK.\n");
    else 
        printf("Erro.\n");

    erro = 0;
    printf("Testando at index (Hard):");
    for(i=0; i< net_queue_total(queue); i++){
        if(net_queue_at_index(queue,i) != NULL){
            erro = 1;
            break;
        }
        item = net_queue_enqueue(queue);
        if(item != net_queue_at_index(queue,i)){
            erro = 1;
            break;
        }
    }   
    if(net_queue_at_index(queue, net_queue_total(queue)))
        erro = 1;
    if(!erro)
        printf("OK.\n");
    else 
        printf("Erro.\n");

    for(i=0; i< net_queue_total(queue); i++) 
        net_queue_dequeue(queue);

    printf("\nIniciando testes de recebimento - HARD \n\n");
    packet = net_packetNew(10000,NET_CONTENT_TYPE_VIDEO);

//    net_packetSetAudioFlags(packet,0);
    net_packetSetBufferSize(packet,3050);
    net_packetSetNumFrag(packet,1);
    net_packetSetNumSeq(packet,1);
    net_packetSetTimestamp(packet,getTimestamp());
    
    printf("Inserindo um pacote simples: ");
    if(net_queue_insert(queue,packet,NET_DEFAULT_PACKSIZE - net_packetGetHeaderSize(packet),NET_DEFAULT_PACKSIZE)!=NULL)
        printf("OK.\n");
    else 
        printf("Erro.\n");

    net_packetSetNumSeq(packet,3);
    printf("Inserindo um pacote a frente: ");
    if(net_queue_insert(queue,packet,NET_DEFAULT_PACKSIZE - net_packetGetHeaderSize(packet),NET_DEFAULT_PACKSIZE)!=NULL)
        printf("OK.\n");
    else 
        printf("Erro.\n");

    net_packetSetNumSeq(packet,2);
    printf("Inserindo um pacote no meio: ");
    if(net_queue_insert(queue,packet,NET_DEFAULT_PACKSIZE - net_packetGetHeaderSize(packet),NET_DEFAULT_PACKSIZE)!=NULL)
        printf("OK.\n");
    else 
        printf("Erro.\n");

    net_packetSetNumSeq(packet,1);
    net_packetSetNumFrag(packet,2);
    printf("Inserindo um pacote que já havia recebido: ");
    if(net_queue_insert(queue,packet,NET_DEFAULT_PACKSIZE - net_packetGetHeaderSize(packet),NET_DEFAULT_PACKSIZE)!=NULL)
        printf("OK.\n");
    else 
        printf("Erro.\n");

    
    printf("Enchendo e tentando inserir: ");
    net_packetSetNumSeq(packet,4);    
    net_queue_insert(queue,packet,NET_DEFAULT_PACKSIZE - net_packetGetHeaderSize(packet),NET_DEFAULT_PACKSIZE);
    net_packetSetNumSeq(packet,5);    
    if(net_queue_insert(queue,packet,NET_DEFAULT_PACKSIZE - net_packetGetHeaderSize(packet),NET_DEFAULT_PACKSIZE) == NULL)
        printf("ERRO.\n");
    net_packetSetNumSeq(packet,6);    
    if(net_queue_insert(queue,packet,NET_DEFAULT_PACKSIZE - net_packetGetHeaderSize(packet),NET_DEFAULT_PACKSIZE)==NULL)
        printf("OK.\n");
    else 
        printf("Erro.\n");

    printf("Testando dequeue e recebimento: ");
    net_queue_dequeue(queue);
    net_packetSetNumFrag(packet,1);
    net_packetSetNumSeq(packet,1);
     if(net_queue_insert(queue,packet,NET_DEFAULT_PACKSIZE - net_packetGetHeaderSize(packet),NET_DEFAULT_PACKSIZE)==NULL)
        printf("OK.\n");
    else 
        printf("Erro.\n");

    printf("Inserindo após dequeue: ");
    net_packetSetNumSeq(packet,6);
     if(net_queue_insert(queue,packet,NET_DEFAULT_PACKSIZE - net_packetGetHeaderSize(packet),NET_DEFAULT_PACKSIZE)!=NULL)
        printf("OK.\n");
    else 
        printf("Erro.\n");


    printf("Testando a queue_clear: ");
    erro = 0;
    if(net_queue_clear(queue) != E_OK)
        erro = 1;
    if(!net_queue_isEmpty(queue))
        erro = 1;
    if(!erro)
        printf("OK.\n");
    else 
        printf("Erro.\n");

    printf("Testando a virada 65000->0: ");
    net_packetSetNumSeq(packet,64998);
    net_queue_insert(queue,packet,NET_DEFAULT_PACKSIZE - net_packetGetHeaderSize(packet),NET_DEFAULT_PACKSIZE);
    net_packetSetNumSeq(packet,1);
    net_queue_insert(queue,packet,NET_DEFAULT_PACKSIZE - net_packetGetHeaderSize(packet),NET_DEFAULT_PACKSIZE);
    if(net_queue_size(queue) != 5)
        printf("Erro.\n");
    else
        printf("OK.\n");
    printf("Testando a virada e indo além do range: ");
     net_packetSetNumSeq(packet,4);
     if(net_queue_insert(queue,packet,NET_DEFAULT_PACKSIZE - net_packetGetHeaderSize(packet),NET_DEFAULT_PACKSIZE) == NULL)
         printf("OK.\n");
     else
         printf("Erro.\n");


    printf("\n\nDestruindo a Net Queue: ");    
    if(net_queue_destroy(queue) == E_OK)
        printf("OK.\n");
    else
        printf("Erro.\n");
    
    return 0;
};