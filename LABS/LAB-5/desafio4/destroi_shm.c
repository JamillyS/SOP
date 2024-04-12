//destrua um shm. Crie um programa que destrua o shm utilizado nos programas anteriores.
//Para isso utilize shmctl com o parâmetro apropriado (veja "man shmctl").
//OBS.: IPC_STAT para recuperar estrutura e IPC_RMID para destruir.

//Para compilar/executar: gcc -o destroi_shm destroi_shm.c && ./destroi_shm

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 1024 

int main(void){
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
    if ((shmid = shmget(key, SHM_SIZE, 0644)) == -1) {
        perror("shmget");
        exit(1);
       }

    //Para a destruição do segmento
    //A eliminação dum segmento só pode ser feita através da seguinte chamada ao sistema: função shmctl():
    //shmctl(shmid, IPC_RMID, NULL);
    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("shmctl");
        exit(1);
    }

    return(0);
}

