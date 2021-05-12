#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>



main(int argc, char *argv[])

{   
    int pid, status, i;
     for(i = 0; i < 2;i++){
     
      
      switch (pid = fork()){

         case -1: error("fork");
                  break;
         case  0: /* child */
                 printf("SOy el hijo\n");
                  system(argv[4]);
                  break;
         default:
                  printf("HE entrado%d\n",pid);
                  if(waitpid(pid, &status, WNOHANG) != 0)
                  
                  kill(pid, SIGKILL);
                  break;
      }
      
   }
}
