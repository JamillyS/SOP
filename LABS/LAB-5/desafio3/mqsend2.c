// Arquivo mq-send.c: envia mensagens para uma fila de mensagens Posix.
// Em Linux, compile usando: cc -Wall mqsend.c -o mqsend -lrt
// Carlos Maziero, DINF/UFPR, Julho de 2020

#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <unistd.h>

#define QUEUE "/my_queue"

int main (int argc, char *argv[])
{
  mqd_t  queue ;         // descritor da fila
  int    msg ;           // mensagem a enviar

  // abre a fila de mensagens, se existir
  if((queue = mq_open (QUEUE, O_RDWR)) < 0)
  {
    perror ("mq_open") ;
    exit (1) ;
  }

  for (int i = 0; i < 10; i++){
    msg = random() % 1000; 

    // envia a mensagem
    if (mq_send (queue, (void*) &msg, sizeof(msg), 0) < 0)
    {
      perror ("mq_send") ;
      exit (1) ;
    }
    printf ("Sent message with value %d\n", msg) ;
    sleep (1) ;
  }

  msg = -1;
  //Enviando a mensagem -1 para encerrar
  if (mq_send (queue, (void*) &msg, sizeof(msg), 0) < 0)
  {
    perror ("mq_send") ;
    exit (1) ;
  }

  if (msg == -1){
    mq_close (queue);   //fecha o descritor da fila
    mq_unlink (QUEUE);  //remove a fila do sistema
    exit (0);           //encerro o programa
  }
 
}