#include <stdio.h>
#include <stdarg.h>

// EXEMPLO DE UMA FUNCAO VARIADICA
//
// Calcula a media de um conjunto de valores 'double',
// com cardinalidade variavel, passados como argumentos.
//
// count -> numero de valores a usar no calculo da media.
//
double media(int count, ...) {

    va_list  ap;
    int      j;
    double   total = 0.0;

    // o segundo argumento de va_start() e’ o nome do ultimo argumento fixo
    va_start(ap, count);

    for(j=0; j<count; j++) {
        // o segundo argumento de va_arg() indica o tipo dos argumentos.
        // va_arg() le um argumento, faz o cast para 'double' e avanca
        //    'ap' para o proximo argumento.
        total += (double)va_arg(ap, double);
    }
    va_end(ap);

    return total/count;
}

int main() {

    double med;

    // faz a media de 4 valores {4.5, 7.0 , 8.5, 1.0}
    med = media(4, 4.5, 7.0 , 8.5, 1.0);
    printf("A MEDIA E' %g\n", med);

    // faz a media de 5 valores {4.5, 7.0 , 8.5, 1.0, 30.4}
    med = media(5, 4.5, 7.0 , 8.5, 1.0, 30.4);
    printf("A MEDIA E' %g\n", med);

    return 0;
}
