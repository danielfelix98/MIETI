#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <time.h>
#include <string.h>

/*programa q conta linhas do prog em arg*/

int main(int argc, char const *argv[])
{
	int fd=open(argv[1],O_RDONLY);
	int linhas=0;
	int i;
	char c;
	while(i=read(fd,&c,1)>0){
		if(c=='\n') linhas++;
	}

	printf("%d\n",linhas);




	return 0;
}