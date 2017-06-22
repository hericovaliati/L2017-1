#ifndef TABELA_h
#define TABELA_h
#define NMax 100

struct {
    char nome[40]; /* Contem o nome do Simbolo */
    int nivel; /* Contem o nivel do Simbolo relacionado */
    int type; //
    int isReference; // 
    int isGlobal; //
    char atributo[40]; /* Contem o atributo do  relacionado */
    int esq; /* Filho da esquerda do simbolo relacionado */
    int dir; /* Filho da direita do simbolo relacionado */
} TabelaS[100]; /* Vetor de struct que contem a tabela de simbolos */


int escopo[10];
int nivel; /* inteiro que contem o numero do nivel atual */
int L; /* inteiro que contem o indice do ultimo elemento da Tabela de Simbolos */
int Raiz; /* inteiro que contem o indice do primeiro elemento da Tabela de Simbolos */
int proc; /* inteiro que para informa se há declaração de um ou mais procedimentos */

void Erro(int num);

void Entrada_Bloco();

void Saida_Bloco();

int Get_Entry(char x[40]);

int Get_Atributo(char x[40], char * atributo);

int Retorna_Tipo(char x[40]);

void Imprimir();

void Instala(char X[40], char atribut[40], int type, int isReference);

#endif
