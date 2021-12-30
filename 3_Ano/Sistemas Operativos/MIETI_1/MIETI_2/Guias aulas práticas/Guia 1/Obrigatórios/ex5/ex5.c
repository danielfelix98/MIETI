#include<unistd.h>

ssize_t readln(int fildes, void *buf, ssize_t nbyte)
{
	char buffer;
	int i = 0;
	while((read(fildes, buf+i, sizeof(char))) != 0)
	{			
		if(*(char*)(buf+i) == '\n'){
			i++;	
			break;
		}
		i++;
	}	
	return i;
}

int main()
{
	char c[100] = "";
	ssize_t out = readln(0,&c,100);
	write(1,&c,out);
	return 0;
}
