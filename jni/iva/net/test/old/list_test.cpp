#include "list_test.h"

int list_tester(){
    int i;
    int tamanho = 5;
    uint32_t status;
    circular_list * list;
    void ** pointer = NULL;

    printf("Iniciando teste da lista circular\n\n");
    
    printf("Criando a lista circular: ");
    list = create_circular_list(tamanho);
    if(list != NULL)
        printf("OK.\n");
    else
        printf("Erro.\n");

    printf("Verificando quando tamanho == 0: ");
    if (circular_list_size(list) == 0)
        printf("OK.\n");
    else 
        printf("ERRO.\n");

    printf("Verificando IS_EMPTY: ");    
    if (circular_list_is_empty(list) == TRUE)
        printf("OK.\n");
    else 
        printf("ERRO.\n");

    printf("Verificando IS_FULL == false: ");    
    if (circular_list_is_full(list) == FALSE)
        printf("OK.\n");
    else 
        printf("ERRO.\n");

    printf("Verificando se evita dar um dequeue quando a lista está vazia: ");    
    if (circular_list_dequeue(list) == E_ERROR)
        printf("OK.\n");
    else 
        printf("ERRO.\n");

    printf("Inserindo um elemento e verificando size: ");
    pointer = circular_list_enqueue(list,&status);
    *pointer =  (void *)1;
    if (status == E_OK && circular_list_size(list) == 1)
        printf("OK.\n");
    else 
        printf("ERRO.\n");

    printf("Verificando front(): ");
    if (circular_list_front(list) == (void *)1)
        printf("OK.\n");
    else 
        printf("ERRO.\n");

    printf("Verificando dequeue e size: ");
     if (circular_list_dequeue(list) == E_OK && circular_list_size(list) == 0 && circular_list_is_empty(list) == TRUE)
        printf("OK.\n");
    else 
        printf("ERRO.\n");
    
     int booleano = 1;
     printf("Enchendo a fila e testando size: ");
     for(i=0; i< tamanho; i++){
         pointer = circular_list_enqueue(list, &status);
         *pointer = (void *)i;
         if( status == E_ERROR)
             booleano = 0;
         if(circular_list_size(list) != i+1)
             booleano = 0;
     }
     if(booleano)
         printf("OK\n");
     else 
         printf("ERRO.\n");

    printf("Agora tem que dar erro no enqueue: "); 
    circular_list_enqueue(list,&status);
    if(status == E_ERROR)
        printf("OK.\n");
    else 
        printf("Erro.\n");


    printf("IS FULL está certo?: ");
    if (circular_list_is_full(list) == TRUE)
        printf("OK.\n");
    else 
        printf("ERRO.\n");
    
    booleano = 1;
    printf("testando at_index: ");
    for(i=0; i<tamanho; i++){
        if(circular_list_at_index(list,i) != (void *)i)
            booleano = 0;
    }
    if(circular_list_at_index(list,tamanho) != NULL)
        booleano  = 0;
    if(booleano)
        printf("OK.\n");
    else 
        printf("ERRO.\n");

    booleano = 1;
    printf("Testando clear: ");
    if(circular_list_clear(list) != E_OK)
        booleano = 0;
    if(circular_list_is_empty(list) != TRUE)
        booleano = 0;
    if(booleano)
        printf("OK.\n");
    else 
        printf("ERRO.\n");
    
          

    printf("Destruindo a lista: ");
    destroy_circular_list(&list);
    if(list == NULL)
        printf("OK.\n");
    else 
        printf("Erro.\n");


    printf("\nFinalizando teste da lista circular\n\n");
    return 0;
}