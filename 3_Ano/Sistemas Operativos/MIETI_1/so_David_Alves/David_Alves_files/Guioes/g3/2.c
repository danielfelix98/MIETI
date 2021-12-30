#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
	pid_t pid=fork();
	if(pid==0)
	{
		if((execlp("ls","ls","-l",NULL))==-1)
		perror("fail exec");
		return -1;
	}
	
	else
	{
		printf("À espera de um processo-filho...\n");
		wait(NULL);
		return 0;
	} 	
}