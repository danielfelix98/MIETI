#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int main()
{
	int i,status;
	pid_t p3,p4,p5,p6,pid;
	for (i=1;i<=10;i++)
	{
		pid = fork();
		if (pid == 0)
		{
			p3 = getpid();
			p4 = getppid();
			printf("SOU FILHO. SOU %d e MEU PAI é %d\n",p3,p4);
			_exit(i);
		} else {
			waitpid(pid,&status,0);
			printf("SOU O PAI. MEU FILHO FOI O %d NA POSICAO %d\n\n",pid,i);
		}
	}
	return 0;
}
