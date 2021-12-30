#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <fcntl.h>    /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <sys/types.h>
#include <string.h>
#define N 100
#define STDIN 0
#define STDOUT 1
#define STDERR 2

int main(int argc, char**argv){

    int fich_entrada,fich_saida;

    if(strcmp(argv[1],"-i")==0){
        fich_entrada = open(argv[2],O_RDONLY);
        dup2(fich_entrada,STDIN);
    
    
        if (strcmp(argv[3],"-o")==0){
            fich_saida=open(argv[4],O_WRONLY|O_CREAT,0666);
            dup2(fich_saida,STDOUT);
            execlp(argv[5],argv[5],NULL);
        }
       
    }
    return 1;
}