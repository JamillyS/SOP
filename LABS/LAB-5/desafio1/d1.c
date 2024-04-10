#include <unistd.h> 
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

char *message = "This is a message!!!" ;

int main()
{
    char buf[1024] ;
    int fd[4][2];

    for (int i=0 ; i<4; i++){
        pipe(fd[i]);   
    }

    if (fork() != 0) {
        //Processo pai
       // Escreve a mensagem do pipe
        write(fd[0][1], message, strlen (message) + 1) ;
    }
    else { 
        //Processo Filho 
        //Ler a mensagem do pipe
        read(fd[0][0], buf, 1024) ;
    
        printf("Eu sou o processo %d, filho de %d\n", getpid(), getppid());
        
        if(fork() != 0){
            //Processo pai
            // Escreve a mensagem do pipe));
            write(fd[1][1], message, strlen (message) + 1) ;

        }else{
            //Processo Filho 
            //Ler a mensagem do pipe
            read(fd[1][0], buf, 1024) ;
            printf("Eu sou o processo %d, filho de %d\n", getpid(), getppid());

            if(fork() != 0){
               //Processo pai
                // Escreve a mensagem do pipe));
                write(fd[2][1], message, strlen (message) + 1) ;   

            }else{
                read(fd[2][0], buf, 1024) ;
                //Processo Filho 
                //Ler a mensagem do pipe
                printf("Eu sou o processo %d, filho de %d\n", getpid(), getppid());

                if(fork() != 0){
                    //Processo pai
                    // Escreve a mensagem do pipe));
                    write(fd[3][1], message, strlen (message) + 1) ;

                }else{
                    //Processo Filho 
                    //Ler a mensagem do pipe
                    read(fd[3][0], buf, 1024) ;
                    printf("Eu sou o processo %d, filho de %d\n", getpid(), getppid());
                   
                }

            }

        }
    }
    return 0;
}



