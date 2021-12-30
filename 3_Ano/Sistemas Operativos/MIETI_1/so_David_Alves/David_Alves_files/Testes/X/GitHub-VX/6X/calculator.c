
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
 
int main(int argc, char *argv[]) {

    int num1 = atoi(argv[1]);
    char operator = argv[2][0];
    int num2 = atoi(argv[3]);
    int result;
    
    switch(operator) {
    case '+': result = num1 + num2;
        break;
    case '-': result = num1 - num2;
        break;
    case 'x': result = num1 * num2;
        break;
    case '/': result = num1 / num2;
        break;
    default : printf("Error in operation");
        break;
    }

    char resultado[50];

    sprintf(resultado, "%d\n", result);

    write(1, resultado, strlen(resultado));

    return 0;
}
