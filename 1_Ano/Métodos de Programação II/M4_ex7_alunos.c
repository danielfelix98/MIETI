#include <stdio.h>

/* ******************* MODULO 4: EXERCICIO 7 ***************************
Escrever um inteiro (int) em memória (por exemplo, 3F2E1D0C em hex).
Ler os 4 bytes, um a um, da memória onde se escreveu o inteiro anterior
e tirar conclusões sobre o tipo de ordenação usada para armazenar
os bytes dum inteiro em memória.
************************************************************************ */
int main() {

    int            iVal = 0x3F2E1D0C;
    unsigned char *byte;

    byte = (unsigned char *) &iVal;

    printf("INTEIRO             = %x\n",iVal);
    printf("ENDERECO DO INTEIRO = %p\n\n",&iVal);

    printf(" |    |\n");
    printf(" | %02x | <- %p\n", *(byte+3), byte+3); // MSByte
    printf(" | %02x | <- %p\n", *(byte+2), byte+2);
    printf(" | %02x | <- %p\n", *(byte+1), byte+1);
    printf(" | %02x | <- %p\n", *(byte+0), byte  ); // LSByte
    printf(" |    |\n");

    return 0;
}
