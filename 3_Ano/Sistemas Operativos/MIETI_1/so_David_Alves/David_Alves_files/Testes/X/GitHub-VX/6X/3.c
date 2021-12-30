#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <time.h>
#include <string.h>
#include <ctype.h>



int main(int argc, char *argv[]){

    int fd[2];
    int status;
    pid_t child;
    int bytesRead = 0;
    char *resultado = NULL;
    char *buffer = NULL;
    size_t len = 0;

    pipe(fd);

    getline(&buffer, &len, stdin);
    getline(&resultado, &len, stdin);

    char names[500][500]; 
    int i, j, ctr;   
 
    j = 0; ctr = 0;
    for(i = 0; i <= (strlen(buffer)); i++) {
        
        if(buffer[i] == ' ' || buffer[i] == '\n') {
            ctr++;
            j = 0;
        }

        else {
            names[ctr][j] = buffer[i];
            j++;
        }
    }
    
    child = fork();
    if (child == 0) {

        close(fd[0]);
        dup2(fd[1], 1);
        close(fd[1]);

        execl("./calculator","./calculator",names[0],names[1],names[2],NULL);

    }

    else {
        
        wait(&child);
        close(fd[1]);

        char fim[500];
        int bytesReadFinal;

        
        bytesReadFinal = read(fd[0], fim, 500);


        if (strcmp(resultado, fim) == 0) {
            printf("O resultado é o esperado!");
        }
        write(1, fim, bytesReadFinal);

    }

    return 0;
}
