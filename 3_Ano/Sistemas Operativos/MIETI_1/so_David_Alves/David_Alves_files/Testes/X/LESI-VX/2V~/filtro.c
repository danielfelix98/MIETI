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

int filed;

void handler_abort(int signum){
	write(filed,"INTERROMPIDO",12);
	close(filed);
	kill(0,SIGTERM);
}

int main (int argc , char**argv){

	int pd[2];
	int fd[2];
	char *buf = NULL;
	int nread,length=1000;
	
	if(argc!=4){
		 exit(0); 
	}

	int pids[2];
	
	signal(SIGQUIT,handler_abort);
	pipe(pd);
	pipe(fd);
	filed = open(argv[3], O_WRONLY);
	setpgid(0,0);

	if(!(pids[0] = fork())){
		dup2(fd[0],0);
		dup2(pd[1],1);
		close(pd[0]);
		close(fd[1]);
		execlp(argv[1],argv[1],NULL);
		close(pd[1]);
		close(fd[0]);
		exit(EXIT_FAILURE);
	}

	if(!(pids[1] == fork())){
		dup2(pd[0],0);
		dup2(filed,1);
		close(pd[1]);
		execlp(argv[2],argv[2],NULL);
		close(pd[0]);
		close(filed);
		exit(EXIT_FAILURE);
	}

	while(1){
		nread = getline(&buf,&length,stdin);
		write(fd[1],buf,nread);
	}

}

