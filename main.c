#include <stdio.h>
#include <stdlib.h>
#include "expressao.h"

int main(void) {
    char *Expressao = "3 4 + 5 *";
    float resultado = getValor(Expressao);
    printf("Resultado 1: %f \n", resultado);

    char *Expressao1 = "7 2 * 4 + ";
    resultado = getValor(Expressao1);
    printf("Resultado 2: %f \n", resultado);

    char *Expressao2 = "8 5 2 4 + * +";
    resultado = getValor(Expressao2);
    printf("Resultado 2: %f \n", resultado);

    char *Expressao3 = "6 2 / 3 + 4 *";
    resultado = getValor(Expressao3);
    printf("Resultado 2: %f \n", resultado);

    char *Expressao4 = "9 5 2 8 * 4 + * +";
    resultado = getValor(Expressao4);
    printf("Resultado 2: %f \n", resultado);

    char *Expressao5 = "2 3 + log 5 / ";
    resultado = getValor(Expressao5);
    printf("Resultado 2: %f \n", resultado);

    char *Expressao6 = "10 log 3 ^ 2 +";
    resultado = getValor(Expressao6);
    printf("Resultado 2: %f \n", resultado);

    char *Expressao7 = "45 60 + 30 cos *";
    resultado = getValor(Expressao7);
    printf("Resultado 2: %f \n", resultado);

    return 0;
}