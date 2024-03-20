/*
Exercício status/wait
O status passado como parâmetro à função wait(&status) é, na verdade, o mecanismo de retorno de resultado do wait/waitpid. 
Ao retornar, esta variável contém informações sobre o resultado da execução do processo filho. Por exemplo, se um processo 
terminou normalmente (i.e., chamou exit), o comando WIFEXITED(status) retorna true. Este comando retorna false se o processo 
foi abortado (e.g., segmentation fault) ou morto (e.g., kill). Investigue no manual do wait no Linux (man wait) o funcionamento
do comando WEXITSTATUS(status), e use-o para modificar o exercício anterior para calcular o 5!, sendo que cada processo pode 
executar apenas uma multiplicação.
*/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
    int pid, status;

    int resp = 1;
    int i = 5;

    // printf("5! = %d", resp);
    // exit(0);

    pid = fork();
    if (pid < 0) {
            perror("fork falhou!\n");
            exit(-1);
    } else if(pid == 0){
        resp *= i;
        return resp;
    }else{
        wait(&status);
            if(WIFEXITED(status)){
                i--;
                resp = WEXITSTATUS(status);
            }
    }

    pid = fork();
    if (pid < 0) {
            perror("fork falhou!\n");
            exit(-1);
    } else if(pid == 0){
        resp *= i;
        return resp;
    }else{
        wait(&status);
            if(WIFEXITED(status)){
                i--;
                resp = WEXITSTATUS(status);
            }
    }


    pid = fork();
    if (pid < 0) {
            perror("fork falhou!\n");
            exit(-1);
    } else if(pid == 0){
        resp *= i;
        return resp;
    }else{
        wait(&status);
            if(WIFEXITED(status)){
                i--;
                resp = WEXITSTATUS(status);
            }
    }


    pid = fork();
    if (pid < 0) {
            perror("fork falhou!\n");
            exit(-1);
    } else if(pid == 0){
        resp *= i;
        return resp;
    }else{
        wait(&status);
            if(WIFEXITED(status)){
                i--;
                resp = WEXITSTATUS(status);
            }
    }


    pid = fork();
    if (pid < 0) {
            perror("fork falhou!\n");
            exit(-1);
    } else if(pid == 0){
        resp *= i;
        return resp;
    }else{
        wait(&status);
            if(WIFEXITED(status)){
                i--;
                resp = WEXITSTATUS(status);
            }
    }

    printf("5! = %d \n", resp);
    exit(0);

}
