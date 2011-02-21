/** net_text.cpp : ponto de entrada para os testes da net
 *
 */


#include <stdio.h>
#include "test_storage_seqnum.h"
#include "threadTest.h"
#include "seq.h"
#include "list_test.h"
#include "net_queue_test.h"
#include "storage_test.h"
#include "net_packet_tester.h"



int main(int argc, char ** argv)
{
    char opt = '.';

    while (opt != 'q') {
        if (opt != '\n') {
            printf("\n");
            printf("Teste da lib 'net'. Opcoes: \n");
            printf("\t 0: storage seqnum \n");
            printf("\t 1: Inicialização e finalização das threads.\n");
            printf("\t 2: Embaralhamento.\n");
            printf("\t 3: Teste da lista encadeada.\n");
            printf("\t 4: Teste da NEt queue.\n");
            printf("\t 5: Teste da Storage.\n");
            printf("\t 6: Teste da Packet.\n");
            printf("\t q: quit \n");
        }

        opt = getchar();
        printf("\n");
        switch (opt) {
            case '\n': break;
            case '0':
                printf("=========================================\n");
                printf("testStorageSeqnum()\n");
                printf("=========================================\n");
                testStorageSeqnum();
                break;
            case '1':
                printf("=========================================\n");
                printf("threadTest()\n");
                printf("=========================================\n");
                threadTest();
                break;
             case '2':
                printf("=========================================\n");
                printf("Embaralhamento()\n");
                printf("=========================================\n");
                embaralhamento();
                break;
             case '3':
                printf("=========================================\n");
                printf("Teste da lista()\n");
                printf("=========================================\n");
                list_tester();
                break;
             case '4':
                printf("=========================================\n");
                printf("Teste da NEt queue()\n");
                printf("=========================================\n");
                test_net_queue();
                break;
            case '5':
                printf("=========================================\n");
                printf("Teste da NEt Storage()\n");
                printf("=========================================\n");
                net_storage_tester();
                break;
            case '6':
                printf("=========================================\n");
                printf("Teste da NeT PaCkEt()\n");
                printf("=========================================\n");
                packet_tester();
                break;
            default:
                printf("=========================================\n");
                printf("OPCAO INVALIDA \n");
                printf("=========================================\n");
        }

    }
 
    return 0;

}

