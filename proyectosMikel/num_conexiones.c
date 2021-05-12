#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
    int pid, fd;
    char buf[256];

    if (mkfifo("myffifo", 0644) == -1)
        error("mkfifo");
    printf("FIFO creado\n");
    switch (pid = fork())
    {
    case -1:
        error("fork");
        break;

    case 0:
        if (close(1) == -1)
            error("close");
        if (open("myffifo", O_WRONLY) != 1)
            error("open");
        execlp("who", "who", NULL);
        error("execlp");
        break;
    }
    if (fd = close(0) == -1)
        error("close");
    if (open("myffifo", O_RDONLY) != 0)
        error("open");
    read(fd, buf, 256);
    printf("%s\n", buf);
    
    while ((pid = wait(NULL)) != -1)
        
    unlink("myffifo");
    printf("FIFO eliminado\n");
}
