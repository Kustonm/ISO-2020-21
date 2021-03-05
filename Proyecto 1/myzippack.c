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
  if(argc < 3){
   fprintf(stderr,"Numero de argumentos erroneo \n");
   exit(1);
  }
  if(open(argv[1],O_RDONLY ,0600) == -1){
   fprintf(stderr,"Fichero inexistente \n");
   exit(2);
  }
  
  if(open(argv[2],O_RDONLY,0600) == -1){
    fprintf(stderr, "Introduzca el nombre del fichero de salida \n");
    exit(3);
  }

  long size = lseek(argv[1], SEEK_END,0);
  char buff [512];
  if(open(argv[2],O_RDONLY,0600) == -1){
    int fichE;
    fichE = open(argv[1],O_RDONLY ,0600);
    comp.FileInfo.Type = "\0";
    comp.FileInfo.Compress = "n";
    comp.FileInfo.DataSize = size;
    comp.FileInfo.CompSize = size;
    int i = 0;
    for (i; i < sizeof(argv[1]); i++)
    {
      comp.FileInfo.DataFileName[i] = argv[1][i];
    }
   vector.vHead[0] = comp;
   int fichS = open(argv[2],O_CREAT|O_RDWR,0600);
   while(read(fichE,buff,1) != 0){
    write(fichS,buff,1);
   }
   close(fichE);
   close(fichS);
   return 0;
  }else{
   int fich1 = open(argv[1],O_RDONLY, 0600);
   int fich2 = open(argv[2],O_WRONLY, 0600);
   while(read(fich1,buff,1) != 0){
    write(fich2,buff,1);
   }
   close(fich1);
   close(fich2);
   return 0;
 }
}
