#include <stdio.h>

#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
int main(int argc,char **argv[]){
int tam=10000000;

for(int i=0;i<tam;i++){
printf(".");
}
return 0;
}
