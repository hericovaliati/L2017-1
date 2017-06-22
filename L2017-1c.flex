/* Analisador léxico para MiniJava */

%{
#include <stdio.h>
#include <string.h>
#include "comandos.h"
#include "identificadores.h"
#include "y.tab.h"
#include "tabela.h"

int yylinha;
int yycoluna;
void conta(); //Conta em qual coluna está a análise léxica


#define debug 0

%}

LINHA \n
DIGITO [0-9]+
LETRA [a-zA-Z]+
ID [a-zA-Z0-9_]+ 

%%

"'"[a-zA-Z]"'" 		{if(debug) printf ("CHAR_CONST\n"); conta(); return CHAR_CONST; }



"program"                       {if(debug) printf ("PROGRAM\n"); conta(); return PROGRAM ; }
"var"                           {if(debug) printf ("VAR\n"); conta(); return VAR ; }
"procedure"			{if(debug) printf ("PROCEDURE\n"); conta(); return PROCEDURE ; }
"begin"                         {if(debug) printf ("BEGINs\n"); conta(); return BEGINs ; }
"end"                           {if(debug) printf ("END\n"); conta(); return END ; }

"integer"                       {if(debug) printf ("INTEGER\n"); conta(); return INTEGER ; }
"real"                          {if(debug) printf ("REAL\n"); conta(); return REAL ;}
"char"                          {if(debug) printf ("CHAR\n"); conta(); return CHAR ;}



"do"                            {if(debug) printf ("DO\n"); conta(); return DO ; }
"while"                         {if(debug) printf ("WHILE\n"); conta(); return WHILE ; }
"repeat"                        {if(debug) printf ("REPEAT\n"); conta(); return REPEAT; }
"until"                         {if(debug) printf ("UNTIL\n"); conta(); return UNTIL; }
"if"                            {if(debug) printf ("IF\n"); conta(); return IF ; }
"then"                          {if(debug) printf ("THEN\n"); conta(); return THEN ; }
"else"                          {if(debug) printf ("ELSE\n"); conta(); return ELSE ; }



"write"				{if(debug) printf ("WRITE\n"); conta(); return WRITE ; }
"read"				{if(debug) printf ("READ\n"); conta(); return READ ; }

"value"				{if(debug) printf ("VALUE\n"); conta(); return VALUE ; }
"reference"			{if(debug) printf ("REFERENCE\n"); conta(); return REFERENCE ; }

"false"				{if(debug) printf ("tk_FALSE\n"); conta(); return tk_FALSE ; }
"true"				{if(debug) printf ("tk_TRUE\n"); conta(); return tk_TRUE ; }



"NOT" 				{if(debug) printf ("NOT\n"); conta(); return NOT ; }
":=" 				{if(debug) printf ("ASSIGNOP\n"); conta(); return ASSIGNOP ; }


"("			{if(debug) printf ("(\n"); conta(); return '('; }
")"			{if(debug) printf (")\n"); conta(); return ')'; }

";"			{if(debug) printf (";\n"); conta(); return ';'; }
","			{if(debug) printf (",\n"); conta(); return ','; }
":"			{if(debug) printf (":\n"); conta(); return ':'; }


"+"			{if(debug) printf ("+\n"); conta(); return ADDOP; }
"-"			{if(debug) printf ("-\n"); conta(); return ADDOP; }
"or"			{if(debug) printf ("or\n"); conta(); return OR; }

"*"			{if(debug) printf ("*\n"); conta(); return MULOP; }
"/"			{if(debug) printf ("/\n"); conta(); return MULOP; }
"div"			{if(debug) printf ("div\n"); conta(); return MULOP; }
"mod"			{if(debug) printf ("mod\n"); conta(); return MULOP; }
"and"			{if(debug) printf ("and------------\n"); conta(); return AND; }


"."			{if(debug) printf (".\n"); conta(); return '.'; }
"="			{if(debug) printf ("RELOP\n"); conta(); return EQ ; }
"<"			{if(debug) printf ("RELOP\n"); conta(); return LT ; }
">"         {if(debug) printf ("RELOP\n"); conta(); return GT ; }
"!="		{if(debug) printf ("RELOP\n"); conta(); return DIF ; }
"<="		{if(debug) printf ("RELOP\n"); conta(); return LTE ; }
">=" 		{if(debug) printf ("RELOP\n"); conta(); return GTE ; }



{DIGITO}+		{if(debug) printf ("INTEIRO\n"); conta(); 
			/*int p = Get_Entry (yytext); 
			printf("\n-------%d--------\n", p);
			if (!p) 
				Instala(yytext, "" , IDENTIFICADOR, INTEIRO);*/
			yylval.num = atoi(yytext); 
			return INTEIRO; }

({DIGITO}+[.]{DIGITO}*)|({DIGITO}*[.]{DIGITO}+) {if(debug) printf ("REAL\n"); conta(); 
			/*int p = Get_Entry (yytext); 
			printf("\n-------%d--------\n", p);
			if (!p) 
				Instala(yytext, "" , IDENTIFICADOR, REAL);*/
			yylval.num = atof(yytext); 
			return REAL; }

{ID}			{if(debug) printf ("IDENTIFICADOR\n"); conta(); 

			/*int p = Get_Entry (yytext); 
			printf("\n-------%d--------\n", p);
			if (!p) 
				Instala(yytext, "" , IDENTIFICADOR, NONE);*/ 
			yylval.identificador = strdup(yytext);
			return IDENTIFICADOR; }


[\t]*			{yycoluna=yycoluna+8;} /*limpa tabs */
[ \r]*			{yycoluna++;}  /*limpa espacos*/      
{LINHA}			{yylinha++; yycoluna=0;} /*limpa quebras de linha */


.			{ printf ("Caracter não reconhecido: %s\n", yytext);}

%%

void conta()
{
	yycoluna=yycoluna+strlen(yytext);
}

/*
int main(void) {
    yylex();
    return 0;
}
*/
