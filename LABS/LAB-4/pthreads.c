/*
pthread_join: bloqueia execução de uma thread até que outra thread termine, implementando um comportamento similar à chamada 
de sistema wait usada em processos Unix.

pthread_exit: encerra a execução de uma thread. A chamada a esta função por uma pthread gera a liberação de outras threads 
que estejam, eventualmente, bloqueadas nela por uma chamada pthread_join.

*/
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>


typedef struct {
   int idx;
   int length;
} thread_arg, *ptr_thread_arg;

pthread_t threads[2]; //estrutura que armazena dados/atributos de uma pthread.
pthread_mutex_t mutex; //estrutura que armazena dados/atributos de um mutex.


void *thread_func(void *arg) {
   ptr_thread_arg targ = (ptr_thread_arg)arg;
   int i;

for(i = targ->idx; i < (targ->idx + targ->length); i++) {

        pthread_mutex_lock(&mutex);     //entra na região crítica  e bloqueia a thread
        printf("Thread %lu – value %d\n", pthread_self(), i);   ///Imprimi o identificador da thread que a chama
        pthread_mutex_unlock(&mutex);   //sai da região crítica e desbloqueia a thread
        usleep(100);    //sleep serve para simular um tempo de execução
   }

   return 0;
}

int main(int argc, char **argv) {
   thread_arg arguments[2];
   int i;

   for(i = 0; i < 2; i++) {
    arguments[i].idx = i * 10;
    arguments[i].length = 10;
    pthread_create(&(threads[i]), NULL, thread_func, &(arguments[i]));
 
   }
   for(i = 0; i < 2; i++) {
       pthread_join(threads[i], NULL);
   }

   return 0;
}


