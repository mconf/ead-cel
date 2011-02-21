#include "net_packet_tester.h"



int packet_tester(){
    net_packet_t * packet = NULL;
    net_video_extra_data_t data;
    net_video_extra_data_t * dados;

    printf("Iniciando o teste da packet\n\n");
    
    printf("Testando a inicialização do pacote: ");
    packet = net_packetNew(NET_DEFAULT_PACKSIZE,NET_CONTENT_TYPE_VIDEO);
    if(packet == NULL)
        printf("ERROR.\n");
    else
        printf("OK.\n");



    printf("Testando o tipo do pacote: ");    
    if(net_packetGetType(packet) != NET_CONTENT_TYPE_VIDEO)
        printf("ERROR.\n");
    else
        printf("OK.\n");

    printf("Testando o size do ExtraSize do pacote: ");    
    if(net_packetGetExtraSize(packet) != sizeof(net_video_extra_data_t))
        printf("ERROR.\n");
    else
        printf("OK.\n");


    
    printf("Testando a inserção de dados extras no pacote: ");    

    data.coder_id = 1;
    data.fps = 30;
    data.height = 800;
    data.width = 600;

    if(!net_packetSetVideoExtraData(packet,&data))
        printf("ERROR.\n");
    else
        printf("OK.\n");

    printf("Testando o GEt de dados extras no pacote: ");    
   
    dados = net_packetGetVideoExtraData(packet);
    if(dados == NULL)
        printf("ERROR.\n");
    else
        printf("OK.\n");
    
    printf("Testando a integridadede dados extras no pacote: ");       
    if(dados->coder_id  == data.coder_id && dados->fps == data.fps && dados->height == data.height && dados->width == data.width)
        printf("OK.\n");
    else
        printf("ERROR.\n");
         

    printf("Testando a destruição do pacote: ");
    if(net_packetDestroy(packet))
        printf("OK.\n");
    else
        printf("ERROR.\n");

    printf("\nFinalizando o teste da packet\n");
    return 0;
}