#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
	int fd1,fd2,fd3,n=0,i=0;
	char buffer[1024];

	

	if ((strcmp(argv[1],"-i")) == 0)
	{
		fd1 = open(argv[2], O_RDONLY);
		close(0);
		dup(fd1);
		n = n + 2;
	}

	if ((strcmp(argv[1],"-o")) == 0)
	{
		if (n == 0)
		{
			fd2 = open(argv[2], O_CREAT | O_WRONLY |O_TRUNC ,0644);
		}
		close(1);
		dup(fd2);
		n = n + 2;
	} else {
		if (argc > 3 && n == 2)
		{
			if ((strcmp(argv[3],"-o")) == 0)
			{
				fd2 = open(argv[4], O_CREAT | O_WRONLY |O_TRUNC ,0644);
			}
		
			close(1);
			dup(fd2);
			n = n + 2;
			printf("n = %d\n",n);
		}
	}
	
	n++;
	char *comando = argv[n];
	
	char **argumentos;
	argumentos = malloc(sizeof(char*)*(argc-n+1));
	int index;
	for (index = n; index < argc; ++index)
	{
	   argumentos[index] = malloc( strlen(*argv)+1 ); // add one for the \0
	   strcpy(argumentos[index-n], argv[index]);
	}
	argumentos[index] = NULL;



	n++;
	/*for (i = n;i < argc;i++)
	{
		argumentos[i-n] = argv[i];
	}*/

	execlp(comando,comando,argumentos,NULL);

	return 0;
	
}