#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>


int main(int argc, char const *argv[])
{ 
	execlp("ls","ls","-l",NULL);



	return 0;
}