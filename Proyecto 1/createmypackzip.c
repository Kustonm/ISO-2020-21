#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

#include "s_header.h"

struct s_mypack_headers vector;

struct s_Header comp;

int main(int argc , char *argv[]){
  if(argc < 3){
   fprintf(stderr,"Numero de argumentos erroneo \n");
   exit(1);
  }
  int fichE = open(argv[1],O_RDONLY,0600);
  if(fichE == -1){
   fprintf(stderr,"Fichero inexistente \n");
   exit(2);
  }

  long size = lseek(fichE, SEEK_END,0);
  char sizeS[50];
  sprintf(sizeS,"%d",size);
  char buff [512];
  if(open(argv[2],O_RDONLY,0600) == -1){
    comp.FileInfo.Type = 'z';
    comp.FileInfo.Compress = 'n';
    comp.FileInfo.DataSize = size;
    comp.FileInfo.CompSize = size;
    comp.FileInfo.DatPosition = 0; //ToDO: En caso de anidacion hay que tener en cuenta donde empieza la siguiente seccion de datos.
    int i = 0;
    for (i; i < strlen(argv[1]); i++)
    {
      comp.FileInfo.DataFileName[i] = argv[1][i];
    }
  vector.vHead[0] = comp;
  int fichS = open(argv[2],O_CREAT|O_RDWR,0600);
  write(fichS,"\n",strlen("\n"));
  write(fichS,"Tipo: ",strlen("Tipo: "));
  write(fichS,&comp.FileInfo.Type,1);
  write(fichS," Compresion: ",strlen(" Compresion: "));
  write(fichS,&comp.FileInfo.Compress,1);
  write(fichS," Tamano: ", strlen(" Tamano: "));
  write(fichS,sizeS,strlen(sizeS));
  write(fichS," TamanoComp: ",strlen(" TamanoComp: "));
  write(fichS,sizeS,strlen(sizeS));
  write(fichS," Nombre: ",strlen(" Nombre: "));
  write(fichS,comp.FileInfo.DataFileName,strlen(comp.FileInfo.DataFileName));
  write(fichS," DataPos: ",strlen(" DataPos: "));
  write(fichS,"0", strlen("0")); // ToDo: conseguir parametro con DataPos
  write(fichS," \n",strlen(" \n"));


  write(fichS,"\n",strlen("\n"));
  lseek(fichE,SEEK_SET,0);
  while(read(fichE,buff,1) != 0){
    write(fichS,buff,1);
   }

  write(fichS,"\n",strlen("\n"));
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

