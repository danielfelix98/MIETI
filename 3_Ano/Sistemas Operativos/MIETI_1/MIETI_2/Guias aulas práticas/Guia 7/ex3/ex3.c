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
	int M = atoi(argv[1]); //nº de linha
	int N = atoi(argv[2]); //nº de colunas
	int n = atoi(argv[3]); //nº pretendido
	int pids[N];
	int i,status,j;
	for (i=0;i<N;i++)
	{
		if ((pids[i] = fork()) == 0)
		{
			int linha[M];
			for (j=0;j<M;j++)
			{
				linha[j] = rand() % 10;
				if (linha[j] == n)
				{
					printf("Criei o nº.\n");
				}
			}
			for (j=0;j<M;j++)
			{
				if (linha[j] == n)
				{
					_exit(1); //encontrou o nº
				}
			}
			_exit(2); // não encontrou o nº
		}
	}
	for (i=0;i<N;i++)
	{
		wait(&status);
		if (WIFEXITED(status))
		{
			if (WEXITSTATUS(status) == 1)
			{
				printf("Encontrei e vou matar os processos.\n");
				//matar todos os processos
				for (j=0;j<N;j++)
				{
					kill(SIGKILL,pids[j]);
				}
				break;
			}
		}
	}
	return 0;
}