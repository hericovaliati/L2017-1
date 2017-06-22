#include "gmepa.h"


void program(TipoListaComando * lista_comandos, TipoListaComando * lista_comandos2, FILE * saida, char * formato) {

    if (proc) {
        TipoComando Comando;
        PopComando(lista_comandos2, &Comando);
        char label[40];
        strcpy(label, "Lbegin");

        strcpy(Comando.rotulo, label);
        PushComando(lista_comandos2, Comando);
    }
    concatena_2_listas(lista_comandos, lista_comandos2);
    if(!strcmp(formato,"bin")){
      ResolveenderecosComando(*lista_comandos);
      ImprimelistaComando(*lista_comandos, saida);
    }else
      ImprimelistaComando(*lista_comandos, saida);
}

TipoListaComando * Define_Tipos(TipoListaId * pilha_ident_list, int tipo) {

    TipoId Id;
    TipoListaComando * lista_comandos = inicializa_listaComando();
    char atrnivel[40];
    int k;
    while (!VaziaId(*pilha_ident_list)) {
        PopId(pilha_ident_list, &Id);
        printf("Instala -> %s na tabela de símbolos com o tipo %d\n", Id.identificador, tipo);
        Instala(Id.identificador, "", tipo, 0);
        k = Get_Entry(Id.identificador);
        sprintf(atrnivel, "%d", TabelaS[k].nivel - 1);
        gerar(lista_comandos, "", "AMEM", atrnivel, "1");
    }
    return lista_comandos;
}

TipoListaComando * dcl_procedimento(TipoListaId * pilha_param_list, char *identificador, int tipo, TipoListaComando * comandos_corpo) {

    TipoListaComando * lista_comandos = inicializa_listaComando();
    printf("Instala procedimento -> %s na tabela de símbolos com o tipo %d e label %s\n", identificador, tipo, "");
    char label[40];
    char desvio[40];
    char param[40];
    if (!proc) {
        gerar(lista_comandos, "", "DSVS", "Lbegin", "");
        proc = 1;
    }
    sprintf(label, "L%d", L + 1);
    Instala(identificador, label, tipo, 0);
    char atrnivel[40];
    int k = Get_Entry(identificador);
    sprintf(atrnivel, "%d", TabelaS[k].nivel);
    gerar(lista_comandos, label, "ENTR", atrnivel, "");
    TipoId Id;
    int nmem = ContaId(*pilha_param_list);
    int dnmem = nmem;
    while (!VaziaId(*pilha_param_list)) {
        PopId(pilha_param_list, &Id);
        printf("Instala -> %s na tabela de símbolos com o tipo %d e modo %d\n", Id.identificador, Id.type, Id.modo);
        Instala(Id.identificador, "param", Id.type, nmem);
        nmem--;
    }
    concatena_2_listas(lista_comandos, comandos_corpo);
    char comandoretorno[40];
    sprintf(comandoretorno, "%d", dnmem);
    gerar(lista_comandos, "", "RTPR", comandoretorno, "");

    return lista_comandos;
}

TipoListaComando * factor(char *identificador) {
    TipoListaComando * lista_comandos = inicializa_listaComando();
    lista_comandos->tipo = Retorna_Tipo(identificador);
    char aux[40];
    sprintf(aux, "%d", nivel - 1);
    gerar(lista_comandos, "", "CRVL", aux, identificador);
    return lista_comandos;

}

TipoListaComando * corpo(TipoListaComando * l1, TipoListaComando * l2) {
    concatena_2_listas(l1, l2);
    return l1;
}

TipoListaComando * constant0(int const_int) {
    TipoListaComando * lista_comandos = inicializa_listaComando();
    char aux[40];
    sprintf(aux, "%d", const_int);
    gerar(lista_comandos, "", "CRCT", aux, "");
    lista_comandos->tipo = 0;
    return lista_comandos;
}

TipoListaComando * constant1(float const_real) {
    TipoListaComando * lista_comandos = inicializa_listaComando();
    char aux[40];
    sprintf(aux, "%f", const_real);
    gerar(lista_comandos, "", "CRCF", aux, "");
    lista_comandos->tipo = 1;
    return lista_comandos;
}

TipoListaComando * constant3(int const_bool) {
    TipoListaComando * lista_comandos = inicializa_listaComando();
    char aux[40];
    sprintf(aux, "%d", const_bool);
    gerar(lista_comandos, "", "CRCT", aux, "");
    lista_comandos->tipo = 1;
    return lista_comandos;
}

TipoListaComando * constant4(char const_char) {
    TipoListaComando * lista_comandos = inicializa_listaComando();
    char aux[40];
    sprintf(aux, "%d", const_char);
    gerar(lista_comandos, "", "CRCT", aux, "");
    lista_comandos->tipo = 4;
    return lista_comandos;
}

TipoListaComando * function_ref_par(char * identificador, TipoListaComando * lista_comandos) {


    TipoComando x;
    strcpy(x.rotulo, "");
    strcpy(x.cmd, "");
    strcpy(x.param1, "");
    strcpy(x.param2, "");
    strcat(x.cmd, "CHPR");

    char endereco[40];
    char label[40];
    int k = Get_Atributo(identificador, label);

    strcat(x.param1, label);

    sprintf(endereco, "%d", TabelaS[k].nivel - 1);
    strcat(x.param2, endereco);

    printf("\nid:%s\n", identificador);

    InsereComando(x, lista_comandos);
    return lista_comandos;
}

TipoListaComando * simple_expr(TipoListaComando * lista_comandos1, TipoListaComando * lista_comandos2) {
    if (lista_comandos1->tipo != lista_comandos2->tipo) {
        fprintf(stderr, "\nErro soma com tipos diferentes\n\n");
        exit(0);
    }
    TipoListaComando * lista_comandos = inicializa_listaComando();
    lista_comandos->tipo = lista_comandos1->tipo;
    concatena_2_listas(lista_comandos, lista_comandos1);
    concatena_2_listas(lista_comandos, lista_comandos2);
    char c[40];
    sprintf(c, "SOMA");
    gerar(lista_comandos, "", c, "", "");
    return lista_comandos;
}

TipoListaComando * factor_a(TipoListaComando * lista_comandos) {
    char c[40];
    sprintf(c, "INVR");
    gerar(lista_comandos, "", c, "", "");
    return lista_comandos;
}

TipoListaComando * term(TipoListaComando * lista_comandos1, TipoListaComando * lista_comandos2) {
    if (lista_comandos1->tipo != lista_comandos2->tipo) {
        fprintf(stderr, "\nErro multiplicacao com tipos diferentes\n\n");
        exit(0);
    }
    TipoListaComando * lista_comandos = inicializa_listaComando();
    lista_comandos->tipo = lista_comandos1->tipo;
    concatena_2_listas(lista_comandos, lista_comandos1);
    concatena_2_listas(lista_comandos, lista_comandos2);
    char c[40];
    sprintf(c, "MULT");
    gerar(lista_comandos, "", c, "", "");
    return lista_comandos;
}

TipoListaComando * decl_list(TipoListaComando * lista_comandos1, TipoListaComando * lista_comandos2) {

    concatena_2_listas(lista_comandos1, lista_comandos2);
    return lista_comandos1;
}

TipoListaComando * stmt_list(TipoListaComando * lista_comandos1, TipoListaComando * lista_comandos2) {
    concatena_2_listas(lista_comandos1, lista_comandos2);
    return lista_comandos1;
}

TipoListaComando * assign_stmt(char* identificador, TipoListaComando * lista_comandos) {

    char aux[40];
    sprintf(aux, "%d", nivel - 1);
    gerar(lista_comandos, "", "ARMZ", aux, identificador);
    return lista_comandos;
}

TipoListaComando * expr_list(TipoListaComando * lista1, TipoListaComando * lista2) {
    concatena_2_listas(lista1, lista2);
    return lista1;
}

TipoListaComando * if_stmt1(TipoListaComando * lista1, TipoListaComando * lista2) {
    int l = 0;

    TipoListaComando * lista_comandos = inicializa_listaComando();
    char label[40];
    sprintf(label, "LI%d", l);
    gerar(lista1, "", "DSVF", label, "");
    sprintf(label, "LI%d", l++);
    gerar(lista2, "", label, "", "");
    concatena_2_listas(lista_comandos, lista1);
    concatena_2_listas(lista_comandos, lista2);
    return lista_comandos;
}

TipoListaComando * if_stmt2(TipoListaComando * lista1, TipoListaComando * lista2, TipoListaComando * lista3) {

    TipoListaComando * lista_comandos = inicializa_listaComando();
    int l = 0;
    char label[40];

    sprintf(label, "LIE%d", l);
    gerar(lista1, "", "DSVF", label, "");

    sprintf(label, "LIED%d %s", l++, lista3->Primeiro->Comando.cmd);
    strcpy(lista3->Primeiro->Comando.cmd, label);

    sprintf(label, "LIE%d", l);
    gerar(lista2, "", "DSVS", label, "");

    sprintf(label, "LIE%d", l++);
    gerar(lista3, "", label, "", "");

    concatena_2_listas(lista_comandos, lista1);
    concatena_2_listas(lista_comandos, lista2);
    concatena_2_listas(lista_comandos, lista3);

    return lista_comandos;
}

TipoListaComando * repeat_stmt(TipoListaComando * lista1, TipoListaComando * lista2) {

    TipoListaComando * lista_comandos = inicializa_listaComando();
    int l = 0;
    char label[40];


    sprintf(label, "LW%d", l);//, lista1->Primeiro->Comando.cmd);
    strcpy(lista1->Primeiro->Comando.rotulo, label);

    sprintf(label, "LW%d", l++);
    gerar(lista2, "", "DSVS" ,label, "");

    sprintf(label, "LW%d", l);
    gerar(lista1, "", "DSVF" , label, "");

    sprintf(label, "LW%d", l++);
    gerar(lista2, label, "", "", "");

    concatena_2_listas(lista_comandos, lista1);
    concatena_2_listas(lista_comandos, lista2);

    return lista_comandos;
}

TipoListaComando * read_stmt(TipoListaId * ident_list) {


    TipoListaComando * lista_comandos = inicializa_listaComando();
    TipoId Id;
    while (!VaziaId(*ident_list)) {
        PopId(ident_list, &Id);
        printf("read -> %s \n", Id.identificador);
        gerar(lista_comandos, "", "LEIT", "", "");
        gerar(lista_comandos, "", "ARMZ", Id.identificador, "");
    }
    return lista_comandos;
}

TipoListaComando * write_stmt(TipoListaComando * lista1) {
    TipoListaComando * lista_comandos = inicializa_listaComando();
    char comando[40];
    TipoComando c;
    while (!VaziaComando(*lista1)) {
        PopComando(lista1, &c);
        if (lista1->tipo == 0)
            sprintf(comando, "IMPR");
        if (lista1->tipo == 1)
            sprintf(comando, "IMPF");
        if (lista1->tipo == 2)
            sprintf(comando, "IMPR");
        if (lista1->tipo == 3)
            sprintf(comando, "IMPC");
        InsereComando(c, lista_comandos);
        gerar(lista_comandos, "", comando, "", "");
    }

    return lista_comandos;
}

TipoListaId * ident_list(char* identificador, TipoListaId * pilha_ident_list) {


    TipoId x;
    strcpy(x.identificador, identificador);
    InsereId(x, pilha_ident_list);
    return pilha_ident_list;
}

TipoListaId * ident_list2(char* identificador) {
    TipoId x;
    strcpy(x.identificador, identificador);
    TipoListaId * pilha_ident_list = inicializa_listaId();
    InsereId(x, pilha_ident_list);
    return pilha_ident_list;
}

TipoListaId * param_list(int modo, int type, char* identificador, TipoListaId * pilha_ident_list) {
    TipoId x;

    strcpy(x.identificador, identificador);
    x.type = type;
    x.modo = modo;
    InsereId(x, pilha_ident_list);
    return pilha_ident_list;
}

TipoListaId * define_param_list(TipoListaId * pilha_ident_list) {
    return pilha_ident_list;
}

TipoListaComando * expr(TipoListaComando * lista1, int relop, TipoListaComando * lista2) {

    if (lista1->tipo != lista2->tipo) {
        fprintf(stderr, "\nERRO! Op relacional tipos diferentes \n\n");
        exit(0);
    }

    TipoListaComando * lista_comandos = inicializa_listaComando();
    lista_comandos->tipo = lista1->tipo;
    char c[40];
    ;
    if (relop == 1) {
        if (lista1->tipo == 0)
            sprintf(c, "CMIG"); //=
        if (lista1->tipo == 1)
            sprintf(c, "CMIF"); //=
    }
    if (relop == 2) {
        if (lista1->tipo == 0)
            sprintf(c, "CMME"); //<
        if (lista1->tipo == 1)
            sprintf(c, "CMNF"); //<
    }
    if (relop == 3) {
        sprintf(c, "CMEG"); //> n
    }
    if (relop == 4) {
        if (lista1->tipo == 0)
            sprintf(c, "CMDG"); //!=
        if (lista1->tipo == 1)
            sprintf(c, "CMDF"); //!=
    }
    if (relop == 5) {
        if (lista1->tipo == 0)
            sprintf(c, "CMEG"); //<=
        if (lista1->tipo == 1)
            sprintf(c, "CMEF"); //<=
    }
    if (relop == 6) {
        sprintf(c, "CMDG"); //>= n
    }

    concatena_2_listas(lista_comandos, lista1);
    concatena_2_listas(lista_comandos, lista2);
    lista_comandos->tipo = 4;
    gerar(lista_comandos, "", c, "", "");
    return lista_comandos;
}

TipoListaComando * expr_boolean(TipoListaComando * lista1, TipoListaComando * lista2) {
    if (lista1->tipo != 4 || lista2->tipo != 4) {
        fprintf(stderr, "\nErro tipo nao bool no or\n\n");
        exit(0);
    }
    TipoListaComando * lista = inicializa_listaComando();
    concatena_2_listas(lista, lista1);
    concatena_2_listas(lista, lista2);
    lista->tipo = 4;
    char comando[40];
    sprintf(comando, "DISJ");
    gerar(lista, "", comando, "", "");
    return lista;
}

TipoListaComando * expr_bool_and(TipoListaComando * lista1, TipoListaComando * lista2) {
    printf("eu entrei aqui %d %d\n", lista1->tipo, lista2->tipo);
    if (lista1->tipo != 4 || lista2->tipo != 4) {
        fprintf(stderr, "\nErro tipo nao bool no and\n\n");
        exit(0);
    }
    TipoListaComando * lista = inicializa_listaComando();
    concatena_2_listas(lista, lista1);
    concatena_2_listas(lista, lista2);
    lista->tipo = 4;
    char comando[40];
    sprintf(comando, "CONJ");
    gerar(lista, "", comando, "", "");
    return lista;
}

TipoListaComando * expr_bool_not(TipoListaComando * lista) {
    if (lista->tipo != 4) {
        fprintf(stderr, "\nErro tipo nao bool no not\n\n");
        exit(0);
    }
    lista->tipo = 4;
    char comando[40];
    sprintf(comando, "CONJ");
    gerar(lista, "", comando, "", "");
    return lista;
}

TipoListaComando * concatena_2_listas(TipoListaComando * l1, TipoListaComando * l2) {
    l1->Ultimo->Prox = l2->Primeiro->Prox;
    l1-> Ultimo = l2 -> Ultimo;
    free(l2);
    return l1;
}

void gerar(TipoListaComando * lista_comandos, char * rotulo, char * codigo, char * param1, char * param2) {
    TipoComando x;
    if (strlen(rotulo))
        strcpy(x.rotulo, rotulo);
    else
        strcpy(x.rotulo, "");

    strcpy(x.cmd, codigo);

    if (strlen(param1))
        strcpy(x.param1, param1);
    else
        strcpy(x.param1, "");

    if (strlen(param2))
        strcpy(x.param2, param2);
    else
        strcpy(x.param2, "");

    InsereComando(x, lista_comandos);
}
