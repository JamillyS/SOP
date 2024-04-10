// Arquivo mq-send.c: envia mensagens para uma fila de mensagens Posix.
// Em Linux, compile usando: gcc -Wall mqsend.c -o mqsend -lrt
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
  // se nao existir, cria a fila com permissoes 0666
  if((queue = mq_open (QUEUE, O_RDWR)) < 0)
  {
    perror ("mq_open") ;
    exit (1) ;
  }

  // envia mensagens para a fila
  for (;;)
  {
    // gera um valor aleatorio entre 0 e 99
    msg = random() % 100 ;  // valor entre 0 e 99

    // envia a mensagem
    // se a fila estiver cheia, o processo sera bloqueado
    if (mq_send (queue, (void*) &msg, sizeof(msg), 0) < 0)
    {
      perror ("mq_send") ;
      exit (1) ;
    }
    printf ("Sent message with value %d\n", msg) ;
    sleep (1) ;
  }
}
