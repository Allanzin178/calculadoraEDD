#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "expressao.h"

#define numTestes 9

int main(void) {

    Expressao E[numTestes];
    system("cls");
    
    char *Expressao = "3 4 + 5 * ";
    char *Expressao1 = "7 2 * 4 +";
    char *Expressao2 = "8 5 2 4 + * +";
    char *Expressao3 = "6 2 / 3 + 4 * ";
    char *Expressao4 = "9 5 2 8 * 4 + * +";
    char *Expressao5 = "2 3 + log 5 / ";
    char *Expressao6 = "10 log 3 ^ 2 +";
    char *Expressao7 = "45 60 + 30 cos *";
    char *Expressao8 = "0.5 45 sen 2 ^ +";
    // char *Expressao9 = "450 tg";
    // char *Expressao10 = "64 raiz";

    strcpy(E[0].posFixa, Expressao);
    strcpy(E[1].posFixa, Expressao1);
    strcpy(E[2].posFixa, Expressao2);
    strcpy(E[3].posFixa, Expressao3);
    strcpy(E[4].posFixa, Expressao4);
    strcpy(E[5].posFixa, Expressao5);
    strcpy(E[6].posFixa, Expressao6);
    strcpy(E[7].posFixa, Expressao7);
    strcpy(E[8].posFixa, Expressao8);
    // strcpy(E[9].posFixa, Expressao9);
    // strcpy(E[10].posFixa, Expressao10);

    for(int i = 0; i < numTestes; i++){
        strcpy(E[i].inFixa, getFormaInFixa(E[i].posFixa));

        printf("\n\t TESTE %d: \n", i + 1);

        E[i].Valor = getValor(E[i].posFixa);
        printf("Resultado: %.2f\n", E[i].Valor);
        printf("Pos-fixa: %s\n", E[i].posFixa);
        printf("Infixa: %s\n", E[i].inFixa);
    }
    
    
    

    return 0;
}