#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int mySystem(char *args)
{	pid_t pid=fork();

	if(pid==0){
	execl("/bin/sh","sh","-c",args,NULL);
	perror("fail exec");
	return -1;
	}
	else//pai
	{
	wait(NULL);
	return 0;
	}
}

int main(int argc, char * argv[])
{
	mySystem("ls -l");
}
