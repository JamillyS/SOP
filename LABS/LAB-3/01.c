#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
    int pid, pid2, status;

    pid = fork();   //Cria o filho de A
    if(pid == -1){  //fork falhou
        perror("fork falhou!\n");
        exit(-1); 

    
    }else if(pid == 0){ //Se A é filho de B
       
        pid2 = fork();  //Cria o filho de B

        if(pid2 == -1){ //fork falhou
            perror("fork falhou!\n");
            exit(-1);

        //Se B é filho de C
        }else if(pid == 0){  
            printf("Eu sou o processo %d, filho de %d\n", getpid(), getppid());
            sleep(1);   //Espera 1 segundo
            exit(0);    //Encerra o processo

        //Se B é pai
        }else { 
            wait(&status);  //Espera o filho terminar
            printf("Eu sou o processo %d, filho de %d\n", getpid(), getppid());
            sleep(1);   //Espera 1 segundo
            exit(0);    //Encerra o processo

        }
        
        //Se A é pai
        }else { 
        wait(&status); //Espera o filho terminar
        printf("Eu sou o processo %d, filho de %d\n", getpid(), getppid());
        sleep(1);   //Espera 1 segundo
        exit(0);    //Encerra o processo

    }
    exit(0);    //Encerra o processo
}