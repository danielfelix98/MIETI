#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
	for(int i=1;i<argc;i++){
		pid_t pid=fork();
		if(pid==0){
			execlp(argv[i],argv[i],NULL);
		}

	}

	for(int j=1;j<argc;j++)
		wait(NULL);
	return 0;
}