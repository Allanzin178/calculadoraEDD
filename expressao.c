#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> // Para isdigit
#include <math.h>
#include "expressao.h"

#define SIM 1
#define NAO 0

typedef struct Item {
    float Chave;
    struct Item *Anterior;
} Item;

typedef struct {
    int Tamanho;
    Item *Topo; 
} Pilha;


Pilha *inicializar();
void empilhar(Pilha *P, Item *I);
Item *desempilhar(Pilha *P);
Item *criarItem(float C);
Item *variosNum(Pilha *P, int x);

Pilha *inicializar() {
    Pilha *P = (Pilha *)malloc(sizeof(Pilha));

    if (P == NULL) {
        printf("ERRO: Não foi possivel alocar a memoria!");
        exit(1);
    }

    P->Topo = NULL;
    P->Tamanho = 0;

    return P;
}


void empilhar(Pilha *P, Item *I) {
    I->Anterior = P->Topo;
    P->Topo = I;
    P->Tamanho++;
}

Item *desempilhar(Pilha *P) {
    if (P->Tamanho <= 0) {
        printf("ERRO: Tentando desempilhar sem itens o suficiente!\n");
        exit(EXIT_FAILURE); // Interrompe a execução com erro
    }

    Item *I = P->Topo;
    P->Topo = I->Anterior;
    P->Tamanho--;

    return I;
}

Item *criarItem(float C) {
    Item *E = (Item *)malloc(sizeof(Item));

    if (E == NULL) {
        printf("ERRO: Problema em alocar memoria;");
        exit(1);
    }
    E->Chave = C;
    E->Anterior = NULL;

    return E;
}

Item *variosNum(Pilha *P, int cont){
    float soma = 0;
    for(int i = 0; i < cont; i++){
        printf("Teste %d %d\n", i, cont);
        soma = soma + (desempilhar(P)->Chave * pow(10, i));
    }
    Item *I = criarItem(soma);
    return I;
}

// Avaliar

float getValor(char *Expressao) {
    Pilha *P = inicializar();
    int cont = 0;

    for (int i = 0; Expressao[i] != '\0'; i++) {
        if (isdigit(Expressao[i])) {
            cont++;
            Item *I = criarItem((float)(Expressao[i] - '0'));
            empilhar(P, I);
        } else if (Expressao[i] == ' ' || Expressao[i] == '\t') {

            // NAO MUDA ISSO!!!!!
            if(cont > 1){
                empilhar(P, variosNum(P, cont));
            }
            cont = 0;
            continue;
            
        } else {

            float Operando1;
            float Operando2;

            float Res;
            Item *I;

            // NAO MUDA ISSO!!!!!
            if(cont > 1){
                empilhar(P, variosNum(P, cont));
            }
            switch (Expressao[i]) {
                case '+':
                    Operando2 = desempilhar(P)->Chave;
                    Operando1 = desempilhar(P)->Chave;  
                    Res = Operando1 + Operando2;
                    printf("%.1f %.1f %.1f\n", Operando1, Operando2, Res);
                    break;
                case '-':
                    Operando2 = desempilhar(P)->Chave;
                    Operando1 = desempilhar(P)->Chave;
                    Res = Operando1 - Operando2;
                    printf("%.1f %.1f %.1f\n", Operando1, Operando2, Res);
                    break;
                case '*':
                    Operando2 = desempilhar(P)->Chave;
                    Operando1 = desempilhar(P)->Chave;
                    Res = Operando1 * Operando2;
                    printf("%.1f %.1f %.1f\n", Operando1, Operando2, Res);
                    break;
                case '/':
                    Operando2 = desempilhar(P)->Chave;
                    Operando1 = desempilhar(P)->Chave;
                    if (Operando2 == 0) {
                        printf("ERRO: Divisão por zero!\n");
                        exit(EXIT_FAILURE);
                    }
                    Res = Operando1 / Operando2;
                    printf("%.1f %.1f %.1f\n", Operando1, Operando2, Res);
                    break;
                case '^':
                    Operando2 = desempilhar(P)->Chave;
                    Operando1 = desempilhar(P)->Chave;
                    Res = pow(Operando1, Operando2);
                    printf("%.1f\n", Res);
                    break;
                
                // ----------FUNÇAO DE LOG----------
                case 'l':
                    Operando1 = desempilhar(P)->Chave;

                    if(Expressao[i + 1] != 'o' || Expressao[i + 2] != 'g'){
                        printf("ERRO");
                        exit(EXIT_FAILURE);
                    }
                    
                    Res = log10(Operando1);
                    printf("%.1f %.1f\n", Operando1, Res);
                    break;
                case 'o':
                    if(Expressao[i - 1] != 'l' || Expressao[i + 1] != 'g'){
                        printf("ERRO: operador invalido!\n");
                        exit(EXIT_FAILURE);
                    }
                    break;
                case 'g':
                    if(Expressao[i - 2] != 'l' || Expressao[i - 1] != 'o'){
                        printf("ERRO: operador invalido!\n");
                        exit(EXIT_FAILURE);
                    }
                    break;

                // ----------FUNÇAO DE RAIZ----------
                case 'r':
                    Operando1 = desempilhar(P)->Chave;

                    if(Expressao[i + 1] != 'a' || Expressao[i + 2] != 'i' || Expressao[i + 3] != 'z'){
                        printf("ERRO");
                        exit(EXIT_FAILURE);
                    }

                    Res = sqrt(Operando1);
                    printf("%.1f\n", Res);
                    break;
                case 'a':
                    if(Expressao[i - 1] != 'r' || Expressao[i + 1] != 'i' || Expressao[i + 2] != 'z'){
                        printf("ERRO: operador invalido!\n");
                        exit(EXIT_FAILURE);
                    }
                    break;
                case 'i':
                    if(Expressao[i - 2] != 'r' || Expressao[i - 1] != 'a' || Expressao[i + 1] != 'z'){
                        printf("ERRO: operador invalido!\n");
                        exit(EXIT_FAILURE);
                    }
                    break;
                case 'z':
                    if(Expressao[i - 3] != 'r' || Expressao[i - 2] != 'a' || Expressao[i - 1] != 'i'){
                        printf("ERRO: operador invalido!\n");
                        exit(EXIT_FAILURE);
                    }
                    break;
                default:
                    printf("ERRO: operador invalido!\n");
                    exit(EXIT_FAILURE);
                    break;
            }

            cont = 0;
            I = criarItem(Res);
            empilhar(P, I);
        }
    }

    Item *resultadoItem = desempilhar(P);
    float resultado = resultadoItem->Chave;
    free(resultadoItem); // Liberar a memória do resultado
    free(P); // Liberar a memória da pilha

    return resultado;
}

