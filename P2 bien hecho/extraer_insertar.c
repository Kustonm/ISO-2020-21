#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "s_header.h"
#include <stdlib.h>


extern int extraer_fichero(char * file_mypackzip, unsigned int index);

extern int insertar_fichero(char *file_mypackzip, char *file_dat, int index);

int main(int argc, char *argv[]){
    int retex,retin,menu = 0;


    while(menu != 1 || menu != 2){
        printf("Selecciona que funcion deseas utilizar:\n");
        printf("1 - Extraer\n");
        printf("2 - Insertar \n");
        scanf("%d",&menu);
        if(menu == 1){
            int i = atoi(argv[2]);
            retex = extraer_fichero(argv[1],i);
            break;
        }
        else if(menu == 2){
            int i = atoi(argv[3]);
            insertar_fichero(argv[1],argv[2],i);
            break;
        }else
        {
            printf("El numero introducido no es correcto\n");
        }
    }
   
    if(retex != 0){
        if(retex == 1)
            fprintf(stderr,"No se puede abrir %s. \n",argv[1]);

        if(retex == 2)
            fprintf(stderr," Número de registro erróneo (index). \n");
    }
    if(retin != 0){
        if(retex == -1)
            fprintf(stderr,"No se puede abrir o crear %s. \n",argv[1]);

        if(retex == -2)
            fprintf(stderr,"No se puede abrir o crear %s. \n",argv[2]);

        if(retex == -3)
            fprintf(stderr,"Numero de index erroneo\n");

        if(retex == -4)
            fprintf(stderr,"index hare referencia a un s_header que ya contiene datos válidos.\n");

    }
    return 0;
}