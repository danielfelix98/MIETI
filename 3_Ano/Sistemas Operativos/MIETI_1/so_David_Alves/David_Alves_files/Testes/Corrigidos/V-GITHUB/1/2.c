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
Imprime soma do número de linhas de ficheiro passado como argumento
*/

int main(int argc, char *argv[]){

    long bytesRead = 0;
    int i;
    char c;
    int linhas = 0;

    int fd = open(argv[1], O_RDONLY);
    //abre o ficheiro
    do {

        i = read(fd, &c, 1);
        //le do ficheiro um a um e guarda em c o caractere
        if (c == '\n') linhas++;//se caractere e´ uma nova linha->linhas++
    } while (i > 0);//faz isto enquanto tem coisas para ler do ficheiro

    printf("%d\n", linhas);//imprime o n de linhas

    return 0;
}
