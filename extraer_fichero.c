#include <sis/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

#include "s_header.h"

struct s_Header fS;
struct s_mypack_headers listC;

int main(argc [], char* argv[]){

 if(argc < 2){
 fprintf(stderr, "Numero de argumentos invalido");
 exit(1);
 }


 int fichE = open (argv[1],O_RDONLY,0600);
 char buff[512]

 if(fichE = -1){
 fprintf(stderr,"Fichero inexistente");
 exit(2);
 }

 if(argc > 3){
 fprintf(stderr,"Demasiados argumentos");
 exit(3);
 }

 String texto;
 int fichS= open(argv[2],O_CREAT,0600);
 texto = read(fichE,buff,1);

 while(read(fichE,buff,1) > 0){
 texto += buff; 
  if(strstr(texto,"Tipo: ") != NULL){
  free(texto);
  while(read(fichE,buff,1) > 0){
   if(buff != " "){
   fS.FileInfo.Type += buff;
   }
   if(buff != " "){
   fS.FileInfo.Compress += buff;
   }
   if(buff != " "){
    fS.FileInfo.DataSize += buff;
   }
   if(buff = " "){
   fS.FileInfo.CompSize += buff; 
   } 
   if(buff = " " ){
    fS.FileInfo.   
   }
   
  }
 }
 }


close(fichS);
return(0);
}
