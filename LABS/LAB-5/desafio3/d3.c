
#include <unistd.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>

int main(int argc, char *argv[]){

    //Troca de mensagens com fila de mensagens
    //Desafio 3: feche uma fila. Utilize o exemplo apresentado em aula anterior para criar um receiver 
    //que fecha a fila ao receber o valor "-1"; Crie um sender que envia números aleatórios até 1000;
    //Crie um segundo sender que envia 10 números aleatórios até 1000 e depois envie -1.

    mqd_t queue ;               // descritor da fila
    struct mq_attr attr ;       // atributos da fila de mensagens
    int msg ;                   // mensagem a enviar

    // abre a fila de mensagens, se existir
    // se nao existir, cria a fila com permissoes 0666
    if((queue = mq_open (QUEUE, O_RDWR)) < 0)
    {
        perror ("mq_open") ;
        exit (1) ;
    }
    



}

