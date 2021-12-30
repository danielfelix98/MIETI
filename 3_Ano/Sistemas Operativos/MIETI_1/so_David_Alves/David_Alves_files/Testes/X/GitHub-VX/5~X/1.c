#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <time.h>
#include <string.h>


ssize_t readLine(int fd, char* buffer, long maxBytes) {

    long bytesRead = 0;
    ssize_t i;

    int lines = 0;

    do {
        char c;
        i = read(fd, &c, 1);

        if (i > 0) {
            buffer[bytesRead] = c;
            bytesRead++;

            if (c == '\n') lines++;
        }

    } while (i > 0 && bytesRead < maxBytes && lines < 10);

    buffer[bytesRead] = '\0';

    // Devolver o numero de bytes lidos
    return bytesRead;
}


int main(int argc, char *argv[]){

    int fd[2];
    int j = 0;
    int status;
    char buffer[500];
    int bytesRead = 1;
    pid_t childId;

    for (int i = 1; i < argc; i++) {

        pipe(fd);
        j++;
        childId = fork();

        if (childId == 0) {

            close(fd[0]);
            dup2(fd[1], 1);
            close(fd[1]);

            execlp(argv[i],argv[i],NULL);
            exit(0);
        }

        else {

            sleep(1);

            while (wait(&status) > 0) {
                printf("Um filho terminou com exitstatus %d\n", status);

            }

            close(fd[1]);

            bytesRead = readLine(fd[0], buffer, 1000);

            write(1, buffer, bytesRead);

        }
        
    }

    return 0;
}

