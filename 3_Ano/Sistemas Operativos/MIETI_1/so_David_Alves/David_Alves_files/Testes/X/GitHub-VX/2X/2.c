#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <time.h>
#include <string.h>

int sortWords (char* buffer, char* arg){
    char names[500][500]; 
    int i, j, ctr;   
 
    j = 0; ctr = 0;
    for(i = 0; i <= (strlen(buffer)); i++) {
        
        if(buffer[i] == ' ' || buffer[i] == '\0') {
            // names[ctr][j] = ' ';
            // j++;
            // names[ctr][j] = '\0';
            ctr++;  // for next word
            j = 0;  //for next word, init index to 0
        }

        else {
            names[ctr][j] = buffer[i];
            j++;
        }
    }

    int lines = 0;
    char linhas[500];

    for (i = 0; i < 50; i++) {

        if (strcmp(arg, names[i]) == 0) {
            sprintf(linhas, "Palavra encontrada na linha %d\n", lines);
        }
        if (names[i][(strlen(names[i])-1)] == '\n') lines++;
    }

    write(1, linhas, strlen(linhas));

    return 0;

    }


int main(int argc, char *argv[]){

	int nPipes = argc-1;
    int fd[2];
    int status;
    pid_t child;
    int bytesRead = 1;
    char buffer[500];

    pipe(fd);

    child = fork();

    if (child == 0) {

        close(fd[0]);
        dup2(fd[1], 1);
        close(fd[1]);

        execlp(argv[1],argv[1],argv[2],NULL);
        exit(0);

    }

    else {

		wait(&child);

        close(fd[1]);

        bytesRead = read(fd[0], buffer, 500);

        sortWords(buffer, argv[3]);
    	
    }

    return 0;
}

