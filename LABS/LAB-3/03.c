/*
Exercício fork/wait/exec
Crie um terminal "embrionário", que apenas lê caminhos completos de programas 
(ex.: /usr/bin/ls, /usr/bin/gedit, /usr/bin/firefox), com ou sem '&' ao final. O programa deve 
criar um processo filho (fork), que por sua vez deve se transformar no programa informado (execve). 
O programa deve bloquear a entrada (wait) se não houver um '&', ou liberar a entrada do programa para 
caso não haja o '&'. O programa deve funcionar em um laço que continua lendo novos comandos até que o 
usuário use o comando "sair".
*/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <string.h>

int main(int argc, char **argv, char **envp){ 
    // envp variaveis de ambiente
    int test = 0;

    while(test == 0){
        char in[256];   // entrada
        char s[5][33];  // lê até 5 parametro
        int parms = 0;  // número de parametro dividido por espaço
        int status;     // usar wait
        bool w = true;  // esperar o programa executar
        
        printf("myshell> ");
        fgets(in, 256, stdin);
        in[strcspn(in, "\n")] = '\0';

        char *pch = strtok(in, " ");
        while (pch != NULL){
            strcpy(s[parms], pch);
            pch = strtok(NULL, " ");
            parms++;
        }

        if(s[parms - 1][0] == '&'){
            w = false;
        }

        pid_t pid = fork(); // cria o filho
        if (pid == -1) {
            perror("fork falhou!\n");
            exit(-1); 
        }
    
        else if (pid == 0) { // processo filho
            execve(s[0], argv, envp);
            perror("erro de execução: ");
            exit(1);
        }
        
        wait(&status);

        if(strcmp(s[0], "sair") == 0){
            printf("Saindo... ");
            break;
            exit(0);
        }
    
    }
    exit(0);
}


//Instruções do professor
        // if(s[parms-1][0] == '&'){
        //     w = false;
        // }

        // if(parms > 0){
        //     fazer o fork
        //     fazer verificações
        //     chamar comando depois do for "execve"
        //     verificar erros do execve
// }
