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
			write(STDOUT_FILENO,buf2,j);
			i++;
		}
	}
	return -1;
}

int main(int argc, char * argv[])
{	
	char * buf = (char*)malloc(sizeof(char));
	int n=1;
	int aux=0;
	int fd = 0;
	fd = open(argv[1],O_RDONLY);
	
	do
	{
		printf("%d ",n);
		aux=readln(fd,buf,1);
		printf("\n");
		n++;
	}while(aux !=-1);
	free(buf);
	close(fd);
	return 0;
}

/*
int main(int argc, char **argv) {
	if (argc < 2)
		return -1;

	int fileID;
	char buff[32];
	int count;
	int lineCount = 0;
	char lineNum[8], lastChar = '\n';
	int x, y;
	char *charPtr;
	for(x=1; x<argc; x++) {
		fileID = open(argv[x], O_RDONLY);
		
		count = 32;
		
		while(count == 32) {
			count = read(fileID, buff, 32);
			
			charPtr = buff;
			for(y=0; y<count; y++) {
				if (lastChar == '\n') {
					lineCount++;
					sprintf(lineNum, "\t%d  ", lineCount);
					write(1, lineNum, strlen(lineNum));
				}
				
				lastChar = *charPtr;
				write(1, charPtr++, 1);
			}
		}
		
		close(fileID);
	}
	
	return 0;
}


