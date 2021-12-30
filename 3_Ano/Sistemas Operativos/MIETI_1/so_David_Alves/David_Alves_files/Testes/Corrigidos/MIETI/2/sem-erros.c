#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>

/*Este programa tem como objetivo esconder os erros do stdout e cada vez que haja um erro para os programas que recebe com arg
*/
int main(int argc, char const *argv[])
{
	int status;
	close(2);
	int pid;
	for(int i=1;i<argc;i++){
		pid=fork();
		if(pid==0){
			execlp(argv[i],argv[i],NULL);
			perror("erro");
			_exit(-1);
		}

	}



	for(int i=1;i<argc;i++){
		wait(&status);
		if (WEXITSTATUS(status)!=0){
			kill(0,SIGTERM);
		}
		
	}

}