#define SYMBOLTABLESIZE 100
#include "comandos.h"

struct symtab {
  char *name;
  double (*funcptr)();
  double value;
} symtab[SYMBOLTABLESIZE];

struct symtab *symlook();

void printHelp();
void yyerror();
