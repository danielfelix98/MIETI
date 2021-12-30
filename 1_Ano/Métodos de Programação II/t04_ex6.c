#include <stdio.h>
#include <stdlib.h>

// Tipo enumerado que funcionará como indice do array
// de apontadores para funções
enum TIPO_OP{SOMA=0, SUB=1, MULT=2, DIV=3};

typedef enum TIPO_OP Tipo;

// Tipo correspondente a um apontador para uma função
// que recebe 2 floats como argumento e devolve um float
typedef float (*fpCalcula)(float,float);

// Funções para as 4 operações suportadas (+,-,x,/).
// Uma destas funções será selecionada durante a execução a
// partir do array de apontadores para funções.
//
float Somar(float a, float b) {
    return a+b;
}

float Subtrair(float a, float b) {
    return a-b;
}

float Multiplicar(float a, float b) {
    return a*b;
}

float Dividir(float a, float b) {
    if (b!=0.0)
        return a/b;
    else
        return 0.0;
}

// Função que efetua 4 tipos de operação utilizando
// um array de apontadores para funções.
//
//  a, b -> operandos
//  op   -> tipo da operação a efetuar
//  fp   -> array de apontadores para as 4 funções.
//
float calcula(float a, float b, Tipo op, fpCalcula fp[]) {
   float resultado;
   resultado = (fp[op])(a,b); // chamar a função correspondente ao 'op'
   return resultado;
}

// ------------------------------------------------------------------
int main(int argc, char *argv[]) { // calcula a op b

    float       a, b, res;
    Tipo        op;
    fpCalcula   funcP[4]   = {Somar,Subtrair,Multiplicar,Dividir};
    char        simboloOp[4] = {'+','-','x','/'};
    char        opAux;

    a  = (float)atof(argv[1]);
    b  = (float)atof(argv[3]);
    opAux = argv[2][0]; // SOMA, SUB, MULT, DIV
    switch(opAux){
        case '+':
            op = SOMA;
            break;
        case '-':
            op = SUB;
            break;
        case 'x':
            op = MULT;
            break;
        case '/':
            op = DIV;
            break;
    }
    printf("Calculadora com array de apontadores para funcao\n");
    res = calcula(a, b, op, funcP);
    printf("--> %f %c %f = %f\n",a,simboloOp[op],b,res); // mostrar o resultado

    return 0;
}
