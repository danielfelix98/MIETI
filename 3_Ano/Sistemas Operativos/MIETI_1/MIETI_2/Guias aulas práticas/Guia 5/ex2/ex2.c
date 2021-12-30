#include <unistd.h>

int main()
{
	int pd[2],n;
	pid_t pid;
	char buffer[256];
	char msg[] = "Msg do pai para o filho\n";
	pipe(pd);

	if ((pid = fork()) == 0)
	{
		close(pd[1]);
		while ((n = read(pd[0],buffer,256)) > 0)
		{
			write(1, buffer,n);
		}
	} else {
		close(pd[0]);
		write(pd[1],msg,sizeof(msg));
		sleep(5);
		close(pd[1]);
		wait(pid);
	}

	return 0;
}