#include "identificadores.h"

void FLVaziaId(TipoListaId *Lista) {
    Lista -> Primeiro = (TipoApontadorId) malloc(sizeof (TipoCelulaId));
    Lista -> Ultimo = Lista -> Primeiro;
    Lista -> Primeiro -> Prox = NULL;
}

int VaziaId(TipoListaId Lista) {
    return (Lista.Primeiro == Lista.Ultimo);
}

void InsereId(TipoId x, TipoListaId *Lista) {

    Lista -> Ultimo -> Prox = (TipoApontadorId) malloc(sizeof (TipoCelulaId));
    Lista -> Ultimo = Lista -> Ultimo -> Prox;
    strcpy(Lista -> Ultimo -> Id.identificador, x.identificador);
    Lista -> Ultimo -> Prox = NULL;
}

void RetiraId(TipoApontadorId p, TipoListaId *Lista, TipoId *Id) { /*  ---   Obs.: o Id a ser retirado e  o seguinte ao apontado por  p --- */
    TipoApontadorId q;
    if (VaziaId(*Lista) || p == NULL || p -> Prox == NULL) {
        printf(" Erro   Lista vazia ou posi  c   a o n  a o existe\n");
        return;
    }
    q = p -> Prox;
    *Id = q -> Id;
    p -> Prox = q -> Prox;
    if (p -> Prox == NULL) Lista -> Ultimo = p;
    free(q);
}

/*  ---   Obs.: retira e retorna o primeiro elemento da lista --- */
void PopId(TipoListaId *Lista, TipoId *Id) {
    TipoApontadorId q;
    TipoApontadorId p = Lista -> Primeiro;
    q = p -> Prox;
    *Id = q -> Id;
    p -> Prox = q -> Prox;
    if (p -> Prox == NULL) Lista -> Ultimo = p;
    free(q);
}

void PushId(TipoListaId *Lista, TipoId x) {
    TipoApontadorId tmp = (TipoApontadorId) malloc(sizeof (TipoCelulaId));
    tmp-> Prox = Lista-> Primeiro->Prox;
    Lista -> Primeiro -> Prox = tmp;
    Lista -> Ultimo = Lista -> Ultimo -> Prox;
    strcpy(tmp -> Id.identificador, x.identificador);

}

int ContaId(TipoListaId Lista) {
    TipoApontadorId Aux;
    Aux = Lista.Primeiro -> Prox;
    int n = 0;
    while (Aux != NULL) {
        n++;
        Aux = Aux -> Prox;
    }
    return n;
}

void ImprimelistaId(TipoListaId Lista) {
    TipoApontadorId Aux;
    Aux = Lista.Primeiro -> Prox;
    while (Aux != NULL) {
        printf("%s\n", Aux -> Id.identificador);
        Aux = Aux -> Prox;
    }
}

TipoListaId * inicializa_listaId() {
    TipoListaId * lista = (TipoListaId *) malloc(sizeof (TipoListaId));
    FLVaziaId(lista);
    return lista;
}
