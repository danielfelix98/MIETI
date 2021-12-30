#include <stdio.h>

//-------------------------------------------------------------------------------------
// Exemplo que mostra como substituir uma declaração switch por um apontador para função
//
// Problema: executar uma de entre quatro operações aritméticas: +,-,x,/.

// Função para cada uma das 4 operações aritméticas
// Uma destas funções será selecionada durante a execução

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

// Solução com uma declaração switch.
//
// 'op' especifica qual a operação a executar com 'a'  e 'b'.
//
float Calcula_Switch(float a, float b, char op) {

    float resultado;

    // executar a operação
    switch(op) {
        case '+':
            resultado = Somar(a,b);
            break;
         case '-':
            resultado = Subtrair(a,b);
            break;
         case 'x':
            resultado = Multiplicar(a,b);
            break;
         case '/':
            resultado = Dividir(a,b);
            break;
    }
    return resultado;

}


// Solução com um apontador para função.
//
// 'pt2Func' é um apontador para função e aponta para uma
// função que possui dois argumentos do tipo float e devolve um float.
// Este apontador "especifica" qual a operação a executar.
//
float Calcula_ApontadorFuncao(float a, float b, float (*pt2Func)(float, float)) {

    float resultado = pt2Func(a, b);  // executar o calculo usando o apontador para função

    return resultado;
}


int main() {
    float a, b, res;
    char  op;
    a  = 2.5;
    b  = 5.3;
    op = '-';

    printf("Executar a calculadora com switch: ");
    res = Calcula_Switch(a, b, op);
    printf("%f %c %f = %f\n", a,op,b,res); // mostrar o resultado


    printf("Executar a calculadora com apontador para funcao: ");
    // res = Calcula_ApontadorFuncao(a, b, Somar);
    res = Calcula_ApontadorFuncao(a, b, Subtrair);
    // res = Calcula_ApontadorFuncao(a, b, Multiplicar);
    // res = Calcula_ApontadorFuncao(a, b, Dividir);
    printf("%f %c %f = %f\n", a,op,b,res); // mostrar o resultado

    return 0;
   }
