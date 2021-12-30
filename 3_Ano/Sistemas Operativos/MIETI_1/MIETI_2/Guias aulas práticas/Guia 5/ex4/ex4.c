#include <unistd.h>

int main(int argc, char *argv[])
{
	int pd[2];
	pipe(pd);

	if (fork())
	{
		close(pd[0]);
		close(1);
		dup(pd[1]);
		execlp("ls","ls","/etc",NULL);
	} else {
		close(pd[1]);
		dup2(pd[0],0);
		execlp("wc","wc","-l",NULL);
	}
	return 0;
}