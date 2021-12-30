#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>


int main(int argc, char * argv[])
{
	int i = 1, j=0;

	for(i=1; i<=argc; i++)
	{
		pid_t pid=fork();
		if(pid==0){//filho
		execlp(argv[i], argv[i],NULL);
		}
	}
	
	for(j=0; j<=argc; j++)//pai
	{
		wait(NULL);
	}
	return 0;
}
 
