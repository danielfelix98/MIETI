#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int readln(int filedes, void *buf, int nbyte)
{
	char * buf2 = (char*)buf;//buffer
	int i = 0;///contadores
	int j = 0;
    
	while((j=read(filedes,buf2,nbyte))!=-1)//enquanto houver algo para ler lê
	{
		if(*buf2 == '\n')//se clicar enter
		{
            
			return i-1;
            
		}
		else //se
		{           
          	i++;//incrementa numero de linhas
            
		}
    
	}

	return -1;
}

int main(int argc, char **argv) {
char buf[1024];
int nbyte=1;
//int i=readln(0,buf,nbyte);
if (argc < 2){
int i;

//char string[1024];

int a=0;  
char buf3[1024];

while(read(0,buf,1024)){
a++;
sprintf(buf3,"\t%d",a);
write(1,buf3,strlen(buf3) );
write(1,"             ",1);
write(1,buf,strlen(buf));
}
}
else{

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
}	
	return 0;
}


/*
for (int i = 1; i < argc; i++){
int filed=open( argv[i], O_RDONLY );

int a=0;  
char buf3[1024];

while(read(filed,buf,100)){//falha
a++;
sprintf(buf3,"\t\n%d",a);
write(1,buf3,strlen(buf3) );
write(1,"             ",1);
write(1,buf,strlen(buf));

}
}}
//close(filed);
	
	
	return 0;

}
*/
