#include<unistd.h>
#include<fcntl.h>
#include<sys/wait.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"api.h"
#include<sys/stat.h>
#include<sys/types.h>
#include<signal.h>

#define BUFSZS	16
#define BUFSZM	64
#define BUFSZL	512
#define MAXTASK	1024

Task tasklist[MAXTASK];
int ntask = 0;

void sighandler(int signum)
{
	int i = 0;
	if(signum == SIGCHLD)
	{
		int pid=-1, stat=-1;
		pid = waitpid(-1,&stat,0);
		
		if(stat!=2)
		{
			for(i=0; i!=ntask; i++)
			{
				if(tasklist[i].pid == pid)
				{
					strcpy(tasklist[i].status,"terminated");
				}
			}
		}
		else
		{
			for(i=0; i!=ntask; i++)
			{
				if(tasklist[i].pid == pid)
				{
					strcpy(tasklist[i].status,"cancelled");
				}
			}
		}
	
	}

	if(signum==SIGALRM)
	{
		//do nothing
	}
	
	if(signum==SIGTERM)
	{
		_exit(2);
	}
	
	if(signum==SIGHUP)
	{
		for(i=0; i!=ntask; i++)
		{	
			char aux[BUFSZS];
			strcpy(aux,tasklist[i].status);

			if((strncmp(aux,"scheduled",strlen(aux)))==0)
			{
				kill(tasklist[i].pid,SIGINT);
			}
		}
	}
	
}


int main()
{	
	//main server
	char * fifopath = malloc(BUFSZS);
	char * fifopath2 = malloc(BUFSZS);
	fifopath = "/tmp/fifo";	
	fifopath2 = "/tmp/fifo2";

	int fifo = mkfifo(fifopath, 0600);
        if(fifo==-1)
        {
        	perror("error creating input fifo...");
		unlink(fifopath);
        	return -1;
        }
	
	int fifo2 = mkfifo(fifopath2,0600);
	if(fifo2==-1)
	{
		perror("error creating output fifo");
		unlink(fifopath2);
		return -1;
	}
	
	if(!fork())//secondary server
	{
		int fifod = 0;
		int fifod2 = 0;
		int cmid = -1;
		int npipes = 0;
		fifod = open(fifopath,O_RDONLY);
		fifod2 = open(fifopath2,O_WRONLY);
		char * frompipe = malloc(BUFSZM);
		char cmnd[BUFSZS], arg1[BUFSZS];
		char ptexecs[12][64];
		//char ptexecs1[12][64];
		char * ptr_ptexecs1 [3][5];
		int nbytes = 0;
		
		//trap signals
		signal(SIGCHLD,sighandler);
		signal(SIGHUP,sighandler);
		do
		{
			nbytes=read(fifod,frompipe,BUFSZM);
			//frompipe[nbytes]='\0';
			cmid = getcmd(frompipe);
			
			switch(cmid)
			{
				//agendar
				case 1: {
						//task fields: name, status, date, id, pid
						int fr = -1;
						sscanf(frompipe,"%s %s %s %s %s %s %s %s %s %s %s %s %s %s",cmnd,arg1,ptexecs[0],ptexecs[1],ptexecs[2], ptexecs[3], ptexecs[4], ptexecs[5], ptexecs[6], ptexecs[7], ptexecs[8], ptexecs[9], ptexecs[10], ptexecs[11]);
	
						char cmds[BUFSZM];
						sprintf(cmds, "%s %s %s %s %s %s %s %s %s %s %s %s",ptexecs[0], ptexecs[1], ptexecs[2], ptexecs[3], ptexecs[4], ptexecs[5], ptexecs[6], ptexecs[7], ptexecs[8],ptexecs[9],ptexecs[10],ptexecs[11]);
						Task currTask;
						strcpy(currTask.name,ptexecs[0]);
						strcpy(currTask.status,"scheduled");
						strcpy(currTask.date,arg1);
						currTask.id = ntask;
						tasklist[ntask]=currTask;
						//npipes = argumentparser(ptexecs1,cmds,ptr_ptexecs1);
						
						fr = fork();
						dup2(fifod2,STDOUT_FILENO);
						
						if(fr==0)//processo que executa tarefa pedida - pipe[0] é read end, pipe[1] é write end
						{
							signal(SIGINT,sighandler);
							int writefd[2];
							signal(SIGALRM,sighandler);
							alarm(atoi(arg1));		
							pause();	
							
							npipes = argumentparser(ptexecs,cmds,ptr_ptexecs1);
							npipes--;

							if(npipes == 0)
							{
								execvp(ptr_ptexecs1[0][0],ptr_ptexecs1[0]);
								perror("erro exec...");
								_exit(-1);	
							}
							/*pipe(writefd);
							setwrite(writefd);

							if(!fork())
							{
								execlp(ptexecs[0],ptexecs[0],NULL);
								perror(ptexecs[0]);
								_exit(-1);
							copypipe(writefd,readfd);
							
							for(i=1; i < nexecs-1; i++);
							{
								pipe(readfd);
								printf("PROGRAMA A EXECUTAR: %s",ptexecs[i]);	
								forkexec(writefd,readfd,ptexecs[i]);
								closepipe(readfd);
								copypipe(writefd,readfd);
							}

							forkexec(readfd,NULL,ptexecs[nexecs-1]);
							closepipe(readfd);
							}*/

							npipes = 0;
							pipe(writefd);
							if(!fork())
							{
								close(writefd[0]);
								dup2(writefd[1],STDOUT_FILENO);
								execvp(ptr_ptexecs1[0][0],ptr_ptexecs1[0]);
								perror("erro exec...");
								return -1;
							}
							else
							{
								close(writefd[1]);
								dup2(writefd[0],STDIN_FILENO);
								wait(NULL);
								execvp(ptr_ptexecs1[1][0],ptr_ptexecs1[1]);
								perror("erro exec...");
								return -1;
							}

						}
						else
						{
							tasklist[ntask].pid=fr;
							ntask++;
						}
						break;
					}	
				//listar
				case 2: {
						sscanf(frompipe,"%s %s",cmnd,arg1);
						int i = 0, j=-1;
						j=listopt(arg1);

						if(ntask==0)
						{
							printf("\n## no tasks scheduled or completed ##\n");
						}
						else
						{
							for(i=0; i!=ntask; i++)
							{
								liststatus(j,tasklist[i],fifod2);
							}
						}
						break;
					}

				//consultar
				case 3: {
						sscanf(frompipe,"%s %s",cmnd,arg1);
						int i = 0, j=-1;
						
						j=atoi(arg1);

						if(ntask==0)
						{
							printf("\n## no tasks scheduled or completed ##\n");
						}
						else
						{
							for(i=0; i!=ntask; i++)
							{
								listid(j,tasklist[i],fifod2);
							}
						}
						
						break;
					}
				//cancelar
				case 4: {
						sscanf(frompipe,"%s %s",cmnd,arg1);
						int i = 0;

						for(i=0; i!=ntask; i++)
						{
							if(tasklist[i].id==(atoi(arg1)))
							{
								kill(tasklist[i].pid,SIGTERM);
							}
						}
						break;
					}
				default:{ 
					
						printf("Arg inválido...\n");
						break;
					}
			}
			
		}while(strncmp(frompipe,"exit",(nbytes+1))!=0);
		free(frompipe);
		_exit(0);
		
	}	
	
	wait(NULL); //main server waits for secondary server to exit
	unlink(fifopath);
	unlink(fifopath2);
	return 0;
	
}
