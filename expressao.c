#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
#define PI 3.14159265358979323846

//---------------- STRUCT ----------------

typedef struct Item
{
    char expressao[512];
    double Chave;
    struct Item *Anterior;
} Item;

typedef struct
{
    int Tamanho;
    Item *Topo;
} Pilha;

//---------------- FUNÇÕES ADICIONAIS ----------------

Pilha *inicializar();
void empilhar(Pilha *P, Item *I);
Item *desempilhar(Pilha *P);
Item *criarItem(double C);
Item *variosNum(Pilha *P, int cont, int contVirg);
void empilharString(Pilha *P, char *exp);
void liberarPilha(Pilha *P);

//---------------- ESTUTURANDO FUNÇÕES ----------------

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
    // printf("Empilhando %.1f:\n", I->Chave);
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
    // printf("Desempilhando %.1f:\n", I->Chave);

    return I;
}

void empilharString(Pilha *P, char *exp)
{
    Item *novo = criarItem(0);
    strcpy(novo->expressao, exp);
    novo->Anterior = P->Topo;
    P->Topo = novo;
    P->Tamanho++;
}

Item *criarItem(double C)
{
    Item *E = (Item *)malloc(sizeof(Item));

    if (E == NULL)
    {
        printf("ERRO: Problema em alocar memoria;");
        exit(1);
    }
    E->Chave = C;
    strcpy(E->expressao, "");
    E->Anterior = NULL;

    return E;
}

void liberarPilha(Pilha *P)
{
    if (P == NULL)
    {
        printf("Erro! Pilha vazia");
        exit(1);
    }
    while (P->Topo != NULL)
    {
        Item *I = desempilhar(P);
        free(I);
    }

    free(P);
}
// --------------------------- fundao ----------------------------------------

Item *variosNum(Pilha *P, int cont, int contVirg)
{
    double soma = 0;
    // IF VIRGULA > 0
    if (contVirg > 0)
    {
        // FOR VIRGULA
        for (int i = contVirg; i > 0; i--)
        {
            Item *I = desempilhar(P);
            soma = soma + (I->Chave / pow(10, i));
            free(I);
            // printf("%f\n", soma);
        }
    }

    // printf("\tApós a virgula: \n");
    // FOR NAO VIRGULA
    for (int i = 0; i < cont; i++)
    {
        Item *I = desempilhar(P);
        // printf("%f * %.2f = ", I->Chave, pow(10, i));
        soma = soma + (I->Chave * pow(10, i));
        free(I);
        // printf("%f\n", soma);
    }

    // printf("%f\n", soma);
    Item *I = criarItem(soma);
    return I;
}

// Avaliar

float getValor(char *Expressao)
{
    Pilha *P = inicializar();
    int cont = 0, contVirg = 0;
    int virgula = NAO, negativo = NAO;

    for (int i = 0; Expressao[i] != '\0'; i++)
    {
        if (isdigit(Expressao[i]) || (Expressao[i] == '-' && isdigit(Expressao[i + 1])))
        {
            if (Expressao[i] == '-')
            {
                negativo = SIM;
                continue;
            }
            if (virgula == NAO)
            {
                cont++;
            }
            if (virgula == SIM)
            {
                contVirg++;
            }
            Item *I = criarItem((double)(Expressao[i] - '0'));
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
            if (negativo == SIM)
            {
                Item *I1 = desempilhar(P);
                I1->Chave = I1->Chave * -1;
                empilhar(P, I1);
                negativo = NAO;
            }
            cont = 0;
            contVirg = 0;
            virgula = NAO;
            continue;
        }
        else
        {

            double Operando1;
            double Operando2;
            double radianos;
            double Res;
            Item *I;

            // NAO MUDA ISSO!!!!!
            if (cont > 1 || contVirg > 0)
            {
                empilhar(P, variosNum(P, cont, contVirg));
            }
            if (negativo == SIM)
            {
                Item *I1 = desempilhar(P);
                I1->Chave = I1->Chave * -1;
                empilhar(P, I1);
                negativo = NAO;
            }
            switch (Expressao[i])
            {
            // ----------FUNÇAO DE GERAIS----------
            case '+':
                Operando2 = desempilhar(P)->Chave;
                Operando1 = desempilhar(P)->Chave;
                Res = Operando1 + Operando2;
                // printf("%.1f %.1f %.1f\n", Operando1, Operando2, Res);
                break;
            case '-':
                Operando2 = desempilhar(P)->Chave;
                Operando1 = desempilhar(P)->Chave;
                Res = Operando1 - Operando2;
                // printf("%.1f %.1f %.1f\n", Operando1, Operando2, Res);
                break;
            case '*':
                Operando2 = desempilhar(P)->Chave;
                Operando1 = desempilhar(P)->Chave;
                Res = Operando1 * Operando2;
                // printf("%.1f %.1f %.1f\n", Operando1, Operando2, Res);
                break;
            case '/':
                Operando2 = desempilhar(P)->Chave;
                Operando1 = desempilhar(P)->Chave;
                if (Operando2 == 0)
                {
                    printf("ERRO: Divisão por zero!\n");
                    liberarPilha(P);
                    return 0;
                }
                Res = Operando1 / Operando2;
                // printf("%.1f %.1f %.1f\n", Operando1, Operando2, Res);
                break;
            case '^':
                Operando2 = desempilhar(P)->Chave;
                Operando1 = desempilhar(P)->Chave;
                Res = pow(Operando1, Operando2);
                // printf("%.1f %.1f %.1f\n", Operando1, Operando2, Res);
                break;

            // ----------FUNÇAO DE LOG----------
            case 'l':
                Operando1 = desempilhar(P)->Chave;

                if (Expressao[i + 1] != 'o' || Expressao[i + 2] != 'g')
                {
                    printf("ERRO");
                    liberarPilha(P);
                    return 0;
                }

                if (Operando1 <= 0)
                {
                    printf("ERRO! Logaritmo invalido");
                    liberarPilha(P);
                    return 0;
                }

                Res = log10(Operando1);
                i += LOG;
                // printf("%.1f\n", Res);
                break;
            // ----------FUNÇAO DE RAIZ----------
            case 'r':
                Operando1 = desempilhar(P)->Chave;

                if (Expressao[i + 1] != 'a' || Expressao[i + 2] != 'i' || Expressao[i + 3] != 'z')
                {
                    printf("ERRO");
                    liberarPilha(P);
                    return 0;
                }

                if (Operando1 < 0)
                {
                    printf("Raiz de números negativos são invalidos\n");
                    liberarPilha(P);
                    return 0;
                }

                Res = sqrt(Operando1);
                i += RAIZ;
                // printf("%.1f\n", Res);
                break;
            // ----------FUNÇAO SENO---------
            case 's':
                Operando1 = desempilhar(P)->Chave;
                radianos = Operando1 * (PI / 180.0);

                if (Expressao[i + 1] != 'e' || Expressao[i + 2] != 'n')
                {
                    printf("ERRO");
                    liberarPilha(P);
                    return 0;
                }

                Res = sin(radianos);
                i += SEN;
                // printf("%.1f\n", Res);
                break;
            // ----------FUNÇAO COSSENO---------
            case 'c':
                Operando1 = desempilhar(P)->Chave;
                radianos = Operando1 * (PI / 180.0);

                if (Expressao[i + 1] != 'o' || Expressao[i + 2] != 's')
                {
                    printf("ERRO");
                    liberarPilha(P);
                    return 0;
                }
                Res = cos(radianos);
                i += COS;
                // printf("%.1f\n", Res);
                break;
            // ----------FUNÇAO TANGENTE---------
            case 't':
                Operando1 = desempilhar(P)->Chave;
                radianos = Operando1 * (PI / 180.0);

                if (Expressao[i + 1] != 'g')
                {
                    printf("ERRO");
                    liberarPilha(P);
                    return 0;
                }

                if (fabs(cos(radianos)) < 1e-10)
                {
                    printf("ERRO! IMPOSSIVEL FAZER O CALCULO DA TANGENTE!\n");
                    liberarPilha(P);
                    return 0;
                }

                Res = tan(radianos);
                i += TG;
                // printf("%.1f\n", Res);
                break;

            default:
                printf("ERRO: operador invalido!\n");
                liberarPilha(P);
                return 0;
                break;
            }

            cont = 0;
            contVirg = 0;
            virgula = NAO;
            I = criarItem(Res);
            empilhar(P, I);
        }
    }

    if (negativo == SIM)
    {
        Item *I1 = desempilhar(P);
        I1->Chave = I1->Chave * -1;
        empilhar(P, I1);
        negativo = NAO;
    }

    Item *resultadoItem = desempilhar(P);
    double resultado = resultadoItem->Chave;
    free(resultadoItem); // Liberar a memória do resultado
    liberarPilha(P);

    return resultado;
}

char *getFormaInFixa(char *Expressao)
{
    Pilha *P = inicializar();
    char token[512];
    int i = 0;

    while (Expressao[i] != '\0')
    {
        if (isdigit(Expressao[i]) || (Expressao[i] == '-' && (i == 0 || Expressao[i - 1] == ' ' && isdigit(Expressao[i + 1]))))
        { // Número ou número negativo
            int j = 0;
            if (Expressao[i] == '-')
            {
                token[j++] = Expressao[i++]; // Adicionar o sinal de negativo
            }
            while (isdigit(Expressao[i]) || Expressao[i] == '.')
            {
                token[j++] = Expressao[i++];
            }
            token[j] = '\0';
            empilharString(P, token);
        }
        else if (Expressao[i] == ' ' || Expressao[i] == '\t')
        {
            i++; // Ignorar espaços
        }
        else if (strncmp(&Expressao[i], "sen", 3) == 0)
        { // Seno
            i += 3;
            char *arg = desempilhar(P)->expressao;
            char novaExpressao[512];
            sprintf(novaExpressao, "sen(%s)", arg);
            free(arg);
            empilharString(P, novaExpressao);
        }
        else if (strncmp(&Expressao[i], "cos", 3) == 0)
        { // Cosseno
            i += 3;
            char *arg = desempilhar(P)->expressao;
            char novaExpressao[512];
            sprintf(novaExpressao, "cos(%s)", arg);
            free(arg);
            empilharString(P, novaExpressao);
        }
        else if (strncmp(&Expressao[i], "tg", 2) == 0)
        { // Tangente
            i += 2;
            char *arg = desempilhar(P)->expressao;
            char novaExpressao[512];
            sprintf(novaExpressao, "tg(%s)", arg);
            free(arg);
            empilharString(P, novaExpressao);
        }
        else if (strncmp(&Expressao[i], "log", 3) == 0)
        { // Logaritmo
            i += 3;
            char *arg = desempilhar(P)->expressao;
            char novaExpressao[512];
            sprintf(novaExpressao, "log(%s)", arg);
            free(arg);
            empilharString(P, novaExpressao);
        }
        else if (strncmp(&Expressao[i], "raiz", 4) == 0)
        { // Raiz quadrada
            i += 4;
            char *arg = desempilhar(P)->expressao;
            char novaExpressao[512];
            sprintf(novaExpressao, "raiz(%s)", arg);
            free(arg);
            empilharString(P, novaExpressao);
        }
        else
        { // Operadores (como +, -, *, /, ^)
            char operador = Expressao[i];
            char *direito = desempilhar(P)->expressao;
            char *esquerdo = desempilhar(P)->expressao;
            char novaExpressao[512];
            sprintf(novaExpressao, "(%s %c %s)", esquerdo, operador, direito);
            free(direito);
            free(esquerdo);
            empilharString(P, novaExpressao);
            i++;
        }
    }

    char *resultado = desempilhar(P)->expressao;
    liberarPilha(P);
    return resultado;
}