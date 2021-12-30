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

    } while (i > 0 && bytesRead < maxBytes);

    buffer[bytesRead] = '\0';
    
    return bytesRead;
}


int compare (const void *a, const void *b) {
    return strcasecmp(a, b);
}

int sortWords (char* buffer, char* arg){
    char names[500][500]; 
    int i, j, ctr;   
 
    j = 0; ctr=0;
    for(i = 0; i <= (strlen(buffer)); i++) {
        // if space or NULL found, assign NULL into newString[ctr]
        if(buffer[i] == ' '||buffer[i] == '\0') {
            names[ctr][j]=' ';
            j++;
            names[ctr][j]='\0';
            ctr++;  //for next word
            j = 0;    //for next word, init index to 0
        }

        else {
            names[ctr][j]=buffer[i];
            j++;
        }
    }

    for (i = 0; i < strlen(names); i++) {
        if (names[i][j] == '\n') names[i][j] = '\0';
    }

    int n = 100;
    qsort (names, n, 500, compare); 


    char sorted[] = ".sorted";
    strcat(arg, sorted);

    int fd = open(arg, O_WRONLY | O_APPEND | O_CREAT);

    write(fd, names, 50000);

    printf("Ficheiro ordenado criado com sucesso.\n");

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

        bytesRead = readLine(fd[0], buffer, 500);

        sortWords(buffer, argv[2]);
    	
    }

    return 0;
}
