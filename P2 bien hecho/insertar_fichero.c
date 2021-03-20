#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "s_header.h"

struct s_Header header;
struct s_mypack_headers lista;

int insertar_fichero(char *file_mypackzip, char *file_dat, int index)
{

    int ofile, ifile, i = 0, n;
    char buff[512];

    ifile = open(file_dat, O_RDONLY, 0600);
    if (ifile == -1)
    {
        return (-2);
    }

    if (access(file_mypackzip, F_OK) == 0)
    {   ofile = open(file_mypackzip,O_WRONLY|O_RDONLY|O_TRUNC, 0600);
        while (read(ofile, &header, sizeof(header)) && i < NUM_HEADERS)
        {
            lista.vHead[i] = header;
            i++;
            
        }
        if (index > i)
            return -3;
        if (lista.vHead[index].FileInfo.DataSize != 0)
            return -4;
        n = read(ifile, &header, sizeof(header));
        lista.vHead[index] = header;
        n = write(ofile, &lista, sizeof(lista));
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
        if (ofile == -1)
        {
            fprintf(stderr, "Error al abrir el fichero %s. \n", file_mypackzip);
            return -1;
        }
        for (int j = 0; j <= index; j++)
            bzero(&(lista.vHead[j]), S_HEADER_SIZE);

        lista.vHead[index].FileInfo.Type = 'z';
        lista.vHead[index].FileInfo.Compress = 'n';
        lista.vHead[index].FileInfo.DataSize = S_HEADER_SIZE;
        lista.vHead[index].FileInfo.CompSize = header.FileInfo.DataSize;
        strcpy(lista.vHead[index].FileInfo.DataFileName, file_mypackzip);
        lista.vHead[index].FileInfo.DatPosition = 0;
        while (read(ifile, buff, sizeof(buff)) != 0)
        {
            strcpy(lista.vHead[index].Dummy, buff);
        }

        n = write(ofile, &lista, sizeof(lista));
        if (n != sizeof(lista))
        {
            fprintf(stderr, "Error al escribir en el fichero %s. \n", file_mypackzip);
            close(ofile);
            _exit(4);
        }
    }
}