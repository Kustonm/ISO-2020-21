#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "s_header.h"

struct s_Header header;

int main (int argc, char *argv[]){
    
    int n,r;
    int ofile,ifile; 
    char buff [512];

    if (argc != 3) {
        fprintf(stderr,"Numero de argumentos incorrecto. \n");
        _exit(1);
    }

    ifile = open(argv[1],O_RDONLY,0600);
    if(ifile == -1){
        fprintf(stderr,"Error al abrir el fichero %s. \n",argv[1]);
       _exit(2);
    }

    ofile = open(argv[2],O_WRONLY|O_CREAT|O_TRUNC,0600);
    if (ofile == -1) {
       fprintf(stderr,"Error al abrir el fichero %s. \n",argv[2]);
       _exit(3);

    }

    bzero( &(header), S_HEADER_SIZE);

    header.FileInfo.Type = 'z';
    header.FileInfo.Compress = 'n';
    header.FileInfo.DataSize = S_HEADER_SIZE;
    header.FileInfo.CompSize = header.FileInfo.DataSize;
    strcpy(header.FileInfo.DataFileName,argv[1]);
    header.FileInfo.DatPosition = 0;
    while(read(ifile,buff,sizeof(buff)) != 0){
        strcpy(header.Dummy,buff);
   }
    
    n = write(ofile,&header,sizeof(header));

    if (n != sizeof(header)) {
       fprintf(stderr,"Error al escribir en el fichero %s. \n",argv[2]);
       close(ofile);	
       _exit(4);
    }

   close(ifile);
   close(ofile);
   return 0;

}
