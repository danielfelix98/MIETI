// EXERCICIO 3 DA AULA T06

#include <stdio.h>

int main() {
    int size;

    size = sizeof(char);          //  1   (S.O. 64-bits)
    printf("O tamanho do char e' %d bytes.\n",size);
    size = sizeof(short int);     //  2   (S.O. 64-bits)
    printf("O tamanho do short int e' %d bytes.\n",size);
    size = sizeof(int);           //  4   (S.O. 64-bits)
    printf("O tamanho do int e' %d bytes.\n",size);
    size = sizeof(long int);      //  8   (S.O. 64-bits)
    printf("O tamanho do long e' %d bytes.\n",size);
    size = sizeof(long long int); // 16   (S.O. 64-bits)
    printf("O tamanho do long long e' %d bytes.\n",size);
    size = sizeof(float);         //  4   (S.O. 64-bits)
    printf("O tamanho do float e' %d bytes.\n",size);
    size = sizeof(double);        //  8   (S.O. 64-bits)
    printf("O tamanho do double e' %d bytes.\n",size);

    return 0;
}
