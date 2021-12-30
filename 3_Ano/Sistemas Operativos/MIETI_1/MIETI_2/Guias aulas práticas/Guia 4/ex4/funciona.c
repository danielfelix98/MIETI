#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <signal.h>

int main(int argc, char *argv[])
{
	int n=1;
	if (argc > 1)
	{
		if (n == 1 && (strcmp(argv[1],"-i") == 0))
		{
			close(0);
			int fd_in = open(argv[2],O_RDONLY);
			if (fd_in == -1)
			{
				perror("Abrir ficheiro input");
			}
			n = n + 2;
		}
		if ((n == 1 && (strcmp(argv[1],"-o") == 0)) || (n == 3 && (strcmp(argv[3],"-o") == 0)))
		{
			close(1);
			int fd_out = open(argv[2],O_WRONLY | O_TRUNC | O_CREAT,0666);
			if (fd_out == -1)
			{
				perror("Abrir ficheiro output");
			}
			n = n + 2;
		}
	}
	printf("argc: %d\nn: %d\n",argc,n);
	char args[argc-n][100];
	int i;
	for (i=n;i<argc;i++)
	{
		strcpy(args[i-n],argv[i]);
		printf("%s\n",args[i-n]);
	}
	execlp(argv[n],args,NULL);
	return 0;
}