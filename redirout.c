#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    if (argc < 3) {
        printf("Not enough arguments (minimum 2)\n");
        return -1;
    }

    int output_file = open(argv[1], O_WRONLY);

    int pfd[2];
    pipe(pfd);

    int pid = fork();
    if (pid == 0) {
        dup2(pfd[1], 1);
        close(pfd[0]);

        execvp(argv[2], argv + 2);
    }

    close(pfd[1]);

    char output_buffer[2048];
    int bytes_read = 0;
    do {
        bytes_read = read(pfd[0], output_buffer, 2048);

        write(output_file, output_buffer, bytes_read);
    } while (bytes_read > 0); 

    close(pfd[0]);
    close(output_file);
}
