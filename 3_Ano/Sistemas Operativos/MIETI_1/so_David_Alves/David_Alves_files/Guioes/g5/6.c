#include <stdio.h>
#include <unistd.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <fcntl.h>    /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <sys/types.h>
#include <string.h>
 

/* Este programa demonstra a funcionalidade da função popen */

 
int main()

{

int d;

FILE *executa; /* este descritor vai ser usado para ler a "saída" da

execução do comando "sort fich.txt" */

 

char buffer[81];

int i;

executa=popen("password.txt","r"); /* permite ler o resultado de

executar o comando "sort fich.txt" */

 

printf("Vou executar o comando 'sort fich.txt' e apresentar o resultado\n");

/* Enquanto existem dados para ler, lê esses dados e imprime-os no monitor */

while((d=fread(buffer,sizeof(char),80,executa)))

{

buffer[d]='\0';

printf("%s",buffer);

}

pclose(executa); /* fecha o descritor */

 

}
