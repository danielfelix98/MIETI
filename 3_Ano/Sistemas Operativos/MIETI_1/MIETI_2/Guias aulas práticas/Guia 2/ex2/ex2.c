#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int main()
{
	pid_t p1,p2,p3,p4,p5,p6;
	pid_t f;
	p1 = getpid();
	p2 = getppid();
	printf("antes\n");
	printf("SOU PAI. SOU %d e MEU PAI é %d\n",p1,p2);
	printf("depois\n");
	f = fork();
	if (f == 0)
	{
		p3 = getpid();
		p4 = getppid();
		printf("SOU FILHO. SOU %d e MEU PAI é %d\n",p3,p4);
	} else {
		p5 = getpid();
		p6 = getppid();
		printf("SOU PAI. SOU %d e MEU PAI é %d\n",p5,p6);
		printf("MEU FILHO É %d\n",f);
	}
	return 0;
}
