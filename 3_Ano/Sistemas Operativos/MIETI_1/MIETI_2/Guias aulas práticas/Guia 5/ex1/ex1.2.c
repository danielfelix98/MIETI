#include <unistd.h>

int main()
{
	int pd[2],n,pid;
	char buffer[256];
	char msg[] = "Msg do filho para pai\n";
	pipe(pd);

	if ((pid = fork()) == 0)
	{
		close(pd[0]);
		write(pd[1],msg,sizeof(msg));
	} else {
		close(pd[1]);
		n = read(pd[0],buffer,256);
		write(1, buffer,n);
	}
	return 0;
}