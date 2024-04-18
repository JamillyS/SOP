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
 
// número de NUM_THREADS
#define NUM_CARROS 20
// número de vagas
#define NUM_STEPS 10    

sem_t s;
int num = 0 ;
pthread_mutex_t mutex_num;
pthread_mutex_t cancela[7];

void *carroEstacionando(void *){
    
    //mutex
    //primeiro carro vai ser o carro 1
    pthread_mutex_lock(&mutex_num);
    num++;
    int meu_num = num;
    pthread_mutex_lock(&mutex_num);

    int cancela = rand() % 7;

    //Escreve que o carro chegou na cancela
    sem_wait(&s);
    //aqui as 7 cancelas
    //imprimir carro X entrando pela cancela Y
    //Esperar 5 segundos
    //faz unlock da cancela

    //esperar 10 +(a a 10) segundos
    sem_post(&s);
    //imprime que está saindo

    pthread_exit(NULL);


}
 
int main(int argc, char *argv[]){

    pthread_t carro[NUM_CARROS];
    pthread_attr_t attr;
    long status;
    int i;

    sem_init(&s, 0, 10);
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    //cria as threads com um for ate NUM_CARRO
    for(i = 0; i < NUM_CARROS; i++){
        status = pthread_create(&carro[i], &attr, carroEstacionando, (void *) i );
        if(status){
            perror("pthread_create") ;
            exit (1);
        }
    }

    //Realiza join usando  for até o NUM_CARROS
    for(i = 0; i < NUM_CARROS; i++){
        status = pthread_join (carro[i], NULL);
        if(status){
            perror ("pthread_join") ;
            exit (1) ;
        }
    }


}

// As cancelas serão o mutex
// sleep 5 segundos

// fila será o semafaro de tamanho 10
// distribuição aleatória

// numero maximo da estrutura da fila


//dow - entrada na fila
//up - saida da fila

//desafio 2 com struct