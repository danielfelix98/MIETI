#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/wait.h>
int main(int argc, char const *argv[])
{
	int status;
	for(int i=1;i<11;i++){
		pid_t pid=fork();
		if(pid==0){
			printf("Êu sou o filho nr.%d com pid %d e o meu pai tem pid %d\n",i,getpid(),getppid());
			_exit(i);
		}
		else{
			wait(&status);
			int ii=WEXITSTATUS(status);
			printf("Pai com pid=%d confirma que filho nr.%d terminou\n",getpid(),ii);
		}


	}





	return 0;
}