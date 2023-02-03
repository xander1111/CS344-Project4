#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char const *argv[])
{
    int pfd[2];
    int err = pipe(pfd);
    if (err) {
        perror("Error creaing pipe");
    }

    int pid = fork();
    if (pid == 0) {
        dup2(pfd[0], 0);
        close(pfd[1]);

        execlp("wc", "wc", "-l", NULL);
    } else
    {
        dup2(pfd[1], 1);
        close(pfd[0]);

        execlp("ls", "ls", "-1a", NULL);
    }
    
}

