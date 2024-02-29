#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

// Laborátorio 1 de Sistemas Operacionais
// 2024.1
// Aluna: Jamilly da Silva Pinheiro

#define SIZE 128 

int myopen (const char *filename, int flags, int mode);
ssize_t myread(int fd, void *buf);
ssize_t mywrite(int fd, const void *buf, size_t count);
int myclose(int fd);

// r : 64 bits
// e : 32 bits

//Parâmetros pegados na tabela http://blog.rchapman.org/posts/Linux_System_Call_Table_for_x86_64/

//Para abertura
int myopen (const char *filename, int flags, int mode) {
  
 // int fd = 0;
 // return open(filename, flags);
  
 ssize_t response;

//vamos escrever a interface de um sistema operacional 
//feito para cada parâmetro passado
  __asm__("mov %0, %%rdi" : : "r"(filename));
  __asm__("mov %0, %%esi" : : "r"(flags));        //tem que sdi ao invés de rsi por ser um int
  __asm__("mov %0, %%edx" : : "r"(mode));                                         
  __asm__("mov $2, %rax");                        //número do registrador
  __asm__("syscall");                             //chamada de sistema
  __asm__("mov %%rax, %0" : "=r"(response) : );   //para receber dados                            

 return response;
}

//Para leitura
ssize_t myread(int fd, void *buf) {

  ssize_t response2;

  //vamos escrever a interface de um sistema operacional 
  //feito para cada parâmetro passado
  __asm__("mov %0, %%edi" : : "r"(fd));           //tem que sdi ao invés de rsi por ser um int
  __asm__("mov %0, %%rsi" : : "r"(buf));
  __asm__("mov %0, %%edx" : : "r"(SIZE));
  __asm__("mov $0, %rax");
  __asm__("syscall"); 
  __asm__("mov %%rax, %0" : "=r"(response2) : );

  return response2;
  //return read(fd, buf, SIZE);
}

//Para escrita
ssize_t mywrite(int fd, const void *buf, size_t count) {

  ssize_t response3;

  //vamos escrever a interface de um sistema operacional 
  //feito para cada parâmetro passado
  __asm__("mov %0, %%edi" : : "r"(fd));        //tem que sdi ao invés de rsi por ser um int
  __asm__("mov %0, %%rsi" : : "r"(buf));
  __asm__("mov %0, %%rdx" : : "r"(count));
  __asm__("mov $1, %rax");
  __asm__("syscall"); 
  __asm__("mov %%rax, %0" : "=r"(response3) : );

  return response3;
  //return write(fd, buf, count);
}

//Para fechamento
int myclose(int fd) {

  //vamos escrever a interface de um sistema operacional 
  //feito para cada parâmetro passado
  __asm__("mov %0, %%edi" : : "r"(fd));
  __asm__("mov $3, %rax");
  __asm__("syscall"); 
  __asm__("mov %%eax, %0" : "=r"(fd) : );

   return fd;
  //return close(fd);
}

int main (int argc, char** argv) {

  int file;
  char buf[SIZE];
  ssize_t readCount;

  if (argc != 2) {
    fprintf(stderr,"correct usage: %s <filename>\n", argv[0]);
    return 1;
  }

  file = myopen (argv[1], O_RDONLY, SIZE);
  if (file<0) { 
      perror("file open"); 
      return 1;
  }

  while ((readCount = myread (file, buf)) > 0)
    if ((mywrite (STDOUT_FILENO, buf, readCount) != readCount)) { 
        perror("write");
        return 1;
    }

  myclose (file);
  return 0;

}

