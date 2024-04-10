

#include <unistd.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>

 
#define SHM_SIZE 1024 /* make it a 1K shared memory segment */
 
int main(int argc, char *argv[]){

     //Verifico o número de argumentos
     if(argc != 3){
          printf("");
          return (-1);
     }
     //Se quiserem verifique o numero de caracteres do arquivo 

     //Crio um pipe
     int buf_size = 1024;
     char buf[buf_size];
     int fd[2];
     pipe(fd);

     //Criação do processo filho
     if(fork() != 0){

          //Abro o arquivo
          FILE *fp = fopen(argv[1], "r");

          //Verifico se o arquivo foi aberto
          if(fp != NULL){
               //fread serve para ler o arquivo
               //Coloco o argumento fd que é o pipe
               fread(buf, sizeof(char), buf_size, fp);

               //Verifico se houve erro na leitura
               if(ferror(fp) != 0){
                    perror("Erro de leitura");
                    return -1;
               }
               //write serve para escrever no pipe
               else{
               write(fd[1], buf, strlen(buf)+1);
          }
     }else{
          //Caso eu não consiga abrir o arquivo
          perror("Erro na abertura");
          return -1;
     }

     //Fecho o arquivo
     fclose(fp);

     }else{

          //Crio um arquivo 2 (que será a copia do arquivo 1)
          FILE *fp = fopen(argv[2], "ab+");

          //Verifico se o arquivo criado foi aberto
          if(fp != NULL){

               //fread serve para ler o arquivo
               read(fd[0], buf, buf_size);

               //fputs serve para escrever no arquivo
               fputs(buf, fp);

               //fecho o arquivo
               fclose(fp);
    

          //Se eu não consegui abrir o arquivo
          }else{
               perror("Erro na criação arquivo");
               return -1;
          }

     }

}

