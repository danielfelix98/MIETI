#include <unistd.h>

int main()
{
	int pd[2];
	pipe(pd);
	int n;
	char buffer[256];
	if (fork())
	{
		close(pd[1]);
		close(0);
		dup(pd[0]);
		execlp("wc","wc",NULL);
	} else {
		close(pd[0]);
		while ((n = read(0,buffer,sizeof(buffer))) > 0)
		{
			write(pd[1],buffer,n);
		}
		wait(NULL);
	}
	return 0;
}