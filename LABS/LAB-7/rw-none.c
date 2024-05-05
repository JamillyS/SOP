/*
Sistema leitores-escritores, sem coordenação.
Compilar com gcc -Wall rw-none.c -o rw-none -lpthread
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_READERS 5
#define NUM_WRITERS 2

sem_t mutex ;		
int shared ;		// área compartilhada

// espera um tempo aleatório entre 0 e n segundos (float)
void espera (int n)
{
  sleep (random() % n) ;	// pausa entre 0 e n segundos (inteiro)
  usleep (random() % 1000000) ;	// pausa entre 0 e 1 segundo (float)
}

// corpo das tarefas leitoras
void *readerBody (void *id){

  long tid = (long) id ;
  while (1)
  {
    sem_wait(&mutex);
    printf ("R%02ld: read %d\n", tid, shared) ;
    sem_post(&mutex);
    espera (2) ;

    printf ("R%02ld: out\n", tid) ;
    espera (2) ;
  }

}


// corpo das tarefas escritoras
void *writerBody (void *id){
  //com semaforo
  long tid = (long) id ;
  while (1)
  {
    sem_wait(&mutex);
    shared = random () % 1000 ;
    printf ("\t\t\tW%02ld: wrote %d\n", tid, shared) ;
    sem_post(&mutex);
    espera (2) ;

    printf ("\t\t\tW%02ld: out\n", tid) ;
    espera (2) ;
  }

}


int main (int argc, char *argv[])
{
  pthread_t reader [NUM_READERS] ;
  pthread_t writer [NUM_WRITERS] ;
  long i ;

  shared  = 0 ;

  sem_init(&mutex, 0, 1);

  // cria leitores
  for (i=0; i<NUM_READERS; i++)
    if (pthread_create (&reader[i], NULL, readerBody, (void *) i))
    {
       perror ("pthread_create") ;
       exit (1) ;
    }

  // cria escritores
  for (i=0; i<NUM_WRITERS; i++)
    if (pthread_create (&writer[i], NULL, writerBody, (void *) i))
    {
      perror ("pthread_create") ;
      exit (1) ;
    }

  // main encerra aqui
  pthread_exit (NULL) ;
}