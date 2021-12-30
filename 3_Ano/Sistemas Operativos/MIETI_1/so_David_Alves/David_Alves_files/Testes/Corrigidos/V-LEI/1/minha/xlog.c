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

int main(int argc, char const *argv[])
{
	int fd=open("teste.log",O_CREAT|O_TRUNC|O_WRONLY,0666);
	
	int status;
	int pid;
	for(int i=1;i<argc;i++){
		pid=fork();
		if(pid==0){
			dup2(fd,1);
			execlp(argv[i],argv[i],NULL);
			close(fd);
			perror("erro");
			_exit(-1);
		}

	}



	for(int i=1;i<argc;i++){
		wait(&status);
		}

	close(fd);
	







	return 0;
}

