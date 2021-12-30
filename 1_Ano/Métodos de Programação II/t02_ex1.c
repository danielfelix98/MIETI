#include <stdio.h>

int nmax = 20;

/* função main() */
int main ( int argc , char **argv) { /* ponto de entrada */
    int a=0, b=1, c, n;
    nmax =25;
    printf ( "%4d: %d\n" ,1 ,a );
    printf ( "%4d: %d\n" ,2 ,b );
    for (n=3; n<nmax; n++) {
        c=a+b; a=b; b=c;
        printf ( "%3d: %d\n" ,n, c );
    }
    return 0; /* sucesso */
}
