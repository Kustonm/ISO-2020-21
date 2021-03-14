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

int main(argc[], char *argv[])
{

    if (argc <= 2)
    {
        fprintf(stderr, "Numero de argumentos invalido");
        exit(1);
    }

    int fichE = open(argv[1], O_RDONLY, 0600);
    char buff[512]

        if (fichE = -1)
    {
        fprintf(stderr, "Fichero inexistente");
        exit(2);
    }

    if (argc > 3)
    {
        fprintf(stderr, "Demasiados argumentos");
        exit(3);
    }

    String texto;
    int fichS = open(argv[2], O_CREAT, 0600);
    texto = read(fichE, buff, 1);

    while (read(fichE, buff, 1) > 0)
    {
        texto += buff;
        if (strstr(texto, "Tipo: ") != NULL)
        {
            free(texto);
            while (read(fichE, buff, 1) > 0)
            {
                if (buff != " ")
                {
                    fS.FileInfo.Type += buff;
                }
            }
        }
        if (strstr(texto, "Compresion: ") != NULL)
        {
            free(texto);
            while (read(fichE, buff, 1) > 0)
            {
                if (buff != " ")
                {
                    fS.FileInfo.C += buff;
                }
            }
        }
        if (strstr(texto, "Tipo: ") != NULL)
        {
            free(texto);
            while (read(fichE, buff, 1) > 0)
            {
                if (buff != " ")
                {
                    fS.FileInfo.Type += buff;
                }
            }
        }
        if (strstr(texto, "Compresion: ") != NULL)
        {
            free(texto);
            while (read(fichE, buff, 1) > 0)
            {
                if (buff != " ")
                {
                    fS.FileInfo.Compress += buff;
                }
            }
        }
    }
    if (strstr(texto, "Tamano: ") != NULL)
    {
        free(texto);
        while (read(fichE, buff, 1) > 0)
        {
            if (buff != " ")
            {
                fS.FileInfo.DataSize += buff;
            }
        }
    }
    if (strstr(texto, "TamanoComp: ") != NULL)
    {
        free(texto);
        while (read(fichE, buff, 1) > 0)
        {
            if (buff != " ")
            {
                fS.FileInfo.CompSize += buff;
            }
        }
    }
    if (strstr(texto, "Nombre: ") != NULL)
    {
        free(texto);
        while (read(fichE, buff, 1) > 0)
        {
            if (buff != " ")
            {
                fS.FileInfo.DataFileName += buff;
            }
        }
    }
    if (strstr(texto, "DataPos: ") != NULL)
    {
        free(texto);
        while (read(fichE, buff, 1) > 0)
        {
            if (buff != " ")
            {
                fS.FileInfo.DatPosition += buff;
            }
        }
        listC[sizeof(listC)] = fS;
    }
    if (sizeof(listC) > argv[2])
    {
        write(fichS, "Tipo: ", strlen("+ Tipo: "));
        write(fichS, &listC.vHead[argv[2]].FileInfo.Type, 1);
        write(fichS, " Compresion: ", strlen(" Compresion: "));
        write(fichS, &listC.vHead[argv[2]].FileInfo.Compress, 1);
        write(fichS, " Tamano: ", strlen(" Tamano: "));
        write(fichS, listC.vHead[argv[2]].FileInfo.DataSize, strlen(listC.vHead[argv[2]].FileInfo.DataSize));
        write(fichS, " TamanoComp: ", strlen(" TamanoComp: "));
        write(fichS, listC.vHead[argv[2]].FileInfo.Compsize, strlen(listC.vHead[argv[2]].FileInfo.DataSize));
        write(fichS, " Nombre: ", strlen(" Nombre: "));
        write(fichS, listC.vHead[argv[2]].FileInfo.DataFileName, strlen(listC.vHead[argv[2]].FileInfo.DataFileName));
        write(fichS, " DataPos: ", strlen(" DataPos: "));
        write(fichS, "0", strlen("0")); // ToDo: conseguir parametro con DataPos
    }

    close(fichS);
    return (0);
}
