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
  int fichE = open(argv[1],O_RDONLY ,0600);
  if(fichE == -1){
   fprintf(stderr,"Fichero inexistente \n");
   exit(2);
  }

  long size = lseek(argv[1], SEEK_END,0);
  char buff [512];
  char sizeS[256];
  sprintf(sizeS,"%ld",size);
  if(open(argv[2],O_RDONLY,0600) == -1){
    comp.FileInfo.Type = 'z';
    comp.FileInfo.Compress = 'n';
    comp.FileInfo.DataSize = size;
    comp.FileInfo.CompSize = size;
    comp.FileInfo.DatPosition = 0; //ToDO: En caso de anidacion hay que tener en cuenta donde empieza la siguiente seccion de datos.
    int i = 0;
    for (i; i < sizeof(argv[1]); i++)
    {
      comp.FileInfo.DataFileName[i] = argv[1][i];
    }
   vector.vHead[0] = comp;
  int fichS = open(argv[2],O_CREAT|O_RDWR,0600);
  int j;  
  for (j = 0; j < 80; j++)
  {
    write(fichS,"+",1);
  }
  //printf(comp.FileInfo.Type);
  char n = comp.FileInfo.Type;
  write(fichS,"\n",1);
  write(fichS,"+ Tipo: ",8);
  write(fichS,n,10);
  write(fichS," Compresion: ",strlen(" Compresion: "));
  write(fichS,comp.FileInfo.Compress,1);
  write(fichS," Tamano: ",strlen(" Tamano: "));
  write(fichS,sizeS,strlen(SizeS));
  write(fichS," TamanoComp: ",strlen(" TamanoComp: "));
  write(fichS,sizeS,strlen(sizeS));
  write(fichS," Nombre: ",strlen(" Nombre: "));
  write(fichS,comp.FileInfo.DataFileName,256);
  write(fichS," DataPos: ",strlen(" DataPos: "));
  write(fichS,"0",1); // ToDo: Conseguiir indice
  write(fichS," +",16);
  for (i = 0; i < 80; i++)
  {
    write(fichS,"+",1);
  }
  write(fichS,"+",1);
 
  while(read(fichE,buff,1) != 0){
    write(fichS,buff,1);
   }
   for (i = 0; i < 80; i++)
  {
    write(fichS,"+",1);
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
