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

sem_t s;
int num = 0 ;
pthread_mutex_t mutex_num;
pthread_mutex_t Cancela[7];
//coloquei arg
void *carroEstacionando(void *){
    
    pthread_mutex_lock(&mutex_num);
    num++;
    int meu_num = num;
    pthread_mutex_unlock(&mutex_num);

    int cancela = rand() % 7;

    // Escrevo que o carro chegou na cancela
    //aqui as 7 cancelas
    //imprimir carro X entrando pela cancela Y
    //Esperar 5 segundos
    //faz unlock da cancela


    sem_wait(&s);
    printf("Carro %d chegou na cancela %d\n", meu_num, cancela);
    pthread_mutex_lock(&Cancela[cancela]);
    printf("Carro %d entrando pela cancela %d\n", meu_num, cancela);
    sleep(5);
    pthread_mutex_unlock(&Cancela[cancela]);



    int sorteio = rand() % 10;
    //esperar 10 +(a a 10) segundos
    sleep(10 + sorteio);
    sem_post(&s);
    //imprime que está saindo
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

    //cria as threads com um for ate NUM_CARRO
    for(i = 0; i < NUM_CARROS; i++){
        //Talvez no final seja um NULL
         status = pthread_create(&carro[i], &attr, carroEstacionando, (void *)&i);
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

    pthread_attr_destroy (&attr) ;
    pthread_mutex_destroy(&mutex_num);
    for(i = 0; i < 7; i++){
        pthread_mutex_destroy(&Cancela[i]);
    }
    pthread_exit (NULL) ;


}

// As cancelas serão o mutex
// sleep 5 segundos

// fila será o semafaro de tamanho 10
// distribuição aleatória

// numero maximo da estrutura da fila


//dow - entrada na fila
//up - saida da fila

//desafio 2 com struct