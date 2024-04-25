#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_CARROS 20
#define NUM_STEPS 10

sem_t s;                    // Semáforo
int num = 0;                // num é o número de carros
pthread_mutex_t mutex_num;  // mutex de num
pthread_mutex_t Cancela[7]; // um mutex para cada cancela

pthread_mutex_t mutex_fila; // para poder imprimir a fila de carros

int fila[NUM_CARROS];       // fila de carros

struct carro {
    int n_carro;         // id do carro
    int cancela;
};

void *carroEstacionando(void *){

    pthread_mutex_lock(&mutex_num);     //bloqueia o mutex_num
    num++;                              //incrementa o num
    int meu_num = num;
    pthread_mutex_unlock(&mutex_num);   //desbloqueia o mutex_num

    int cancela = rand() % 7;

    sem_wait(&s);
    printf("Carro %d chegou na cancela %d\n", meu_num, cancela);

    pthread_mutex_lock(&mutex_fila);
    fila[meu_num] = cancela;
    pthread_mutex_unlock(&mutex_fila);

    pthread_mutex_lock(&mutex_num);     //bloqueia o mutex_num

    printf("[");
    for (int i = 1; i <= num; i++){
        if(fila[i] == cancela){
            printf(" %d,", i);
        }
    }
    printf(" ]");

    printf("Carro %d entrando pela cancela %d\n", meu_num, cancela);
    sleep(5);                           //Atraso, para simular a passagem do carro pela cancela
    //pthread_mutex_unlock(&Cancela[cancela]);
    pthread_mutex_unlock(&mutex_num);   //desbloqueia o mutex_num

    int sorteio = rand() % 10;
    sleep(10 + sorteio);            //Atraso, para simular o tempo que o carro fica no estacionamento

    sem_post(&s);                   //Libera a vaga no estacionamento
    printf("Carro %d saindo do estacionamento\n", meu_num);

    pthread_mutex_lock(&mutex_fila);
    

    pthread_exit(NULL);

}

int main(int argc, char *argv[]){

    pthread_t carro[NUM_CARROS];        //threads
    pthread_attr_t attr;
    long status;                        //status da thread

    int i;

    sem_init(&s, 0, NUM_STEPS);             //inicializa o semáforo
    pthread_mutex_init(&mutex_num, NULL);   //inicializa o mutex_num
    pthread_mutex_init(&mutex_fila, NULL);  //inicializa o mutex_fila
    // for(i = 0; i < 7; i++){
    //     pthread_mutex_init(&Cancela[i], NULL);
    // }

    pthread_attr_init(&attr);           //inicializa a thread
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE); //estado da thread

    for(i = 0; i < NUM_CARROS; i++){
        //Talvez no final seja um NULL
        status = pthread_create(&carro[i], &attr, carroEstacionando, NULL);
        if(status){
            perror("pthread_create") ;
            exit (1);
        }
    }

    for(i = 0; i < NUM_CARROS; i++){
        status = pthread_join (carro[i], NULL);
        if(status){
            perror ("pthread_join") ;
            exit (1) ;
        }
    }

    pthread_attr_destroy (&attr) ;
    pthread_mutex_destroy(&mutex_num);


}