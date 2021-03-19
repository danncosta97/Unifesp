#include <stdio.h>
#include <stdlib.h>

struct dados{
    char nome[15];
    int ra;
    int p1,p2,p3;
    struct dados *proximo;
};
typedef struct dados aluno;

struct lista{
    aluno *primeiro;
    aluno *ultimo;
    int tmh;
};
typedef struct lista listaDE;

void inicializaLista (listaDE *listaAux);
void insereAluno (listaDE *listaAux);

/******************************************/

void inicializaLista (listaDE *listaAux){
    listaAux->primeiro = NULL;
    listaAux->ultimo = NULL;
    listaAux->tmh=0;
}

void insreAluno (listaDE *listaAux){
    aluno *novoAluno = malloc(sizeof(aluno));

    scanf ("%s %d %f %f %f", novoAluno->nome, novoAluno->ra, novoAluno->p1, novoAluno->p2, novoAluno->p3);
    aluno->proximo
}
