#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_CARROS 20
#define NUM_STEPS 10

sem_t s;
int num = 0;
pthread_mutex_t mutex_num;
pthread_mutex_t Cancela[7];

int fila[7] = {0};


typedef struct {
    int n_carro;     // o id é o numero do carro
    int cancela;
} Carro;

void *carroEstacionando(void *arg) {

    Carro *carro = (Carro *) arg;

    pthread_mutex_lock(&mutex_num);
    num++;
    int meu_num = num;
    pthread_mutex_unlock(&mutex_num);

   printf("Carro %d chegou na cancela %d ", meu_num, carro->cancela);
   printf(" Fila: [");

    for (int i = 0; i < 7; i++) {
        if (fila[i] != 0) {
            printf("%d, ", fila[i]);
        }  
    }
    printf("]\n");

    fila[carro->cancela] = meu_num;
    pthread_mutex_unlock(&Cancela[carro->cancela]);

    sem_wait(&s);

    pthread_mutex_lock(&Cancela[carro->cancela]);
    printf("Carro %d entrando pela cancela %d\n", meu_num, carro->cancela);
    sleep(5);
    //pthread_mutex_unlock(&mute_num);
    pthread_mutex_unlock(&Cancela[carro->cancela]);

    int sorteio = rand() % 10;
    sleep(10 + sorteio);
    sem_post(&s);

    pthread_mutex_lock(&Cancela[carro->cancela]);
    fila[carro->cancela] = 0;
    pthread_mutex_unlock(&Cancela[carro->cancela]);


    printf("Carro %d saindo do estacionamento\n", meu_num);
    pthread_exit(NULL);

}

int main(int argc, char *argv[]) {
    pthread_t carro[NUM_CARROS];
    pthread_attr_t attr;
    long status;
    int i;

    sem_init(&s, 0, NUM_STEPS);
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    for (i = 0; i < NUM_CARROS; i++) {
        Carro *car = (Carro *) malloc(sizeof(Carro));
        car->n_carro = i;
        car->cancela = rand() % 7;
        status = pthread_create(&carro[i], &attr, carroEstacionando, (void *) car);
        if (status) {
            perror("pthread_create");
            exit(1);
        }
    }

    for (i = 0; i < NUM_CARROS; i++) {
        pthread_join(carro[i], NULL);
    }

    pthread_attr_destroy(&attr);
    pthread_mutex_destroy(&mutex_num);
    sem_destroy(&s);
    pthread_exit(NULL);
    return 0;
}
