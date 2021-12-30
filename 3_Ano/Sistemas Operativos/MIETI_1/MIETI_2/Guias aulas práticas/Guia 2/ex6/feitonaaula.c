#include <stdio.h>
#include <stdlib.h>

int lerLinha(int n,int M,int N,int mat[M][N],int nLinha)
{
	int i;
	int j=0;
	for (i=0;i<N;i++)
	{
		if (mat[nLinha][i] == n)
		{
			j++;
		}
	}
	return j;
}

int main(int argc, char *argv[])
{
	/*Atribuir parametros a variáveis*/
	int i,j,n,M,N;
	if (argc == 4)
	{
		M = atoi(argv[1]);
		N = atoi(argv[2]);
		n = atoi(argv[3]);
	} else {
		perror("Número errado de argumentos.");
	}
	printf("M = %d, N = %d, n = %d\n",M,N,n);

	/*FORMAR A MATRIZ E IMPRIMI-LA*/
	int mat[M][N];
	for (i=0;i<M;i++)
	{
		for (j=0;j<N;j++)
		{
			mat[i][j]=rand() % 10;		
		}
	}
	for (i=0;i<M;i++)
	{
		for (j=0;j<N;j++)
		{
			printf("%d ",mat[i][j]);		
		}
		printf("\n");
	}
	printf("\n");

	/*CRIAR VÁRIOS PROCESSO, EM QUE CADA UM LERÁ UMA LINHA*/
	int y;
	int status;
	for (i=0;i<M;i++)
	{
		if (fork() == 0)
		{
			y = lerLinha(n,M,N,mat,i);
			if (y != 0)
			{
				for (j=0;j<N;j++)
				{
					printf("%d ",mat[i][j]);		
				}
				printf("\n");
			}
			_exit(y);
		} 
	}

	//RECEBER OS VALORES LIDOS E RETURNADOS POR CADA PROCESSO
	int res = 0;
	for (i=0;i<M;i++)
	{
		wait(&status);
		if (WIFEXITED(status))
		{
			res += WEXITSTATUS(status);
		}
	}
	if (res > 0)
	{
		printf("Foi encontrado o número %d, %d vezes.\n",n,res);
	} else {
		printf("Não foi encontrado o número %d.\n",n);
	}

	return 0;
}
