#include <unistd.h>

int main()
{
	int pd[2],n,pid;
	char buffer[256];
	char msg[] = "Msg do pai para o filho\n";
	pipe(pd);

	if ((pid = fork()) == 0)
	{
		close(pd[1]);
		n = read(pd[0],buffer,256);
		write(1, buffer,n);
	} else {
		close(pd[0]);
		sleep(5);
		write(pd[1],msg,sizeof(msg));
		wait(pid);
	}

	return 0;
}