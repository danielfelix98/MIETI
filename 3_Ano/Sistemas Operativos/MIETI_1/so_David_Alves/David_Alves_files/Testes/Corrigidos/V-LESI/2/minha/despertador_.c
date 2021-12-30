#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include<stdio.h>
#include<sys/wait.h> 

//executa apos x
//int np;
//int *pids;
//int args;
//int pid;
char **argvv;

void new(int sig){
	alarm(5);

}


void handler_alarm(int sig){

	
	int pid=fork();
	if(pid==0){
		execlp(argvv[1],argvv[1],NULL);
		perror("erro");
		_exit(-1);
	}
	wait(0);
	_exit(0);
	}


int main (int argc, char * argv[]){
	
	//args=argc;
	//np=argc-2;
	argvv=argv;
	//pids[np];
	
	
	int tempo=atoi(argv[2]);
	signal(SIGALRM,handler_alarm);
	signal(SIGUSR1,new);
	
	alarm(tempo);
	while(1){
	pause();}
}