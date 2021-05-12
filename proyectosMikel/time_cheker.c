

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAXARG 10


main(int argc, char *argv[])
{
   if(argc < 5){
    fprintf(stderr,"Numero de argumentos incorrecto \n");
    exit(1);
   }

   int min_time = 0, max_time = 0, exact_time = 0,pid,status;
   double time_taken = 0, total = 0;
   clock_t start,end,final;
   char *arg[MAXARG];


   int j;
   for(j = 4; j < argc-1;j++){
      strcat(argv[4]," ");
      strcpy(argv[4],argv[j]);
   }
   argv[4][strlen(argv[4])] = '\0';
   get_parameters(argv[4], strlen(argv[4]+1), arg, MAXARG);

   int i;
   for(i = 0; i < atoi(argv[1]);i++){
      start = clock();
      
      switch (pid = fork()){

         case -1: error("fork");
                  break;
         case  0: /* child */
                  execvp(arg[0],arg);
                  exit(0);
                  break;
         default:
                  if(waitpid(pid, &status, WUNTRACED) != 0){
                     end = clock();
                     break;
                  }
      }
      final = ((double)end-start)/CLOCKS_PER_SEC;
      time_taken = (double)final;
      total = total + time_taken;
      if(time_taken < atoi(argv[2]))
         min_time++;
      else if(time_taken > atoi(argv[3]))
         max_time++;
      else
         exact_time++;
   }
   printf("\nEl programa ha tardado menos del tiempo estipulado %d veces\n",min_time);
   printf("El programa ha tardado más del tiempo estipulado %d veces\n",max_time);
   printf("El programa ha estado dentro de los valores estipulados %d veces\n",exact_time);
   printf("En total la ejecuccion ha tomado %f segundos\n",total);
}

void get_parameters(char *buf, int n, char *argk[], int m)
{
   int i, j;

   for (i = 0, j = 0; (i < n) && (j < m); j++)
   {
      /* advance blanks */
      while (((buf[i] == ' ') || (buf[i] == '\n')) && (i < n)) i++;
      if (i == n) break;
      argk[j] = &buf[i];
      /* find blank */
      while ((buf[i] != ' ') && (buf[i] != '\n')) i++;
      buf[i++] = '\0';
   }
   argk[j] = NULL;
}
