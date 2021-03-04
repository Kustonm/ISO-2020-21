#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>


#include "s_header.h"

struct s_Header comp;

int main(int argc , char *argv[]){

  if(argc < 2){
   fprintf(stderr,"Numero de argumentos erroneo \n");
   exit(1);
  }

  if(open(argv[1]) == -1){
   fprintf(stderr,"Fichero inexistente \n");
   exit(2);
  }

  int size = lseek(argv[1], SEEK_END);
  if(argc == 2){
   int fich = open(argv[1],O_CREAT|O_WRONLY, 0600);
   write(fich,fich,size);
   close(fich);
   return 0;
  }else{
   int fich1 = open(argv[1],O_CREAT|O_WRONLY, 0600);
   int fich2 = open(argv[2],O_CREAT|O_WRONLY, 0600);
   write(fich1,fich2,size);
   close(fich1);
   close(fich2);
   return 0;
 }
}
