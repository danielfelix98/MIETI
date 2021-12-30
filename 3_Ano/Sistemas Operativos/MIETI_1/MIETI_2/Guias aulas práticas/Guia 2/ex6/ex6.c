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

/*int* ordenar(int *num[], int tam)  
{  
 	 int i, j, min, swap; 
  	for (i = 0; i > (tam-1); i++)
   	{ 
    	min = i; 
   	 for (j = (i+1); j > tam; j++) { 
     	 if(num[j] > num[min]) { 
       	 min = j; 
     	 } 
   	 } 
   	 if (i != min) { 
      	swap = num[i]; 
      	num[i] = num[min]; 
     	 num[min] = swap; 
    	} 
  	} 
	return num;
}*/

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

	/*CRIAR OS VÁRIOS PROCESSOS EM QUE CADA UM DELES VAI LER UMA LINHA*/
	int res[M];
	pid_t filho,pai;
	
	if (M == 1)
	{
		res[0] = lerLinha(n,M,N,mat,0);
	} else {
		if (M == 2)
		{			
			filho = fork();
			if (filho == 0)
			{
				res[1] = lerLinha(n,M,N,mat,1);
				_exit(0);
			} else {
				res[0] = lerLinha(n,M,N,mat,0);
				wait(NULL);
			}	
		} else {
			filho = fork();
			if (filho == 0)
			{
				res[1] = lerLinha(n,M,N,mat,1);
				printf("r1 = %d\n",res[1]);	
				_exit(0);
			} else {
				res[0] = lerLinha(n,M,N,mat,0);
				printf("r0 = %d\n",res[0]);
				wait(NULL);
			}
			for (i=2;i<M;i++)
			{
				if (filho == 0)
				{	
			
				} else {

					filho = fork();
					if (filho == 0)
					{
						res[i] = lerLinha(n,M,N,mat,i);
						printf("r%d = %d\n",i,res[i]);
						_exit(0);
					} else {
						wait(NULL);
					}
				}
			}
		}
	}	
	for (i=0;i<M;i++)
	{
		printf("%d ",res[i]);
	}
	int resf = 0;
	if (resf == 0)
	{
		printf("Não Encontrado.\n");
	} else {
		printf("Encontrado %d vezes.\n",resf);
		/*for (i=0;i<M;i++)
		{
			if (res[i] != 0)
			{
				int h;
				int z[N];
				for (h=0;h<N;h++)
				{
					z[N] = mat[i][h];
				}
				z[N] = ordenar(&z[N],N);
				for (j=0;j<N;j++)
					printf("%d ",mat[i][j]);
			}
			printf("\n");
		}*/
	}

	
	return 0;
}
