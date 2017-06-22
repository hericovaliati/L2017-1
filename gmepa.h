#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tabela.h"
#include "comandos.h"
#include "identificadores.h"



#ifndef GMEPA_H
#define GMEPA_H

TipoListaComando * assign_stmt(char* identificador,TipoListaComando * lista_comandos);
TipoListaComando * concatena_2_listas(TipoListaComando * l1, TipoListaComando * l2);
TipoListaComando * constant0(int const_int);
TipoListaComando * constant1(float const_real);
TipoListaComando * constant3(int const_bool);
TipoListaComando * constant4(char const_char);
TipoListaComando  * dcl_procedimento(TipoListaId  * pilha_param_list, char *identificador, int tipo, TipoListaComando  * comandos_corpo);
TipoListaComando * decl_list(TipoListaComando * lista_comandos1, TipoListaComando * lista_comandos2);
TipoListaComando * Define_Tipos(TipoListaId * pilha_ident_list, int tipo);
TipoListaId * define_param_list(TipoListaId * pilha_ident_list);
TipoListaComando * expr(TipoListaComando * lista1, int relop, TipoListaComando * lista2);
TipoListaComando * expr_list(TipoListaComando* lista1 , TipoListaComando* lista2);
TipoListaComando * factor(char *identificador);
TipoListaComando * corpo(TipoListaComando * l1,TipoListaComando * l2);
TipoListaComando * factor_a(TipoListaComando * lista_comandos);
TipoListaComando * function_ref_par(char * identificador, TipoListaComando * lista_comandos);
TipoListaId  * ident_list(char* identificador, TipoListaId  * pilha_ident_list);
TipoListaId  * ident_list2(char* identificador);
TipoListaComando * if_stmt1(TipoListaComando * lista1, TipoListaComando * lista2);
TipoListaComando * if_stmt2(TipoListaComando * lista1, TipoListaComando * lista2, TipoListaComando * lista3);
TipoListaComando * inicializa_lista();
TipoListaId  * param_list(int modo, int type, char* identificador, TipoListaId  * pilha_ident_list) ;
TipoListaComando * read_stmt(TipoListaId * ident_list);
TipoListaComando * repeat_stmt(TipoListaComando * lista1, TipoListaComando * lista2);
TipoListaComando * simple_expr(TipoListaComando * lista_comandos1, TipoListaComando * lista_comandos2);
TipoListaComando * stmt_list(TipoListaComando * lista_comandos1, TipoListaComando * lista_comandos2);
TipoListaComando * term(TipoListaComando * lista_comandos1, TipoListaComando * lista_comandos2);
TipoListaComando  * write_stmt(TipoListaComando * lista1);
TipoListaComando * expr_boolean(TipoListaComando * lista1 , TipoListaComando * lista2);
TipoListaComando * expr_bool_not(TipoListaComando * lista1);
TipoListaComando * expr_bool_and(TipoListaComando * lista1 , TipoListaComando * lista2);
void gerar(TipoListaComando * lista_comandos, char * rotulo, char * codigo, char * param1, char * param2);
void program(TipoListaComando * lista_comandos, TipoListaComando * lista_comandos2, FILE * saida, char * formato);
#endif

