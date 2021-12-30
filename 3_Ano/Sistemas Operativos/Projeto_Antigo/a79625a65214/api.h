#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

struct task{
	char name[32];
	char status[32];
	char date[32];
	int id;
	int pid;
};

typedef struct task Task;

//le linhas de ficheiro, e retorna bytes lidos
int readln(int filedes, void *buf, int nbyte)
{
	char * buf2 = (char*)buf;
	int i = 0;
	int j = 0;
 	
	while((j=read(filedes,buf2,nbyte))>0)
	{
		if(*buf2 == '\n')
		{
			return i-1;
		}
		else
		{
			write(STDOUT_FILENO,buf2,j);
			i++;
		}
	}
	return j;
}

int getcmd(char *s)
{	
	char aux[16];
	sscanf(s,"%s",aux);
	
	if((strncmp(aux,"agendar",strlen(aux)))==0)
	{
		return 1; //comando tipo agendar
	}
	
	else if((strncmp(aux,"listar",strlen(aux)))==0)
	{
		return 2;// comando tipo listar
	}
	
	else if((strncmp(aux,"consultar",strlen(aux)))==0)
        {
                return 3;// comando tipo consultar
        }
	
	else if((strncmp(aux,"cancelar",strlen(aux)))==0)
        {
                return 4;// comando tipo listar
        }

	return -1;
}

void printtask(Task t, int fd)
{	
	char aux1[32];
	snprintf(aux1,256,"%s %s %s %d %d\n",t.name,t.date,t.status,t.id,t.pid);
	write(fd,aux1,strlen(aux1));
}

int listopt(char * s)
{
	char aux[16];
	sscanf(s,"%s",aux);
	
	if((strncmp(aux,"agendados",strlen(aux)))==0)
	{
		return 1;//listar agendados
	}
	
	else if((strncmp(aux,"cancelados",strlen(aux)))==0)
	{
		return 2;//listar cancelados
	}
		
	else if((strncmp(aux,"em-execucao",strlen(aux)))==0)
	{
		return 3;//listar em-execucao
	}
	
	else if((strncmp(aux,"executados",strlen(aux)))==0)
	{
		return 4;//listar executados
	}
		
	else if((strncmp(aux,"todos",strlen(aux)))==0)
	{
		return 5;//listar todos
	}

	return -1;
}

void liststatus(int i, Task t, int fd)
{
	int listed = 0;

	switch(i)
	{
		case 1 :{
				if((strncmp(t.status,"scheduled",strlen(t.status)))==0)
				{
					listed++;
					printtask(t,fd);//lista agendados
				}
				break;
			}
		
		case 2 :{
				if((strncmp(t.status,"cancelled",strlen(t.status)))==0)
				{
					listed++;
					printtask(t,fd);//lista cancelados
				}
				break;
			}

		case 3 :{
				if((strncmp(t.status,"executing",strlen(t.status)))==0)
				{
					listed++;
					printtask(t,fd);//lista a executar
				}
				break;
			}	
		case 4 :{
				if((strncmp(t.status,"terminated",strlen(t.status)))==0)
				{
					listed++;
					printtask(t,fd);//lista terminados
				}
				break;
			}
		
		case 5 :{	
				listed++;
				printtask(t,fd);//lista todos
				break;
			}
		
		default:{
				printf("Bad request\n");
				break;	
			}

		
	}
}

int listid(int i, Task t, int fd)
{
	int listed = 0;
	if(t.id == i)
	{
		printtask(t,fd);
	}

	return listed;
}



int exectask(char * s, int nexecs)
{
	int i = 0;
	char args[4][64];
	char * ptr_args[5];
	
	sscanf(s,"%s %s %s %s",args[0],args[1],args[2],args[3]);
	
	for(i=0; i<nexecs; i++)
	{
		ptr_args[i] = args[i];
	}
	ptr_args[nexecs] = NULL;
	execvp(args[0], ptr_args);
	perror("erro exec...");
	return -1;
}

int argumentparser(char buffer[12][64], char * s, char * ptr_args[3][5])
{
        int pipecount=0, i=0, nargs=0, cargs=0;
        nargs = sscanf(s,"%s %s %s %s %s %s %s %s %s %s %s %s",buffer[0],buffer[1],buffer[2],buffer[3],buffer[4],buffer[5],buffer[6],buffer[7],buffer[8],buffer[9],buffer[10],buffer[11]);

        for(i=0; i< nargs; i++)
        {
                if(strcmp(buffer[i],"|")==0)
                {
                        ptr_args[pipecount][cargs]=NULL;
                        cargs = 0;
                        pipecount++;
                }
                else
                {
                        ptr_args[pipecount][cargs] = buffer[i];
                        cargs++;
                }
        }
        /*if(pipecount == 0)
                ptr_args[pipecount][cargs]=NULL;*/

        return pipecount;
}

void setwrite(int fd[2])
{
	close(fd[0]);
	dup2(fd[1],STDOUT_FILENO);
}

void setread(int fd[2])
{
	close(fd[1]);
	dup2(fd[0],STDIN_FILENO);
}

void copypipe(int src[2], int dst[2])
{
	src[0] = dst[0];
	src[1] = dst[1];
}

void closepipe(int fd[2])
{
	close(fd[0]);
	close(fd[1]);
}

/*void forkexec(int readfromprevious[2], int writetonext[2], char * s)
{
	if(!fork())
	{
		if(readfromprevious)
			setread(readfromprevious);
		if(writetonext)
			setwrite(writetonext);

		execl(s,s,NULL);	
		perror(s);
		_exit(-1);
	}
	else
	{
		if(readfromprevious)
			closepipe(readfromprevious);
		wait(NULL);
	}
}*/
