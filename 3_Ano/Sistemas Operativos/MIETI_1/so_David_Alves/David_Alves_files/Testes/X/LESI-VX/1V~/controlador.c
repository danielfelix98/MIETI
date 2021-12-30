#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include<stdio.h>
#include<sys/wait.h> 

int *pids;
int nprocessos;
int npa;
char** argvglobal;

void handler_alarme(int signum){
	int i;
	for(i = 0 ; i<nprocessos ; i++){
		kill(pids[i],SIGTERM);
	}
	exit(0);
}


int main (int argc , char**argv){

	int tempo = atoi(argv[1]);
	nprocessos = argc-2;
	signal(SIGALRM,handler_alarme);
	argvglobal = argv+2;
	npa=0;
	int pid;

	if((argc-2)==0) exit(0);
	pids = (int*) malloc (sizeof(argc-2));

	for(int i = 0; i<nprocessos ; i++){
		if(!(pids[i] = fork())){
			execlp(argvglobal[i],argvglobal[i],NULL);
		}
	}
	alarm(tempo);

	while(1){
		pid = wait(0); 
		for(int i = 0; i<nprocessos ; i++){
			if(pids[i] == pid){
				if(!(pids[i] = fork())){
					execlp(argvglobal[i],argvglobal[i],NULL);
					exit(EXIT_FAILURE);
				}else{
					break;
				}
			}	
		}
	}
}