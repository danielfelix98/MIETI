#include <stdio.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/wait.h>
#include <stdio.h>
#include <time.h>
#include <sys/wait.h>
#define X 3
#define Y 50
//Este código faz com seja exibido a linha por ordem decrescente
void geraMat(int mat[X][Y]){
  
    int i, j;
    srand(time(NULL));
    for (i = 0; i < X; i++)
        for (j = 0; j < Y; j++)
             mat[i][j] = random() % 300;
}


void printM (int M[X][Y]){
     int i, j;
     for(i = 0; i < X; i++){
         for(j=0; j < Y; j++)
            printf("|[%d]", M[i][j]);
         printf("|\n");
     }
}


int main(int argc, char * argv[])
{
  int i,s;
  int k[X][Y];
  geraMat(k);
  printM(k);
  int status;

  int n = atoi(argv[1]);

  for(i=0; i<X; i++)
  {
    s=fork();
    if(s==-1)
    {
      perror("erro a criar processo");
      return -1;
    }
    if(s==0) //filho
    {
      int aux=0;
      for(aux=0; aux<=Y; aux++)
      {
        if(k[i][aux]==n)
        {
          printf("Sou o processo com pid=%d e encontrei um na linha %d e coluna %d\n",getpid(),(i+1),aux+1);
        }
        
      }
      _exit(0);

      
    }
  }

  for(i=0; i<Y; i++) //pai
  {
    wait(&status);
    

  }
  for(i=0; i<X; i++) //pai
  {
    wait(&status);

  }
  printf("Terminaram todos\n");
  return 0;
} 
