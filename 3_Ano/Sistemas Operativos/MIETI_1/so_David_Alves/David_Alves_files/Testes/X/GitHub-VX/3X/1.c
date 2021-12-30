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
    char c;

    do {

        i = read(fd, &c, 1);

        if (i > 0) {
            buffer[bytesRead] = c;
            bytesRead++;
        }

    } while (i > 0 && bytesRead < maxBytes && c != '\n');

    buffer[bytesRead] = '\0';
    
    return bytesRead;
}



int main(int argc, char *argv[]){

	int nPipes = argc-1;
    int fd[2];
    int status;
    pid_t child;
    int bytesRead = 1;

    pipe(fd);

    child = fork();

    if (child == 0) {

        close(fd[0]);
        dup2(fd[1], 1);
        close(fd[1]);

        execlp(argv[2],argv[2],argv[3],NULL);
        exit(0);

    }

    else {

		wait(&child);

        close(fd[1]);

        char buffer[100];

        while (bytesRead > 0) {

        	sleep(atoi(argv[1]));

	        bytesRead = readLine(fd[0], buffer, 100);
	        write(1, buffer, bytesRead);
    	}
    }

    return 0;
}
