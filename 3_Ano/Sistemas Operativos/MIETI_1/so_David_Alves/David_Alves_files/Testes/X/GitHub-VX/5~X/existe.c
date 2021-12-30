#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <time.h>
#include <string.h>


ssize_t readLine(int fd, char* buffer, long maxBytes) {

    long bytesRead = 0;
    ssize_t i;
    char c;

    do {

        i = read(fd, &c, 1);

        if (i > 0) {
            buffer[bytesRead] = c;
            bytesRead++;

        }

    } while (i > 0 && bytesRead < maxBytes && c != '\n');

    buffer[bytesRead] = '\0';

    // Devolver o numero de bytes lidos
    return bytesRead;
}


int main() {

    char array[] = "bcdefga\n";

    char buffer[500];

    int bytesRead = readLine(0, buffer, 1000);

    char array1[] = "Não é igual\n";
    char array2[] = "É igual\n";

    if ((strcmp(buffer,array)) != 0) {
        write(1, array1, strlen(array1));
        return bytesRead;
    } else {
        write(1, array2, strlen(array2));
    }

    return bytesRead;
}

