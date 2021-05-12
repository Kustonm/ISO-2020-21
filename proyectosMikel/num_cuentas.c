#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    int ret_val,pfd[2],pfd2[2];
    char buff[512];

    ret_val = pipe(pfd);
    if (ret_val != 0)
    {
        printf("Unable to create a pipe; errno=%d\n", errno);
        exit(1);
    }
    pipe(pfd);
    if(fork() == 0)
    {
        close(pfd[0]);
        dup2(pfd[1],STDOUT_FILENO);
        close(pfd[1]);
        execlp("last","last",NULL);
    }
    else
    {
        close(pfd[1]);
        pipe(pfd2); 
    if(fork() == 0)
    {
        close(pfd2[0]);
        
        dup2(pfd[0],STDIN_FILENO);close(pfd[0]);
        
        dup2(pfd2[1],STDOUT_FILENO);close(pfd2[1]);
        
        execlp("grep","grep","acaf00",(char*)NULL);
    }
        else
    {
       close(pfd[0]);
       close(pfd2[1]);
            
            if(fork()==0){
                dup2(pfd2[0],STDIN_FILENO);
                close(pfd2[0]);
                
                execlp("wc","wc","-l",NULL);
            }
        }
   }
    close(pfd2[0]);
    exit(0);
}

