#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int main()
{
	int i,status;
	pid_t p1,p2,pid,pid2;
	pid = fork();
	p1 = getpid();
	p2 = getppid();		
	printf("eu sou: %d\n",p1);
	printf("meu pai é: %d\n\n",p2);	
	pid2 = pid;
	for (i=1;i<=8;i++)
	{
		if (pid2 == 0)
		{	
			pid2 = fork();
			if (pid2 == 0)
			{
				p1 = getpid();
				p2 = getppid();
				printf("eu sou: %d\n",p1);
				printf("meu pai é: %d\n\n",p2);	
			}
		} else {
			waitpid(pid2,&status,0);
		}
	}
	return 0;
}
