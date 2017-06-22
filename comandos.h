#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tabela.h"

#ifndef COMANDOS_H_HEADER_
#define COMANDOS_H_HEADER_

#define MAX 10

/* ========================================================================= */

typedef struct {
    /*Para empilhar comandos*/
    char rotulo[40];
    char cmd[40];
    char param1[40];
    char param2[40];

} TipoComando;

typedef struct TipoCelulaComando *TipoApontadorComando;

typedef struct TipoCelulaComando {
    TipoComando Comando;
    TipoApontadorComando Prox;
} TipoCelulaComando;

typedef struct TipoLista {
    TipoApontadorComando Primeiro, Ultimo;
    int tipo;
} TipoListaComando;

/* ========================================================================= */

void FLVaziaComando(TipoListaComando *Lista);

int VaziaComando(TipoListaComando Lista);

void InsereComando(TipoComando x, TipoListaComando *Lista);

void RetiraComando(TipoApontadorComando p, TipoListaComando *Lista, TipoComando *Comando);

void PushComando(TipoListaComando *Lista, TipoComando x);

void PopComando(TipoListaComando *Lista, TipoComando *Comando);

void ResolveenderecosComando(TipoListaComando Lista);

int rotuloEnd(TipoListaComando Lista, char * rotulo);

void ImprimelistaComando(TipoListaComando Lista, FILE *saida);

void ImprimelistaComandoBin(TipoListaComando Lista, FILE *saida);

TipoListaComando * inicializa_listaComando();

/* ========================================================================== */

#endif
