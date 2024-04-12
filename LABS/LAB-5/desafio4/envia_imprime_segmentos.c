//Para compilar/executar: gcc -o envia_imprime_segmentos envia_imprime_segmentos.c && ./envia_imprime_segmentos

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
 
#define SHM_SIZE 1024
 
int main(int argc, char *argv[])
{
    printf("verificando a memória compartilhada\n");

    //Declaração das variáveis
    key_t key;  //chave de identificação
    int shmid;  //id da memória compartilhada
    char *data; //ponteiro para a memória compartilhada
    int mode;   //modo de acesso 

    //cria a chave key 
    if ((key = ftok("/tmp", 'X')) == -1) {
        perror("ftok");
        exit(1);
       }
       
       //conecta-se ao segmento.
       //NOTA: Não há IPC_CREATE. O que acontece se você colocar IPC_CREATE aqui? 
       //Se eu colocar IPC_CREATE, o programa irá criar um novo segmento de memória compartilhada
       if ((shmid = shmget(key, SHM_SIZE, 0644)) == -1) {
        perror("shmget");
        exit(1);
       }

       //anexa ao segmento para obter um ponteiro para ele
       data = shmat(shmid, (void *)0, 0);

       if (data == (char *)(-1)) {
        perror("shmat");
        exit(1);
        }
 
        //lê ou modifica o segmento, com base na linha de comando

        //Se houver um argumento escreva no segmento
        if (argc == 2) {    
            printf("writing to segment: \"%s\"\n", argv[1]);

            //strncpy é a função que copia uma string para outra
            strncpy(data, argv[1], SHM_SIZE);

        //Se não, imprimi o que está no segmento
        } else
            printf("segment contains: \"%s\"\n", data);
 
 
       // desvincula do segmento
        if (shmdt(data) == -1) {
            perror("shmdt");
            exit(1);
        }
 
       return(0);
}

