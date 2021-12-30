#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h> 
#include <string.h>
#include <fcntl.h>
#include <errno.h>


int main(int argc, char **argv){
	
	int i;
	
	//Abre o descritor onde queremos escrever os logs
	int fd = open("xlog.log", O_WRONLY|O_CREAT, 0666);
	
	for(i=1; i<argc; i++){
		
		//Faz o fork e executa o filho
		int pid=fork();
		if (pid==0){//filho
			
			//Trocamos o output para o FD
			dup2(fd,1);
			close(fd);
			
			//Executa o comando
			execlp(argv[i],argv[i],NULL);
			

			//Caso o exec dê erro.
			exit(EXIT_FAILURE);
			perror("erro");
		}
		
	}
	
	for(i=1; i<argc; i++) wait(0);
	
	//Fechamos o FD porque não vamos precisar mais dele
	close(fd);
	
	return (EXIT_SUCCESS);
}