#include <stdio.h>
#include <stdlib.h>
#include "tabela.h"
#include <string.h>


/**************************************************************************
Implementacoes
 ***************************************************************************/

/************  Funcao que define os erros provaveis de ocorrer  **********/

void Erro(int num) {
    char opcao;
    switch (num) {
        case 1: printf("Tabela de Simbolos cheia\n");
            break;
        case 2: printf("Este item nao foi encontrado\n");
            break;
        case 3: printf("Este item ja foi inserido\n");
            break;
    }
}

/*******************     Funcao de entrada num bloco   ********************/

void Entrada_Bloco() {
    nivel++;
    if (nivel > NMax)
        Erro(1);
    else escopo[nivel] = 0;
    printf("\nEntrada no nivel  %d\n", nivel);
}

/********************  Funcao de saida de um bloco  ***********************/
void Saida_Bloco() {
    int i;
    if (escopo[nivel] != 0) L = escopo[nivel];
    printf("\nSaida do nivel %d\n", nivel);
    nivel--;
}
/********************  Funcao para definir o tipo de multipas declações x, y, z: tipo  ***********************/


/****************  Funcao que pesquisa item na tabela  *******************/

/* Pesquisa o simbolo "x" e retorna o indice da Tabela de simbolos onde ele se encontra */
int Get_Entry(char x[40]) {
    int n, k, aux, achou;
    achou = 0;
    n = nivel;
    while (n > 0) {
        k = escopo[n];
        while ((k != 0)&&(achou == 0)) {
            aux = strcmp(TabelaS[k].nome, x);
            if (aux == 0) achou = 1;
            else if (x < TabelaS[k].nome) k = TabelaS[k].esq;
            else k = TabelaS[k].dir;
        }
        n--;
    }
    if (achou == 1) {
        printf("\nO item: %s esta no nivel: %d", x, TabelaS[k].nivel);
        printf("               Indice: %u\n", k);
        return (k);
    } else {
        Erro(2);
        return (0); /* Retorna o indice no vetor TabelaS do elemento procurado*/
    }
}

int Get_Atributo(char x[40], char * atributo) {
    int n, k, aux, achou;
    achou = 0;
    n = nivel;
    while (n > 0) {
        k = escopo[n];
        while ((k != 0)&&(achou == 0)) {
            aux = strcmp(TabelaS[k].nome, x);
            if (aux == 0) achou = 1;
            else if (x < TabelaS[k].nome) k = TabelaS[k].esq;
            else k = TabelaS[k].dir;
        }
        n--;
    }
    if (achou == 1) {
        printf("\nO item esta no nivel: %d", TabelaS[k].nivel);
        printf("               Indice: %u\n", k);
        strcpy(atributo, TabelaS[k].atributo);
        return (k);
    } else {
        Erro(2);
        return (0); /* Retorna o indice no vetor TabelaS do elemento procurado*/
    }
}

/* Pesquisa o tipo de uma entrada na tabela de símbolos */
int Retorna_Tipo(char x[40]) {
    int n, k, aux, achou;
    achou = 0;
    n = nivel;
    while (n > 0) {
        k = escopo[n];
        while ((k != 0)&&(achou == 0)) {
            aux = strcmp(TabelaS[k].nome, x);
            if (aux == 0) achou = 1;
            else if (x < TabelaS[k].nome) k = TabelaS[k].esq;
            else k = TabelaS[k].dir;
        }
        n--;
    }
    if (achou == 1) {
        printf("\nO item esta no nivel: %d", TabelaS[k].nivel);
        printf("               Indice: %u\n", k);
        return (TabelaS[k].type);
    } else {
        Erro(2);
        return (0); /* Retorna o indice no vetor TabelaS do elemento procurado*/
    }
}

/***************  Funcao que instala o item na tabela  *****************/

/* Instala o simbolo "X" com o atributo atribut na Tabela de Simbolos */
void Instala(char X[40], char atribut[40], int type, int isReference) {
    int S, i, k, aux;
    S = escopo[nivel];
    while (S != 0) /* Enquanto nao achar um nodo folha  */ {
        i = S;
        aux = strcmp(TabelaS[S].nome, X);
        if (aux == 0) Erro(3);
        else if (X < TabelaS[S].nome) S = TabelaS[S].esq;
        else S = TabelaS[S].dir;
    }
    if (L >= NMax + 1) Erro(1);
    else {
        TabelaS[L].nivel = nivel;
        aux = strlen(atribut);
        for (k = 0; k <= aux - 1; k++)
            TabelaS[L].atributo[k] = atribut[k];
        TabelaS[L].type = type;
        TabelaS[L].isReference = isReference;
        TabelaS[L].esq = TabelaS[L].dir = 0;
        aux = strlen(X);
        for (k = 0; k <= (aux - 1); k++)
            TabelaS[L].nome[k] = X[k];
        if (escopo[nivel] == 0) escopo[nivel] = L;
        else if (X < TabelaS[i].nome)
            TabelaS[i].esq = L;
        else TabelaS[i].dir = L;
        L++;
    }
}

void Imprimir() {
    int i;
    for (i = 1; i <= L - 1; i++) {
        printf("\n\nNome : ");
        printf("%s", TabelaS[i].nome);
        printf("\n");
        printf("Atributo : ");
        printf("%s", TabelaS[i].atributo);
        printf("\n");
        printf("Nivel : ");
        printf("%i", TabelaS[i].nivel);
        printf("\n");
        printf("Type : ");
        printf("%d\n", TabelaS[i].type);
        printf("Esquerdo : ");
        printf("%i", TabelaS[i].esq);
        printf("\n");
        printf("Direito : ");
        printf("%i", TabelaS[i].dir);
        printf("\n");
        printf("\n");
    }
}
