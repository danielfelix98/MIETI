#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
int main(int argc, char const *argv[])
{
	for(int i=1;i<argc;i++){
		printf("%s\n",argv[i]);

	}
	return 0;
}