#LEX = lex
#YACC = yacc -dy
LEX = flex 
#YACC = bison -dy --graph
YACC = bison -dy

CC = gcc

L2017-1c: y.tab.o lex.yy.o tabela.o gmepa.o comandos.o identificadores.o
	$(CC) -o L2017-1c y.tab.o lex.yy.o tabela.o gmepa.o comandos.o identificadores.o -ll -lm
	-rm -f *.o  

lex.yy.o: lex.yy.c y.tab.h

lex.yy.o y.tab.o: L2017-1c.h

y.tab.c y.tab.h: L2017-1c.y
	$(YACC) -v L2017-1c.y

tabela.o: tabela.c tabela.h

gmepa.o: gmepa.c gmepa.h

comandos.o: comandos.c comandos.h

identificadores.o: identificadores.c identificadores.h

lex.yy.c: L2017-1c.flex
	$(LEX) L2017-1c.flex

clean:
	-rm -f *.o lex.yy.c *.tab.* *.dot  L2017-1c *.output
