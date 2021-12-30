#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <time.h>
#include <string.h>

int main(int argc, char *argv[]){

	// um processo deve executar filtro e outro processo deve executar existe.
	// é recebido como argumento o número de pares de pipes a executar ao mesmo tempo

    int fd[2];
    int status;
    pid_t child;
    time_t start, end;
    int maxBytes = atoi(argv[2]);

    double maxTime;
    int maxTimeInInt = atoi(argv[1]);
    maxTime = (double)maxTimeInInt;
    
    pipe(fd);

    child = fork();

    if (child == 0) {

        close(fd[0]);
        dup2(fd[1], 1);
        close(fd[1]);

        execlp(argv[3],argv[3],NULL);
        exit(0);

    }
    
    else {

        start = time(NULL);

        double elapsed = 0;
        int bytesRead = 0;

        while (bytesRead < maxBytes && elapsed < maxTime) {

            end = time(NULL);
            elapsed = difftime(end, start);

            close(fd[1]);

            char buffer[maxBytes];

            bytesRead = read(fd[0], buffer, maxBytes);

            write(1, buffer, bytesRead);

        }

        kill(child, SIGKILL);

        if (bytesRead == maxBytes) 
            printf("\nLimite máximo de bytes alcançado. Programa terminado!!\n");

        if (elapsed == maxTime) 
            printf("\nLimite máximo de tempo alcançado. Programa terminado!!\n");

        close(fd[0]);


    }
    return 0;
}
