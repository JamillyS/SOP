// ex1: fork/wait básico
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char **argv, char **envp){ // envp variaveis de ambiente
    int test = 0;
    while(test == 0){
        char in[256]; //entrada
        char s[5][33]; //lê até 5 parametro
        int parms = 0; // núemro de parametro dividido por espaço
        int status; //usar wait
        bool w = true; // esperar o programa executar
        printf("myshell> ");

        fgets(in, 256, stdin);
        in(strcspn(in. "\n") = '\0');
        char *pch = strtok(in, " ");
        while (pch != NULL)
        {
            strcpy(s[parms], pch);
            pch = strtok(NULL, " ");
            parms++;
        }

        if(s[parms-1][0] == '&'){
            w = false;
        }

        if(parms > 0){
            fazer o fork
            fazer verificações
            chamar comando depois do for "execve"
            verificar erros do execve
            trabalhem com o erro do que imprime em _SIZE_T_DECLARED
            
            dois casos pro execve com wair outro sem
        }
        

    }
    
}