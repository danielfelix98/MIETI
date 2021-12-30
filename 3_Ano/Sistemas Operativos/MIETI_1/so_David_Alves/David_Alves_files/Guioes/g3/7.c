#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

ssize_t readln(int fildes, void *buf, size_t nbyte)
{
	int r=0, n=0;
	char * c = buf;
	r = read(fildes,&c[n],1);

	while ( n < (nbyte-1) && r> 0 && c[n] != EOF && c[n] != '\n'&& c[n] != '\0') {
		n++;
		r = read(fildes, &c[n],1);
	}
	c[n+1] = '\0';
	return n+1;
}

int main()
{
	pid_t p ;
	int running = 1;
	char buffer[1024];
	char * temp;
	char * arg[16];
	int i;
		while(running) {
			if(readln(0,buffer,1024)==0) {
				running=0;
			} else {
				i = 0;
				arg[i] = strtok(buffer," \n");
				i++;
		
				for(; arg[i-1]!=NULL; i++) {
					arg[i]=strtok(NULL," \n");
				}

				if(!strcmp(arg[0] ,"exit")) {
					running=0;
				} else {
					if((p = fork())== 0) {
						execvp(arg[0],arg);
					} else {
						if(strcmp(arg[i-2],"&")) {
							wait(NULL);
						}
					}
				}
			}
		}
	return 0;
}