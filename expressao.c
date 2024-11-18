#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> // Para isdigit
#include <math.h>
#include "expressao.h"

#define SIM 1
#define NAO 0
#define RAIZ 3
#define COS 2
#define TG 1
#define SEN 2
#define LOG 2

typedef struct Item
{
    float Chave;
    struct Item *Anterior;
} Item;

typedef struct
{
    int Tamanho;
    Item *Topo;
} Pilha;

Pilha *inicializar();
void empilhar(Pilha *P, Item *I);
Item *desempilhar(Pilha *P);
Item *criarItem(float C);
Item *variosNum(Pilha *P, int cont, int contVirg);

Pilha *inicializar()
{
    Pilha *P = (Pilha *)malloc(sizeof(Pilha));

    if (P == NULL)
    {
        printf("ERRO: Não foi possivel alocar a memoria!");
        exit(1);
    }

    P->Topo = NULL;
    P->Tamanho = 0;

    return P;
}

void empilhar(Pilha *P, Item *I)
{
    I->Anterior = P->Topo;
    P->Topo = I;
    P->Tamanho++;
}

Item *desempilhar(Pilha *P)
{
    if (P->Tamanho <= 0)
    {
        printf("ERRO: Tentando desempilhar sem itens o suficiente!\n");
        exit(EXIT_FAILURE); // Interrompe a execução com erro
    }

    Item *I = P->Topo;
    P->Topo = I->Anterior;
    P->Tamanho--;

    return I;
}

Item *criarItem(float C)
{
    Item *E = (Item *)malloc(sizeof(Item));

    if (E == NULL)
    {
        printf("ERRO: Problema em alocar memoria;");
        exit(1);
    }
    E->Chave = C;
    E->Anterior = NULL;

    return E;
}
// --------------------------- fundao ----------------------------------------

Item *variosNum(Pilha *P, int cont, int contVirg)
{
    float soma = 0;
    // IF VIRGULA > 0
    if(contVirg > 0){
        // FOR VIRGULA
        for(int i = contVirg; i > 0; i--){
            soma = soma + (desempilhar(P)->Chave / pow(10, i));
            printf("%.3f\n", soma);
        }
    }
    
    // FOR NAO VIRGULA
    for (int i = 0; i < cont; i++)
    {
        printf("Teste %d %d %d\n", i, cont, contVirg);
        soma = soma + (desempilhar(P)->Chave * pow(10, i));
        printf("%.3f\n", soma);
    }
    Item *I = criarItem(soma);
    return I;
}

// Avaliar

float getValor(char *Expressao)
{
    Pilha *P = inicializar();
    int cont = 0, contVirg = 0;
    int virgula = NAO;

    for (int i = 0; Expressao[i] != '\0'; i++)
    {
        if (isdigit(Expressao[i]))
        {
            if (virgula == NAO)
            {
                cont++;
            }
            if (virgula == SIM)
            {
                contVirg++;
            }
            Item *I = criarItem((float)(Expressao[i] - '0'));
            empilhar(P, I);
        }
        else if (Expressao[i] == '.')
        {

            virgula = SIM;
        }
        else if (Expressao[i] == ' ' || Expressao[i] == '\t')
        {

            // NAO MUDA ISSO!!!!!
            if (cont > 1 || contVirg > 0)
            {
                empilhar(P, variosNum(P, cont, contVirg));
            }
            cont = 0;
            contVirg = 0;
            virgula = NAO;
            continue;
        }
        else
        {

            float Operando1;
            float Operando2;

            float Res;
            Item *I;

            // NAO MUDA ISSO!!!!!
            if (cont > 1 || contVirg > 0)
            {
                empilhar(P, variosNum(P, cont, contVirg));
            }
            switch (Expressao[i])
            {
            // ----------FUNÇAO DE GERAIS----------
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
                if (Operando2 == 0)
                {
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

                if (Expressao[i + 1] != 'o' || Expressao[i + 2] != 'g')
                {
                    printf("ERRO");
                    exit(EXIT_FAILURE);
                }

                Res = log10(Operando1);
                i += LOG;
                printf("%.1f %.1f\n", Operando1, Res);
                break;
            // ----------FUNÇAO DE RAIZ----------
            case 'r':
                Operando1 = desempilhar(P)->Chave;

                if (Expressao[i + 1] != 'a' || Expressao[i + 2] != 'i' || Expressao[i + 3] != 'z')
                {
                    printf("ERRO");
                    exit(EXIT_FAILURE);
                }

                Res = sqrt(Operando1);
                i += RAIZ;
                printf("%.1f\n", Res);
                break;
            // ----------FUNÇAO SENO---------
            case 's':
                Operando1 = desempilhar(P)->Chave;

                if (Expressao[i + 1] != 'e' || Expressao[i + 2] != 'n')
                {
                    printf("ERRO");
                    exit(EXIT_FAILURE);
                }

                Res = sin(Operando1);
                i += SEN;
                printf("%.1f\n", Res);
                break;
            // ----------FUNÇAO COSSENO---------
            case 'c':
                Operando1 = desempilhar(P)->Chave;

                if (Expressao[i + 1] != 'o' || Expressao[i + 2] != 's')
                {
                    printf("ERRO");
                    exit(EXIT_FAILURE);
                }

                Res = cos(Operando1);
                i += COS;
                printf("%.1f\n", Res);
                break;
            // ----------FUNÇAO TANGENTE---------
            case 't':
                Operando1 = desempilhar(P)->Chave;

                if (Expressao[i + 1] != 'g')
                {
                    printf("ERRO");
                    exit(EXIT_FAILURE);
                }

                Res = tan(Operando1);
                i += TG;
                printf("%.1f\n", Res);
                break;
            default:
                printf("ERRO: operador invalido!\n");
                exit(EXIT_FAILURE);
                break;
            }

            cont = 0;
            contVirg = 0;
            virgula = NAO;
            I = criarItem(Res);
            empilhar(P, I);
        }
    }

    Item *resultadoItem = desempilhar(P);
    float resultado = resultadoItem->Chave;
    free(resultadoItem); // Liberar a memória do resultado
    free(P);             // Liberar a memória da pilha

    return resultado;
}