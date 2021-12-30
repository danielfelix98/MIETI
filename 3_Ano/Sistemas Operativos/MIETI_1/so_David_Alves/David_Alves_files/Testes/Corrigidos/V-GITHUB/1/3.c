#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <time.h>
#include <string.h>


/*
Imprime soma do número de linhas de ficheiros passados como argumentos
*/

int main(int argc, char *argv[]){

    // o nome do programa conta como argumento
    int nficheiros = argc-1;
    
    pid_t pid;
    int fd[nficheiros+1][2];

    for (int i = 1, j = 0; i < nficheiros+1 && j < nficheiros; i++) {

        pipe(fd[j]);

        pid = fork();

        if (pid == 0) {

            close(fd[j][0]);
            dup2(fd[j][1], 1);
            close(fd[j][1]);

            execl("2","2", argv[i], NULL);
            exit(0);

        }

        j++;

    }

    int status;
    int j = 0;
    int soma = 0;
    int linhas;

    // waiting for all child processes

    while ((wait(&status)) > 0);

    while (j < nficheiros) {

        close(fd[j][1]);
        char buffer[j][nficheiros];
        read(fd[j][0], buffer[j], sizeof(int));
        linhas  = atoi(buffer[j]);

        soma += linhas;

        j++;
    }

    printf("O número de linhas é %d.\n", soma);

    return 0;
}
