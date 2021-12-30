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

    int lines = 0;

    do {

        i = read(fd, &c, 1);

        if (i > 0) {
            buffer[bytesRead] = c;
            bytesRead++;

        }

    } while (i > 0 && bytesRead < maxBytes && c != 'a');

    buffer[bytesRead] = '\0';

    // Devolver o numero de bytes lidos
    return bytesRead;
}


int main(int argc, char *argv[]){

	// um processo deve executar filtro e outro processo deve executar existe.
	// é recebido como argumento o número de pares de pipes a executar ao mesmo tempo

	int nPipes = atoi(argv[1]);
    int fd[nPipes][2];
    int status;
    char buffer[50];
    char buffer1[50];
    int bytesRead = 1;
    pid_t childId;

    for (int i = 0; i < atoi(argv[1]); i++) {

        pipe(fd[i]);
        pid_t child1, child2;

        // tenho de passar o argv[2] ao filtro

        if (!(child1 = fork())) {

            close(fd[i][0]);
            dup2(fd[i][1], 1);
            close(fd[i][1]);

            execl("./filtro","./filtro",argv[2],NULL);
            exit(0);
        }

        else if (!(child2 = fork())) {


            dup2(fd[i][0], 0);
            close(fd[i][0]);

            dup2(fd[i][1], 1);
            close(fd[i][1]);

            execl("./existe","./existe",NULL);
            exit(0);

        } else {

			wait(&child1);
        	wait(&child2);

            close(fd[i][1]);

            bytesRead = read(fd[i][0], buffer, 20);

            close(fd[i][0]);

            write(1, buffer, bytesRead);

        }

    }

    remove(argv[2]);

    return 0;
}

