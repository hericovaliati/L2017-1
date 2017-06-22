#include "comandos.h"

void FLVaziaComando(TipoListaComando *Lista) {
    Lista -> Primeiro = (TipoApontadorComando) malloc(sizeof (TipoCelulaComando));
    Lista -> Ultimo = Lista -> Primeiro;
    Lista -> Primeiro -> Prox = NULL;
}

int VaziaComando(TipoListaComando Lista) {
    return (Lista.Primeiro == Lista.Ultimo);
}

void InsereComando(TipoComando x, TipoListaComando *Lista) {
    Lista -> Ultimo -> Prox = (TipoApontadorComando) malloc(sizeof (TipoCelulaComando));

    Lista -> Ultimo = Lista -> Ultimo -> Prox;

    strcpy(Lista -> Ultimo -> Comando.rotulo, x.rotulo);
    strcpy(Lista -> Ultimo -> Comando.cmd, x.cmd);
    strcpy(Lista -> Ultimo -> Comando.param1, x.param1);
    strcpy(Lista -> Ultimo -> Comando.param2, x.param2);
    Lista -> Ultimo -> Prox = NULL;
}

/*  ---   Obs.: o comando a ser retirado e  o seguinte ao apontado por  p --- */
void RetiraComando(TipoApontadorComando p, TipoListaComando *Lista, TipoComando *Comando) {
    TipoApontadorComando q;
    if (VaziaComando(*Lista) || p == NULL || p -> Prox == NULL) {
        printf(" Erro   Lista vazia ou posi  c   a o n  a o existe\n");
        return;
    }
    q = p -> Prox;
    *Comando = q -> Comando;
    p -> Prox = q -> Prox;
    if (p -> Prox == NULL) Lista -> Ultimo = p;
    free(q);
}

/*  ---   Obs.: retira e retorna o primeiro elemento da lista --- */
void PopComando(TipoListaComando *Lista, TipoComando *Comando) {
    TipoApontadorComando q;
    TipoApontadorComando p = Lista -> Primeiro;
    q = p -> Prox;
    *Comando = q -> Comando;
    p -> Prox = q -> Prox;
    if (p -> Prox == NULL) Lista -> Ultimo = p;
    free(q);
}

void PushComando(TipoListaComando *Lista, TipoComando x) {
    TipoApontadorComando tmp = (TipoApontadorComando) malloc(sizeof (TipoCelulaComando));
    tmp-> Prox = Lista-> Primeiro->Prox;
    Lista -> Primeiro -> Prox = tmp;
    Lista -> Ultimo = Lista -> Ultimo -> Prox;
    strcpy(tmp -> Comando.rotulo, x.rotulo);
    strcpy(tmp -> Comando.cmd, x.cmd);
    strcpy(tmp -> Comando.param1, x.param1);
    strcpy(tmp -> Comando.param2, x.param2);
}

void ResolveenderecosComando(TipoListaComando Lista) {
    TipoApontadorComando Aux;
    TipoComando Aux2;
    Aux = Lista.Primeiro -> Prox;
    while (Aux != NULL) {

        char tmp[40] = "";

        if(strlen(Aux->Comando.rotulo) && !strlen(Aux->Comando.cmd) && !strlen(Aux->Prox->Comando.rotulo))
        {
		strcpy(Aux->Comando.cmd, Aux->Prox->Comando.cmd);
		strcpy(Aux->Comando.param1, Aux->Prox->Comando.param1);
		strcpy(Aux->Comando.param2, Aux->Prox->Comando.param2);
                RetiraComando(Aux->Prox, &Lista, &Aux2);
        }
        if (strlen(Aux->Comando.param1)) {
            int k = Get_Entry(Aux->Comando.param1);
            if (k) {
                if (TabelaS[k].isReference) {
                    sprintf(tmp, " -%d", TabelaS[k].isReference + 4);
                    strcpy(Aux->Comando.param1, tmp);
                } else {
                    sprintf(tmp, " %d", k - 1);
                    strcpy(Aux->Comando.param1, tmp);
                }
            } else {
                int rot = rotuloEnd(Lista, Aux->Comando.param1);
                if (rot) {
                    sprintf(tmp, " %d", rot);
                    strcpy(Aux->Comando.param1, tmp);
                } else {
                    sprintf(tmp, " %s", Aux->Comando.param1);
                    strcpy(Aux->Comando.param1, tmp);
                }
            }

        }

        if (strlen(Aux->Comando.param2)) {
            int k = Get_Entry(Aux->Comando.param2);
            if (k) {
                if (TabelaS[k].isReference) {
                    sprintf(tmp, " -%d", TabelaS[k].isReference + 4);
                    strcpy(Aux->Comando.param2, tmp);
                } else {
                    sprintf(tmp, " %d", k - 1);
                    strcpy(Aux->Comando.param2, tmp);
                }
            } else {
                int rot = rotuloEnd(Lista, Aux->Comando.param2);
                if (rot) {
                    sprintf(tmp, " %d", rot);
                    strcpy(Aux->Comando.param2, tmp);
                } else {
                    sprintf(tmp, " %s", Aux->Comando.param2);
                    strcpy(Aux->Comando.param2, tmp);
                }
            }

        }
        Aux = Aux -> Prox;
    }
}

int RetornaOpCode(char * cmd) {

    if (!strcmp(cmd, "AMEM")) return 0;
    if (!strcmp(cmd, "ARMI")) return 1;
    if (!strcmp(cmd, "ARMP")) return 2;
    if (!strcmp(cmd, "ARMZ")) return 3;
    if (!strcmp(cmd, "CHPP")) return 4;
    if (!strcmp(cmd, "CHPR")) return 5;
    if (!strcmp(cmd, "CMAF")) return 6;
    if (!strcmp(cmd, "CMAG")) return 7;
    if (!strcmp(cmd, "CMDF")) return 8;
    if (!strcmp(cmd, "CMDG")) return 9;
    if (!strcmp(cmd, "CMEF")) return 10;
    if (!strcmp(cmd, "CMEG")) return 11;
    if (!strcmp(cmd, "CMIF")) return 12;
    if (!strcmp(cmd, "CMIG")) return 13;
    if (!strcmp(cmd, "CMMA")) return 14;
    if (!strcmp(cmd, "CMMF")) return 15;
    if (!strcmp(cmd, "CMME")) return 16;
    if (!strcmp(cmd, "CMNF")) return 17;
    if (!strcmp(cmd, "CONJ")) return 18;
    if (!strcmp(cmd, "CRCT")) return 19;
    if (!strcmp(cmd, "CRCF")) return 20;
    if (!strcmp(cmd, "CREG")) return 21;
    if (!strcmp(cmd, "CREN")) return 22;
    if (!strcmp(cmd, "CRVI")) return 23;
    if (!strcmp(cmd, "CRVL")) return 24;
    if (!strcmp(cmd, "CRVP")) return 25;
    if (!strcmp(cmd, "DISJ")) return 26;
    if (!strcmp(cmd, "DIVF")) return 27;
    if (!strcmp(cmd, "DIVI")) return 28;
    if (!strcmp(cmd, "DMEM")) return 29;
    if (!strcmp(cmd, "DSVF")) return 30;
    if (!strcmp(cmd, "DSVS")) return 31;
    if (!strcmp(cmd, "ENTR")) return 32;
    if (!strcmp(cmd, "IMPC")) return 33;
    if (!strcmp(cmd, "IMPF")) return 34;
    if (!strcmp(cmd, "IMPR")) return 35;
    if (!strcmp(cmd, "INPP")) return 36;
    if (!strcmp(cmd, "INVF")) return 37;
    if (!strcmp(cmd, "INVR")) return 38;
    if (!strcmp(cmd, "LEIT")) return 39;
    if (!strcmp(cmd, "LEIF")) return 40;
    if (!strcmp(cmd, "MULF")) return 41;
    if (!strcmp(cmd, "MULT")) return 42;
    if (!strcmp(cmd, "NEGA")) return 43;
    if (!strcmp(cmd, "RTPR")) return 44;
    if (!strcmp(cmd, "SOMA")) return 45;
    if (!strcmp(cmd, "SOMF")) return 46;
    if (!strcmp(cmd, "SUBT")) return 47;
    if (!strcmp(cmd, "SUBF")) return 48;
    if (!strcmp(cmd, "PARA")) return 49;

    return 77;
}

int rotuloEnd(TipoListaComando Lista, char * rotulo) {
    TipoApontadorComando Aux;
    Aux = Lista.Primeiro -> Prox;
    int n = 0;
    while (Aux != NULL) {

        n++;
        if (!strcmp(Aux->Comando.rotulo, rotulo)) {
            return n;
        }

        Aux = Aux -> Prox;
    }
    return 0;
}

void ImprimelistaComando(TipoListaComando Lista, FILE *saida) {
    TipoApontadorComando Aux;
    Aux = Lista.Primeiro -> Prox;
    fprintf(saida,"INPP\n");
    while (Aux != NULL) {

        char tmp[40] = "";

        if (strlen(Aux->Comando.rotulo)) {
            strcat(tmp, Aux->Comando.rotulo);
            strcat(tmp, " ");
        }

        strcat(tmp, Aux->Comando.cmd);

        if (strlen(Aux->Comando.param1)) {
            strcat(tmp, " ");
            strcat(tmp, Aux->Comando.param1);
        }


        if (strlen(Aux->Comando.param2)) {
            strcat(tmp, " ");
            strcat(tmp, Aux->Comando.param2);
        }

        fprintf(saida,"%s\n", tmp);
        Aux = Aux -> Prox;
    }
    fprintf(saida,"PARA");
}

void ImprimelistaComandoBin(TipoListaComando Lista, FILE *saida) {
    TipoApontadorComando Aux;
    Aux = Lista.Primeiro -> Prox;
    fprintf(saida,"%d\n", RetornaOpCode("INPP"));
    while (Aux != NULL) {

        char tmp[40] = "";
        int opcode = RetornaOpCode(Aux->Comando.cmd);
        if (opcode == 77)
            sprintf(tmp, "%s", Aux->Comando.cmd);
        else
            sprintf(tmp, "%d", RetornaOpCode(Aux->Comando.cmd));

        if (strlen(Aux->Comando.param1)) {

            strcat(tmp, Aux->Comando.param1);

        }
        if (strlen(Aux->Comando.param2)) {

            strcat(tmp, Aux->Comando.param2);
        }

        fprintf(saida,"%s\n", tmp);

        Aux = Aux -> Prox;
    }
    fprintf(saida,"%d", RetornaOpCode("PARA"));
}

TipoListaComando * inicializa_listaComando() {
    TipoListaComando * lista = (TipoListaComando *) malloc(sizeof (TipoListaComando));
    FLVaziaComando(lista);
    return lista;
}
