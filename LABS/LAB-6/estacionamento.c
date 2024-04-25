//Desafio 1: Considere o desenvolvimento de um sistema que simule um  estacionamento no qual:
// - O número de vagas neste estacionamento possui limite de 10 e inicia vazio;
// - Existem 7 cancelas de entrada;
// - Têm-se 20 carros chegando aleatoriamente em qualquer uma das 7 cancelas "ao mesmo tempo";
// - A passagem de um carro pela cancela leva 5 segundos e nenhum carro pode entrar pela mesma enquanto um carro está em passagem;
// - Uma vez estacionado o carro deve sair em tempo entre 10 e 20 segundos;
// - Você deve numerar os carros por ordem de chegada independente de cancela;

//Imprima:
//  - Quando um carro X chega em uma cancela Y;
//  - Quando o carro X começa a entrar pela cancela Y;
//  - Quando o carro X deixa o estacionamento.

//  Obs1: Note que os carros irão entrar por ordem de chegada, independente de em qual cancela estejam.
// 
//  Obs2: Note que podem haver cancelas sem carros na fila de entrada e fila maior em outras cancelas.

//gcc -Wall estacionamento.c -o estacionamento -lpthread

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

void *carroEstacionando(void *){

    pthread_mutex_lock(&mutex_num);     //bloqueia o mutex_num
    num++;                              //incrementa o num
    int meu_num = num;              
    pthread_mutex_unlock(&mutex_num);   //desbloqueia o mutex_num  

    int cancela = rand() % 7;

    sem_wait(&s);   
    printf("Carro %d chegou na cancela %d\n", meu_num, cancela);
    //pthread_mutex_lock(&Cancela[cancela]);
    pthread_mutex_lock(&mutex_num);     //bloqueia o mutex_num
    printf("Carro %d entrando pela cancela %d\n", meu_num, cancela);
    sleep(5);                           //Atraso, para simular a passagem do carro pela cancela
    //pthread_mutex_unlock(&Cancela[cancela]);
    pthread_mutex_unlock(&mutex_num);   //desbloqueia o mutex_num

    int sorteio = rand() % 10;
    sleep(10 + sorteio);            //Atraso, para simular o tempo que o carro fica no estacionamento

    sem_post(&s);                   //Libera a vaga no estacionamento
    printf("Carro %d saindo do estacionamento\n", meu_num);
    pthread_exit(NULL);

}
 
int main(int argc, char *argv[]){

    pthread_t carro[NUM_CARROS];        //threads
    pthread_attr_t attr;                
    long status;                        //status da thread
    
    int i;

    sem_init(&s, 0, NUM_STEPS);             //inicializa o semáforo
    pthread_mutex_init(&mutex_num, NULL);   //inicializa o mutex_num   
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