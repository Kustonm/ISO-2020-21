#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "s_header.h"

struct s_Header header;
struct s_mypack_headers lista;

int extraer_fichero (char *file_mypackzip, unsigned int index){
    
   int file, n, i= 0;
   char Linea[512];

   file = open(file_mypackzip,O_RDONLY,0600);
   if(file == -1){
       return 1;
   }

    while(read(file,&header,sizeof(header))){
        lista.vHead[i] = header;
        i++;
    }
    if(index >= i)
        return 2;
    

    sprintf(Linea, "Tipo: %c \n", lista.vHead[index].FileInfo.Type);
    write(2, Linea, strlen(Linea));
    sprintf(Linea, "Compress: %d \n", lista.vHead[index].FileInfo.Compress);
    write(2, Linea, strlen(Linea));
    sprintf(Linea, "DataSize:  %lu \n",  lista.vHead[index].FileInfo.DataSize);
    write(2, Linea, strlen(Linea));
    sprintf(Linea, "CompSize: %lu \n", lista.vHead[index].FileInfo.CompSize);
    write(2, Linea, strlen(Linea));
    sprintf(Linea, "DataFileName %s \n", lista.vHead[index].FileInfo.DataFileName);
    write(2, Linea, strlen(Linea));
    sprintf(Linea, "DatPosition: %lu \n", lista.vHead[index].FileInfo.DatPosition);
    write(2, Linea, strlen(Linea));
    sprintf(Linea, "Texto: %s\n", lista.vHead[index].Dummy);
    write(2, Linea, strlen(Linea));

    close(file);

    return 0;



}