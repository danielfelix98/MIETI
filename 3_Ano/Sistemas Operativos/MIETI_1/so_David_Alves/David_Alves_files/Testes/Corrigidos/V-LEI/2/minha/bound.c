#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>

int pid;

void signal_handler(int sig){
	if(sig==SIGALRM){
		kill(pid,SIGINT);
	}
	_exit(0);
}

int main(int argc, char const *argv[])
{
	int tempo=atoi(argv[1]);
	int size=atoi(argv[2]);
	int fd[2];
	pipe(fd);

	pid=fork();
	
	if(pid==0){
		close(fd[0]);
		dup2(fd[1],1);
		execvp(argv[3], argv + 3);
	}
	else{
		signal(SIGALRM,signal_handler);
		signal(SIGCHLD,signal_handler);

		
		close(fd[1]);
		int count=0;
		char buf;	
		char r;
		while( r = read(fd[0],&buf,1)>0){
			count++;
			write(1,&buf,1);
			if(count==size){
				kill(pid,SIGINT);
				_exit(0);
			}
		}
		alarm(tempo);
		pause();
		close(fd[0]);
	}






	return 0;
}