#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int main()
{
	int i,status;
	pid_t p1,p2,pid,pid2,pid3;
	pid3 = getpid();
	pid = fork();
	if (pid == 0)
	{
		p1 = getpid();
		p2 = getppid();		
		printf("eu sou: %d\n",p1);
		printf("meu pai é: %d\n\n",p2);
	} else {
		p1 = getpid();
		p2 = getppid();		
		printf("eu sou: %d\n",p1);
		printf("meu pai é: %d\n\n",p2);
		wait(NULL);
	}
	for (i=1;i<=8;i++)
	{
		if (pid == 0)
		{	
			
		} else {

			pid = fork();
			if (pid == 0)
			{
				p1 = getpid();
				p2 = getppid();
				printf("eu sou: %d\n",p1);
				printf("meu pai é: %d\n\n",p2);
			} else {
				wait(NULL);
			}
		}
	}
	printf("Sou o %d e terminei agora.\n\n",getpid());	
	return 0;
}
