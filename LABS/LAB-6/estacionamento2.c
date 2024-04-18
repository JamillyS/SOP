//Desafio 2: Ao imprimir a chegada de um carro em uma cancela imprima também a fila na referida cancela.
//Ex,: [3, 7, 8, 12] Carro 12 chegou na cancela 3.
//desafio 2 com struct

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_CARROS 20
#define NUM_STEPS 10

//Variaveis globais:
sem_t s;                    // Semáforo
int num = 0 ;               // num é o número de carros
pthread_mutex_t mutex_num;  // mutex de num
pthread_mutex_t Cancela[7]; // um mutex para cada cancela

//A struct serve para o numero do carro e a cancela que ele vai entrar
typedef struct{
    int n_carro;     //o id é o numero do carro
    int cancela;
} Carro;


void *carroEstacionando(void *){
    pthread_mutex_lock(&mutex_num);
    num++;
    int meu_num = num;
    pthread_mutex_unlock(&mutex_num);

    int cancela = rand() % 7;

    sem_wait(&s);
    printf("Carro %d chegou na cancela %d\n", meu_num, cancela);
    pthread_mutex_lock(&Cancela[cancela]);
    printf("Carro %d entrando pela cancela %d\n", meu_num, cancela);
    sleep(5);
    pthread_mutex_unlock(&Cancela[cancela]);

    int sorteio = rand() % 10;
    sleep(10 + sorteio);
    sem_post(&s);
    printf("Carro %d saindo do estacionamento\n", meu_num);

    pthread_exit(NULL);

}
 
int main(int argc, char *argv[]){

    pthread_t carro[NUM_CARROS];
    pthread_attr_t attr;
    long status;
    int i;

    sem_init(&s, 0, NUM_STEPS);
    pthread_mutex_init(&mutex_num, NULL);
    for(i = 0; i < 7; i++){
        pthread_mutex_init(&Cancela[i], NULL);
    }

    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    //Desafio 2: Ao imprimir a chegada de um carro em uma cancela imprima também a fila na referida cancela.
    //Ex,: [3, 7, 8, 12] Carro 12 chegou na cancela 3.

    Carro carros[NUM_CARROS];
    for(i = 0; i < NUM_CARROS; i++){
        carros[i].n_carro = i;
        carros[i].cancela = rand() % 7;
    }

    for(i = 0; i < NUM_CARROS; i++){
        status = pthread_create(&carro[i], &attr, carroEstacionando, (void *)&carros[i]);
        if(status){
            perror("pthread_create") ;
            exit (1);
        }
    }

    for(i = 0; i < NUM_CARROS; i++){
        status = pthread_join (carro[i], NULL);
        if(status){
            perror("pthread_join") ;
            exit (1);
        }
    }

    pthread_attr_destroy(&attr);
    for(i = 0; i < 7; i++){
        pthread_mutex_destroy(&Cancela[i]);
    }
    pthread_mutex_destroy(&mutex_num);
    sem_destroy(&s);
    pthread_exit(NULL);


}

