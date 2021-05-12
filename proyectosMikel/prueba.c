#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>

#define error(a) {perror(a); exit(1);};
#define BUFSIZE 512
#define MAXARG 10

void get_parameters(char *buf, int n, char *argk[], int ma);

main(int argc, char *argv[])
{
   int n, pid,  status, pid2,flag = 0;
   char buf[BUFSIZE];
   char *arg[MAXARG];

   for (n = 0; n < BUFSIZE; n++) buf[n] = '\0';

   /* read */
   write(1, "my_sh1> ", strlen("my_sh1> "));
   while ((n = read(0, buf, BUFSIZE)) > 0)
   {  
      buf[n] = '\n';
      n++;
      get_parameters(buf, n, arg, MAXARG);

      if (arg[0] == NULL)
      {
         write(1, "my_sh1> ", strlen("my_sh1> "));
         continue;
      }

      switch (pid = fork())
      {
         case -1: error("fork");
                  break;
         case  0: /* child */
         
                  if(!(pid2 = fork())){
                  execvp(arg[0], arg);
                  error("exec");
                  }
                  printf("%d (%s ...) process created\n", pid2, arg[0]);
                  flag = 1;
                  waitpid(pid,&status,0);
                  printf("%d (%s ...) process ended\n", pid2, arg[0]);
                  exit(pid);
                  break;

         default:    
                  break;
      }
   }
   printf("\n");
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
