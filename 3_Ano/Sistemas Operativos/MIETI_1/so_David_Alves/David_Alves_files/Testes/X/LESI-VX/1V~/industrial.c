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
int main (int argc , char**argv){

	int flog = open("log.log",O_APPEND | O_CREAT , 0666);
	int pd[2];
	pipe(pd);
	char buf[1024];
	for(int i=1 ; i<argc ; i++){
		if (!fork()){
			if(!fork()){
				dup2(pd[1],1);
				close(pd[0]);
				execlp(argv[i],argv[i],NULL);
				close(pd[1]);
				exit(EXIT_FAILURE);
			}
			else{
				dup2(pd[0],0);
				close(pd[1]);
				while(read(pd[0],buf,1){
					write(flog,buf,1);
					write(1,buf,1);
				}
				wait(0);
			}
			exit(0);
		}
	}
	for(int i=1;i<(argc);i++){wait(0);}
	close(flog);
	return 0;
}
