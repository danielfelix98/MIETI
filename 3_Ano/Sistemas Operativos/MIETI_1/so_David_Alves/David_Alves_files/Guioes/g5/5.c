#include <unistd.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <fcntl.h>    /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <sys/types.h>
#include <string.h>
//grep -v ˆ# /etc/passwd | cut -f7 -d: | uniq | wc -l

int main(){
    pid_t pid;
    int pd1[2];
    int pd2[2];
    int pd3[2];
    pipe(pd3);
    pid = fork();
     
    if (pid==0){
        pipe(pd2);
        pid=fork();

        if(pid==0){
            pipe(pd1);
            pid=fork();
            
            if(pid==0){
                dup2(pd1[1],1);
                close(pd1[0]);
                close(pd1[1]);
                execlp("grep","grep","-v","ˆ#","password.txt",NULL);
                perror("grep");
                _exit(1);
            } 
            else {
                dup2(pd1[0],0);
                dup2(pd2[1],1);
                close(pd1[0]);
                close(pd1[1]);
                close(pd2[0]);
                close(pd2[1]);
                execlp("cut","cut","-f7","-d:",NULL);
                perror("cut");
                _exit(1);
            }
        }
        else {
            dup2(pd2[0],0);
            dup2(pd3[1],1);
            close(pd2[0]);
            close(pd2[1]);
            close(pd3[0]);
            close(pd3[1]);
            execlp("uniq","uniq",NULL);
            perror("uniq");
            _exit(1);
        }
    } else {
        dup2(pd3[0],0);
        close(pd3[0]);
        close(pd3[1]);
        execlp("wc","wc","-l",NULL);
        perror("wc");
        _exit(1);
    }
    return 0;
}