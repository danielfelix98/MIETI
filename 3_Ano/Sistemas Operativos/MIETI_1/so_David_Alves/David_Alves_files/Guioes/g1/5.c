#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int readln(int filedes, void *buf, int nbyte)
{
	char * buf2 = (char*)buf;
	int i = 0;
	int j = 0;
 
	while((j=read(filedes,buf2,nbyte))!=-1)
	{
		if(*buf2 == '\n')
		{
			return i-1;
		}
		else
		{
			write(1,buf2,j);
			i++;
		}
	}
	return -1;
}

