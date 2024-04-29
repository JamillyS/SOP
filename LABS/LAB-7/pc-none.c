/*
Sistema produtor-consumidor sem coordenação.
Compilar com gcc -Wall pc-none.c -o pc-none -lpthread
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define NUM_PROD 3
#define NUM_CONS 5
#define VAGAS 6

int num_itens, num_vagas ; 	// contadores de vagas e peças

// espera um tempo aleatório entre 0 e n segundos (float)
void espera (int n)
{
  sleep (random() % n) ;	// pausa entre 0 e n segundos (inteiro)
  usleep (random() % 1000000) ;	// pausa entre 0 e 1 segundo (float)
}

// corpo de produtor
void *prodBody (void *id)
{
  long tid = (long) id ;

  printf ("P%02ld: Olá!\n", tid) ;

  while (1)
  {
    num_itens++ ;
    num_vagas-- ;
    printf ("P%02ld: put an item (%d itens, %d vagas)!\n",
            tid, num_itens, num_vagas) ;
    espera (2) ;
  }
}

// corpo de consumidor
void *consBody (void *id)
{
  long tid = (long) id ;

  printf ("C%02ld: Olá!\n", tid) ;

  while (1)
  {
    num_itens-- ;
    num_vagas++ ;
    printf ("C%02ld: got an item (%d itens, %d vagas)!\n",
            tid, num_itens, num_vagas) ;
    espera (2) ;
  }
}

// programa principal
int main (int argc, char *argv[])
{
  pthread_t produtor   [NUM_PROD] ;
  pthread_t consumidor [NUM_CONS] ;
  long i ;

  num_itens = 0 ;
  num_vagas = VAGAS ;

  // cria produtores
  for (i=0; i<NUM_PROD; i++)
    if (pthread_create (&produtor[i], NULL, prodBody, (void *) i))
    {
      perror ("pthread_create") ;
      exit (1) ;
    }

  // cria consumidores
  for (i=0; i<NUM_CONS; i++)
    if (pthread_create (&consumidor[i], NULL, consBody, (void *) i))
    {
      perror ("pthread_create") ;
      exit (1) ;
    }

  // main encerra aqui
  pthread_exit (NULL) ;
}
