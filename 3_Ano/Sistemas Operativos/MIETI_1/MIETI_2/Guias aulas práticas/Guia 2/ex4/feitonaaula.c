#include <unistd.h>
#include <stdlib.h>

int main()
{
	pid_t pid;	
	int i,status;
	char string[256]; //ver o snprintf
	for (i=0;i<10;i++)
	{
		pid = fork();
		if (pid == 0)
		{
			sprintf(string,"Eu sou %d, meu pai é %d\n",getpid(),getppid());
			write(1,string,strlen(string));
			_exit(i+1);
		} 
		sprintf(string,"meu pid %d, pid pai %d,pid processo pid %d\n",getpid(),getppid(),pid);	
		write(1,string,strlen(string));
	}
	for (i=0;i<10;i++)
	{
		pid = wait(&status);// no pid fica o valor do processo que morreu
		if(WIFEXITED(status))
		{
			sprintf(string, "%d %d\n",pid,WEXITSTATUS(status));
		}
	}
	return 0;
}
