#include <unistd.h>


int main(int argc, char *argv[])
{
	int pd1[2];
	int pd2[2];
	int pd3[2];
	pipe(pd1);
	pipe(pd2);
	pipe(pd3);

	if (fork())
	{
		if (fork())
		{
			if (fork())
			{
				close(pd1[0]);
				dup2(pd1[1],1);
				execlp("grep","grep","-v","^#","/etc/passwd",NULL);
			} else {
				wait(NULL);
				close(pd1[1]);
				close(pd2[0]);
				dup2(pd1[0],0);
				dup2(pd2[1],1);
				execlp("cut","cut","-f7","-d:",NULL);
			}
		} else {
			wait(NULL);
			wait(NULL);
			close(pd2[1]);
			close(pd3[0]);
			dup2(pd2[0],0);
			dup2(pd3[1],1);
			execlp("uniq","uniq",NULL);
		}
	} else {		
		wait(NULL);
		wait(NULL);
		wait(NULL);
		close(pd3[1]);
		dup2(pd3[0],0);
		execlp("wc","wc","-l",NULL);
	}
	return 0;
}