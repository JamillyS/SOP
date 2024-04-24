#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_CARROS 20

sem_t s;

int num = 0;
pthread_mutex_t mutex_num;
pthread_mutex_t mutex_cancela[7];

void *carroEstacionando(void *arg) {
    int meu_num;

    pthread_mutex_lock(&mutex_num);
    num++;
    meu_num = num;
    pthread_mutex_unlock(&mutex_num);

    int cancela_id = rand() % 7;

    printf("Carro %d chegou na cancela %d.\n", meu_num, cancela_id);

    sem_wait(&s);
    pthread_mutex_lock(&mutex_num);
    
    printf("Carro %d entrou pela cancela %d.\n", meu_num, cancela_id);
    sleep(5); // Simulando passagem pela cancela
    pthread_mutex_unlock(&mutex_num);
    sleep(10+(random()%10));
    sem_post(&s);
    
    printf("Carro %d saiu\n", meu_num); 

    pthread_exit(NULL);
}

int main (int argc, char *argv[]) {
    pthread_t carro[NUM_CARROS];
    pthread_attr_t attr;
    long status;

    sem_init(&s, 0, 10);
    pthread_mutex_init(&mutex_num, NULL);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    
    for (int i = 0; i < 7; i++) {
    	status = pthread_create(&carro[i], &attr, carroEstacionando, NULL);
        if (status) {
        	perror("pthread_create");
        	exit(1);
        }
    }
    for (int i=0; i< NUM_CARROS; i++) {
    status = pthread_join(carro[i], NULL);
    if (status) {
   	perror("pthread_join");
   	exit(1);
    
   	}
   }



}
