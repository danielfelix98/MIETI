#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>


int main(int argc, char *argv[]){
	pid_t pid;
	int status;
	int pd[2];
	int i;
	close(2);
	int pids[argc-1];

	for(int i=1;i<argc;i++){
		pid=fork();
		if(pid==0){
			int exe=execlp(argv[i],argv[i],NULL);
			perror("erro");
			_exit(-1);
		}
	}
	
	for(int j=0;j<argc;j++){
		wait(&status);
		if(WEXITSTATUS(status)!=0){
			kill(0,SIGTERM);
		}


	}




}