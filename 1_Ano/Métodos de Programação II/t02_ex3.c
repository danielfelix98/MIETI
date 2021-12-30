#include <stdio.h>
#include <stdarg.h>

// EXEMPLO DE UMA FUNÇÃO VARIÁDICA
//
// Impementa uma versão simplificada de printf().
//
// fmt -> string de formatação (d-inteiro, c-char, g-double)
//
void simple_printf(const char *fmt, ...) {

    va_list args;

    va_start(args, fmt);

    while (*fmt != '\0') { // percorre string 'fmt'; o caratere na
                           // posição 'n' define o tipo do argumento 'n+1'

        if (*fmt == 'd') {        // argumento do tipo INT
            int i = (int)va_arg(args, int);
            printf("%d ", i);

        } else if (*fmt == 'c') { // argumento do tipo CHAR (lido como INT)
            char c = (char)va_arg(args, int);
            printf("%c ", c);

        } else if (*fmt == 'g') { // argumento do tipo DOUBLE
            double g = (double)va_arg(args, double);
            printf("%lf ", g);
        }
        ++fmt;
    }
    printf("\n");
    va_end(args);
}

int main(void) {
    // "dcgg" -> cada caratere indica o tipo dum argumento desconhecido
    simple_printf("dcgg", 3, 'a', 1.999, 42.5);

    return 0;
}
