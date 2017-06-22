#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef IDENT_H_HEADER_
#define IDENT_H_HEADER_

#define MAX 10

/* ========================================================================= */

typedef struct {
    /* Para empilhar identificadores */
    char identificador[40];
    int type;
    int modo;
} TipoId;

typedef struct TipoCelulaId *TipoApontadorId;

typedef struct TipoCelulaId {
    TipoId Id;
    TipoApontadorId Prox;
} TipoCelulaId;

typedef struct TipoListaId {
    TipoApontadorId Primeiro, Ultimo;
} TipoListaId;

/* ========================================================================= */

void FLVaziaId(TipoListaId *Lista);

int VaziaId(TipoListaId Lista);

void InsereId(TipoId x, TipoListaId *Lista);

void RetiraId(TipoApontadorId p, TipoListaId *Lista, TipoId *Comando);

void PushId(TipoListaId *Lista, TipoId x);

void PopId(TipoListaId *Lista, TipoId *Comando);

int ContaId(TipoListaId Lista);

void ImprimelistaId(TipoListaId Lista);

TipoListaId * inicializa_listaId();

/* ========================================================================== */

#endif
