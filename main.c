#include <stdio.h>
#include <stdlib.h>
#include "expressao.h"

int main(void) {
    char *Expressao = "2 4 + 5 *";
    float resultado = getValor(Expressao);
    printf("Resultado 1: %f \n", resultado);

    char *Expressao1 = "2 ";
    resultado = getValor(Expressao1);
    printf("Resultado 2: %f \n", resultado);

    return 0;
}