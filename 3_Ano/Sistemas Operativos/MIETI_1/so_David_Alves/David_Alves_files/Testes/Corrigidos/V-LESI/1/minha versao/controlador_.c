#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include<stdio.h>
#include<sys/wait.h> 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>


//executa apos x
int np;
int * pids;

void handler_alarm(int sig){

	for(int i=2;i<np;i++){
		//wait(&status);
		kill(pids[i],SIGTERM);
	}
}

int main (int argc, char * argv[]){
	pid_t pid;
	int status;
	int pd[2];
	int i;
	close(2);
	np=argc-2;
	//pids[np];
	pids = (int*) malloc (sizeof(argc-2));
	
	int tempo=atoi(argv[1]);
	signal(SIGALRM,handler_alarm);
	

	for(int i=2;i<argc;i++){
		pid=fork();
		if(pid==0){
			int exe=execlp(argv[i],argv[i],NULL);
			perror("erro");
			_exit(-1);
		}
		pids[i]=pid;
	}
	
	alarm(tempo);
	pause();

}
