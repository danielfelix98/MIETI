#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sys/types.h> 
#include <unistd.h>
int main(int argc,char * argv[])
{
  int i , pid=1 , status;
    for(i=0; i<argc ; i++){
        if(pid){
        pid = fork();
        }
        else break;
    }


    if(pid!=0){//pai
        for(i=0; i<=argc; i++){
            wait(&status);
        	if(WEXITSTATUS(status)==0){
        		return 0;
        	}
		}
	}

    else{//filho
    	int res;
    	do{
    		res=execlp(argv[i],argv[i],NULL);
    		_exit(res);
		}while(res!=0 || res!=-1);

	}	

	return 0;
}
/*
Implemente um programa controlador que execute concorrentemente um conjunto de programas
especificados como argumento da sua linha de comando. O controlador deverá re-executar cada
programa enquanto não terminar com código de saı́da nulo. No final da sua execução, o controlador
deverá imprimir o número de vezes que cada programa foi executado. Considere que os programas são
especificados sem qualquer argumento*/