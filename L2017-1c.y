%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "tabela.h"
#include "gmepa.h"
#include "comandos.h"
#include "identificadores.h"


extern char yytext[];
extern int yycoluna;
extern int yylinha;

int yylex(void);
void yyerror(const char *s);
int yydebug=1;
FILE *yyin;
FILE *yysaida;
char *formato = NULL;

TipoListaComando comandos_final;
TipoListaId pilha_ident_list;
TipoListaId pilha_param_list;

%}
%union {
	int num;
	char numC;
	float numR;
	char *identificador;
	TipoListaComando *lista_comandos;
	TipoListaId *lista_ids;
	char *ident;
	int tipo;
	
};
%error-verbose
%start program;


%token <num>INTEIRO PROGRAM VAR INTEGER <numR>REAL CHAR BEGINs END DO
%token WHILE IF THEN ELSE NOT ASSIGNOP ADDOP MULOP PROCEDURE REPEAT UNTIL AND OR
%token <num>RELOP WRITE READ tk_FALSE tk_TRUE VALUE REFERENCE <numC>CHAR_CONST NONE EQ LT GT GTE LTE DIF

%token <identificador> IDENTIFICADOR
%type <ident> simple_variable_or_proc
%type <lista_comandos> assign_stmt
%type <lista_comandos> compound_stmt
%type <lista_comandos> cond
%type <lista_comandos> constant
%type <lista_comandos> corpo
%type <lista_comandos> dcl_proc
%type <lista_comandos> dcl_var
%type <lista_comandos> decl
%type <lista_comandos> decl_list
%type <lista_comandos> expr_bool_and
%type <lista_comandos> expr_boolean
%type <lista_comandos> expr_bool_not
%type <lista_ids> espec_parametros
%type <lista_comandos> expr
%type <lista_comandos> expr_list
%type <lista_comandos> factor
%type <lista_comandos> factor_a
%type <lista_comandos> function_ref_par
%type <lista_ids> ident_list
%type <lista_comandos> if_stmt
%type <lista_ids> lista_de_parametros
%type <lista_ids> parametro
%type <lista_comandos> read_stmt
%type <lista_comandos> repeat_stmt
%type <lista_comandos> simple_expr
%type <lista_comandos> stmt
%type <lista_comandos> stmt_list
%type <lista_comandos> term
%type <lista_comandos> write_stmt
%type <num> boolean_constant
%type <num> modo
%type <num> tipo_retornado
%type <num> relop
%type <tipo> type



%type <ident> variable

%%

program:
	PROGRAM IDENTIFICADOR ';' decl_list   compound_stmt 
		{program($4,$5,yysaida,formato);}
;

decl_list:
	  decl_list ';' decl 
		{$$ = decl_list($1,$3);} 
	| decl 
		{$$ = $1;}
;

decl:
	dcl_var 
		{$$ = $1;}
	| dcl_proc 
		{$$ = $1;}
;

dcl_var:
	ident_list ':' type 
		{$$ = Define_Tipos($1,$3);}
;

ident_list:
	ident_list ',' IDENTIFICADOR
		{$$ = ident_list($3,$1);} 
	| IDENTIFICADOR 
		{$$ = ident_list2($1);}
;

type:
	INTEGER 
		{$$=0;}
	| REAL 
		{$$=1;}
	| boolean_constant
		{$$=3;}
	| CHAR 
		{$$=4;}
;

dcl_proc:
	tipo_retornado PROCEDURE IDENTIFICADOR espec_parametros corpo  
		{$$=dcl_procedimento($4,$3,$1,$5);define_param_list($4);}
		
;

tipo_retornado: 
	INTEGER {$$=0;}
	| REAL 
		{$$=1;}
	| boolean_constant 
		{$$=3;}
	| CHAR 
		{$$=4;} 
	| /*Vazio*/
		{$$=5;}
;

corpo:	
	/*vazio*/ 
		{$$ = inicializa_listaComando(); Saida_Bloco();}
	| ':' decl_list ';' compound_stmt   id_return 
		{$$ = corpo($2,$4); Saida_Bloco();}
	| ':' compound_stmt   id_return 
		{$$ = $2; Saida_Bloco();}
;

id_return:
	/*vazio*/ 
	| IDENTIFICADOR
;

espec_parametros:
	 '(' lista_de_parametros ')'
	{$$=$2;};
;

lista_de_parametros:
	lista_de_parametros ',' parametro 
		{$$=$3;}
	| parametro 
		{$$=$1; Entrada_Bloco();}
;

parametro:	modo   type   ':'   IDENTIFICADOR
		{$$ = param_list($1,$2,$4,&pilha_param_list);}
;

modo:
	VALUE
		{$$=0;}
	| REFERENCE 
		{$$=1;}
;

compound_stmt:
	BEGINs stmt_list END 
		{$$ = $2 ;}
;

stmt_list:
	stmt_list ';' stmt
		{$$ = stmt_list($1,$3);}
	| stmt 
		{$$ = $1;}
;

stmt:
	assign_stmt 
		{$$ = $1;}
	| if_stmt
		{$$ = $1;}
	| repeat_stmt 
		{$$ = $1;}
	| read_stmt 
		{$$ = $1;}
	| write_stmt 
		{$$ = $1;}
	| compound_stmt
 		{$$ = $1;}
	| function_ref_par
		{$$ = $1;}
;

assign_stmt:
	IDENTIFICADOR ASSIGNOP expr
		{$$ = assign_stmt($1,$3);}
;

if_stmt:
	IF cond THEN stmt
		{$$ = if_stmt1($2,$4);}
	|IF cond THEN stmt ELSE stmt 
		{$$ = if_stmt2($2,$4 ,$6 );}
;

cond:
	expr_boolean
		{$$ = $1;}
;

expr_boolean: 
	expr_bool_and			
		{$$ = $1;}
	| expr_bool_and OR expr_boolean	
		{$$ = expr_boolean($1, $3);}
;

expr_bool_and: 
	expr_bool_not			
		{$$ = $1;}
	| expr_bool_not AND expr_bool_and	
		{$$ = expr_bool_and($1, $3);}
;
expr_bool_not: 
	expr			
		{$$ = $1;}
	| NOT expr				
		{$$ = expr_bool_not($2);}
;
repeat_stmt:
	REPEAT stmt_list UNTIL expr
		{$$ = repeat_stmt($2,$4);}
;

read_stmt:
	READ '(' ident_list ')' 
		{$$ = read_stmt($3);}
;

write_stmt:
	WRITE '(' expr_list ')'
		{$$ = write_stmt($3);}
;

expr_list:
	expr 
		{$$ = $1;} 
	| expr_list ',' expr 
		{$$ = expr_list($1,$3);}
;

expr:
	simple_expr 
		{$$ = $1;}
	| simple_expr   relop   simple_expr 
		{$$ = expr($1,$2,$3);}
;

relop:
	EQ 
		{$$=1;}
	|LT
		{$$=2;}
	|GT
		{$$=3;}
	|DIF
		{$$=4;}
	|LTE
		{$$=5;}
	|GTE
		{$$=6;}			
;

simple_expr:
	term 
		{$$ = $1;}
	| simple_expr   ADDOP   term 
		{$$ = simple_expr($1,$3);}
;

term:
	factor_a 
		{$$ = $1;}
	| term   MULOP   factor_a 
		{$$ = term($1,$3);} 
;

factor_a:
	'-' factor
		{$$ = factor_a($2);}
	| factor
		{$$ = $1;}
;

factor:	
	IDENTIFICADOR 
		{$$ = factor($1);}
	|constant
		{$$ = $1;}
	|'(' expr ')'
		{$$ = $2;}
	|function_ref_par
		{$$ = $1;}
	|NOT factor
		{$$ = expr_bool_not($2);}
;

function_ref_par:
	variable '(' expr_list ')'
		{$$ = function_ref_par($1,$3);}
;

variable:
	simple_variable_or_proc
		{$$ = $1;}
;

simple_variable_or_proc:
	IDENTIFICADOR
		{$$ = $1;}
;

constant:
	INTEIRO 
		{$$ = constant0( $1 );}
	| REAL 
		{$$ = constant1( $1 );}
	| CHAR_CONST 
		{$$ = constant3( $1 );}
	| boolean_constant 
		{$$ = constant4( $1 );}
;

boolean_constant:
	tk_FALSE 
		{$$ = 0;}
	| tk_TRUE 
		{$$ = 1;}
;

%%



void yyerror(const char *s) {
    fprintf(stderr, "%s: linha %d coluna %d\n", s, yylinha + 1, yycoluna);
}

int main(int argc, char **argv) {
    /* Captura dos parametros de entrada, saida e formato de saida*/
    /******************************************************************/
    /******************************************************************/
    int opt;
    char *entrada = NULL, *saida = NULL;
    if (argc < 6) {
        printf("Uso: ./L2017-1 -i <entrada.pas> -o <saida.o> -c <bin|inter>\n");
        return 0;
    };
    while ((opt = getopt(argc, argv, "i:o:c:")) > 0) {
        switch (opt) {
            case 'i': /* opção -i */
                entrada = optarg;
                break;
            case 'o': /* opção -o */
                saida = optarg;
                break;
            case 'c': /* opção -c */
                formato = optarg;
                break;
            default:
                fprintf(stderr, "Opcao invalida ou faltando argumento: `%c'\n", optopt);
                return -1;
        }
    }
    if (argv[optind] != NULL) {
        int i;

        puts("** Argumentos em excesso **");
        for (i = optind; argv[i] != NULL; i++) {
            printf("-- %s\n", argv[i]);
        }
    }
    /******************************************************************/
    /******************************************************************/
    /* Fim Captura dos parametros de entrada, saida e formato de saida*/

    /* Declara os atributos da estrutura Floresta de Árvores que armazena
    a tabela de símbolos **********************************************/
    /******************************************************************/

    L = 1; /* Considera-se que a primeira posicao da tabela eh a de indice 1. L eh o final da arvore binaria */
    nivel = 1; /* O primeiro nivel o 1 */
    escopo[nivel] = 0; /* escopo[1] contem o indice do primeiro elemento */

    /******************************************************************/
    /******************************************************************/
    /* Fim da declaração da tabela de símbolos*/

    FLVaziaComando(&comandos_final);
    FLVaziaId(&pilha_param_list);


    yyin = fopen(entrada, "r");
    yysaida = fopen(saida, "w+");

    if (yydebug) {
        if (!yyparse())
            printf("\nParsing com sucesso\n");
        else {
            printf("\nParsing falhou\n");
            exit(0);
        }
        printf("\nTabela de símbolos:\n");
        Imprimir();
    } else yyparse();
    fclose(yyin);
    fclose(yysaida);
    return 0;
}
