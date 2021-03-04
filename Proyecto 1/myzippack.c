#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

#include "s_header.h"

struct s_mypack_headers vector;

struct s_Header comp;

int main(int argc , char *argv[]){

  int fdbook;

  if(argc < 2){
   fprintf(stderr,"Numero de argumentos erroneo \n");
   exit(1);
  }
  fdbook = open(argv[1],O_RDONLY ,0600);
  if( fdbook == -1){
   fprintf(stderr,"Fichero inexistente \n");
   exit(2);
  }

  long size = lseek(argv[1], SEEK_END,0);
  if(argc == 2){
    comp.FileInfo.Type = "\0";
    comp.FileInfo.Compress = "n";
    comp.FileInfo.DataSize = size;
    comp.FileInfo.CompSize = size;
    for (int i = 0; i < sizeof(argv[1]); i++)
    {
      comp.FileInfo.DataFileName[i] = argv[1][i];
    }
    vector.vHead[0] = comp;
   write(fdbook,fdbook,size);
   close(fdbook);
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
