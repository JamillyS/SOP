#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h> //getcwd exige que use essa biblioteca
#include <string.h>
#include <limits.h> //PATH_MAX definido nessa biblioteca
#include <dirent.h>
#include <time.h>


int mycwd() {
  // char *getcwd(char buf[.size], size_t size);
    
    size_t size = PATH_MAX;
    char buf[size];

    if(getcwd(buf, sizeof(buf)) != NULL){
        printf("%s\n", buf);
    }else {
        perror("getcwd() error\n"); return 1;
     }
    return 0;  
    }

//Função para criar uma pasta
int mymkdir() {
  // int mkdir(const char *pathname, mode_t mode);
    
    char pathname[PATH_MAX];
    printf("Novo diretório: ");
    scanf("%s", &pathname);

    if(mkdir(pathname, 0700) != 0){
       perror("mkdir() error\n"); return 1;
    }

  return 0;
}

//Função para remover pasta/arquivos
int myrmdir() {
  // int rmdir(const char *pathname);
  //int size = statbuf.st_size;
    char pathname[PATH_MAX];
    printf("Diretório a ser removido: ");
    scanf("%s", &pathname);

  if(rmdir(pathname) != 0){
      perror("rmdir() error\n"); return 1;
  } 

  return 0;
}

//Função para entrar em um diretório
int mycd() {
  // int chdir(const char *path);
  char path[PATH_MAX];
  //int fd;
  printf("Para qual diretório você deseja ir? ");
  scanf("%s", &path);

  if(chdir(path) != 0){
    perror("cd() error\n"); return 1;
  }
  return 0;
}

int mystat() {
  char pathname[PATH_MAX];
  printf("Qual arquivo você deseja verificar os seus dados? ");
  scanf("%s", pathname);

  struct stat statbuf;

  if (stat(pathname, &statbuf) != 0) {
    perror("stat() error"); return 1;
  }

  // Use appropriate format specifiers and type casts for clarity
  printf("Tipo de arquivo: ");
  switch (statbuf.st_mode & S_IFMT) {
    case S_IFBLK: printf("block device\n"); break;
    case S_IFCHR: printf("character device\n"); break;
    case S_IFDIR: printf("directory\n"); break;
    case S_IFIFO: printf("FIFO/pipe\n"); break;
    case S_IFLNK: printf("symlink\n"); break;
    case S_IFREG: printf("regular file\n"); break;
    case S_IFSOCK: printf("socket\n"); break;
    default: printf("unknown?\n"); break;
  }

  // Corrected format specifiers and removed unnecessary parentheses
  printf("I-node number: %ju\n", statbuf.st_ino);
  printf("Mode: %jo (octal)\n", statbuf.st_mode);
  printf("Link count: %ju\n", statbuf.st_nlink);
  printf("Ownership: UID=%ju   GID=%ju\n", statbuf.st_uid, statbuf.st_gid);
  printf("Preferred I/O block size: %jd bytes\n", statbuf.st_blksize);
  printf("File size: %jd bytes\n", statbuf.st_size);
  printf("Blocks allocated: %jd\n", statbuf.st_blocks);

  printf("Last status change:       %s", ctime(&statbuf.st_ctime));
  printf("Last file access:         %s", ctime(&statbuf.st_atime));
  printf("Last file modification:   %s", ctime(&statbuf.st_mtime));

  return 0;
}

//solução do professor
int myls() {

   //  Abre o diretório
  DIR *d;
  struct dirent *dir;

  char name[PATH_MAX];
  printf("Diretório a listar: ");
  scanf("%s", &name);

  d = opendir(name);

  if (d != NULL) {
      while ((dir = readdir(d)) !=  NULL){
      printf("%s\n", dir->d_name);
      }
      closedir(d);
  }else{
    printf("Diretório %s não encontrado\n", &name);
    return 1;
  }
  return 0;

 }

//Minha solução
//int myls() {

  //printf("Listando conteúdo do diretório atual: \n");

  //  Abre o diretório
  //DIR *d = opendir(".");

 // if (d == NULL) {
  //  perror("ls() error");
   // return 1;
  //}

 // struct dirent *dir;

  //  Realizo a leitura do diretório enquanto não for NULL
 // while ((dir = readdir(d)) != NULL) {

    //  O if ignora os "." || ".." para são serem impressos
   // if (strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0) {
     // continue;
   // }

    // Impressão dos nomes dos arquivos
   // printf("%s ", dir->d_name);
  //}

  //fechamento do diretório
 // closedir(d);
 // printf("\n");

 // return 0;
//}


int main(int argc, char** argv) {
  int test = 0;
  while(test == 0) {
    char in[60];
    printf("myshell> ");
    scanf("%s", &in);
  
    if(strcmp(in, "exit") == 0) {
      test = 1;
    } else if(strcmp(in, "cwd") == 0) {
      mycwd();
    } else if(strcmp(in, "mkdir") == 0) {
      mymkdir();
    } else if(strcmp(in, "rmdir") == 0) {
      myrmdir();
    } else if(strcmp(in, "cd") == 0) {
      mycd();
    } else if(strcmp(in, "stat") == 0) {
      mystat();
    } else if(strcmp(in, "ls") == 0) {
      myls();
    } else {
      printf("Comando não encontrado\n");
    }
  }
}
