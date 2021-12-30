#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include<stdio.h>
#include<sys/wait.h> 

char **argvglobal;

void handler_newalarm(int signum){
	alarm(5);
}

void handler_alarm(int signum){
	if(!fork()){
		execlp(argvglobal[1],argvglobal[1],NULL);
		exit(EXIT_FAILURE);
	}
	wait(0);
	exit(0);
}

int main (int argc, char**argv){

	int tempo;
	argvglobal = argv;
	if(argc<3) exit(0);
	tempo = atoi(argv[2]);
	signal(SIGUSR1,handler_newalarm);
	signal(SIGALRM,handler_alarm);
	alarm(tempo);
	while(1){
		pause();
	}
}