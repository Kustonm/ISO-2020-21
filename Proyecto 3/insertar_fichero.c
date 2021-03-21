#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "s_header.h"
#include <dirent.h> 


struct s_Header header;
struct s_mypack_headers lista;

int insertar_fichero(char *file_mypackzip, char *file_dat, int index)
{
    struct dirent *de;

    int ofile, ifile, i = 0, n, directorio = 0;
    char buff[512];


    DIR *dr = opendir(file_dat);

        if (dr != NULL){  // opendir returns NULL if couldn't open directory 
        printf("hola\n");
        directorio = 1;
        header.FileInfo.Type = 'z';
        header.FileInfo.Compress = 'n';
        header.FileInfo.DataSize = 0;
        header.FileInfo.CompSize = header.FileInfo.DataSize;
        strcpy(header.FileInfo.DataFileName, file_dat);
        header.FileInfo.DatPosition = 0;
        header.FileInfo.FileType = 'd';
        while ((de = readdir(dr)) != NULL)
        {
            strcpy(header.Dummy, de->d_name);
        }
    }
        
    
   
    if (access(file_mypackzip, F_OK) == 0)
    {   ofile = open(file_mypackzip,O_WRONLY|O_RDONLY|O_TRUNC, 0600);
        if(!directorio){
            ifile = open(file_dat, O_RDONLY, 0600);
            if (ifile == -1)
            {
                return (-2);
            }
            while (read(ofile, &header, sizeof(header)) && i < NUM_HEADERS)
            {
                lista.vHead[i] = header;
                i++;
                
            }
        }
        if (index > i)
            return -3;
        if (lista.vHead[index].FileInfo.DataSize != 0)
            return -4;
        if(!directorio)
            n = read(ifile, &header, sizeof(header));
        lista.vHead[index] = header;
        n = write(ofile, &lista, sizeof(lista));
        printf("%d,%d\n",n,sizeof(lista));
       if (n != sizeof(lista))
        {
            fprintf(stderr, "Error al escribir en el fichero %s. \n", file_mypackzip);
            close(ofile);
            _exit(4);
        }
        
    }
    else
    {
        ofile = open(file_mypackzip, O_WRONLY | O_CREAT | O_TRUNC, 0600);
        ifile = open(file_dat, O_RDONLY, 0600);

        if (ofile == -1)
        {
            fprintf(stderr, "Error al abrir el fichero %s. \n", file_mypackzip);
            return -1;
        }
        int j;
        for (j = 0; j <= index; j++)
            bzero(&(lista.vHead[j]), S_HEADER_SIZE);
    
        if(directorio){
            lista.vHead[index].FileInfo.Type = 'z';
            lista.vHead[index].FileInfo.Compress = 'n';
            lista.vHead[index].FileInfo.DataSize = S_HEADER_SIZE;
            lista.vHead[index].FileInfo.CompSize = header.FileInfo.DataSize;
            strcpy(lista.vHead[index].FileInfo.DataFileName, file_mypackzip);
            lista.vHead[index].FileInfo.DatPosition = 0;
            lista.vHead[index].FileInfo.FileType = 'r';
            while (read(ifile, buff, sizeof(buff)) != 0)
            {
                strcpy(lista.vHead[index].Dummy, buff);
            }
        }else{
            lista.vHead[index] = header;
        }
        n = write(ofile, &lista, sizeof(lista));
        if (n != sizeof(lista))
        {
            fprintf(stderr, "Error al escribir en el fichero %s. \n", file_mypackzip);
            close(ofile);
            _exit(4);
        }
    }
    closedir(dr);     

    return 0;
}
