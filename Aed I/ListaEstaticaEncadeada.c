#include <stdio.h>
#include <stdlib.h>
#define MAX 15

/*****************************TAD.h*********************************/

typedef struct info{
    int numero;
    int proximo;
}tipo_dados;

typedef struct lista{
    int tamanho;
    int primeiro;
    int ultimo;
    int pos_livre;
    tipo_dados elemento[MAX];
}tipo_listaEE;

/****************************TAD.c**********************************/

void inicia (tipo_listaEE *listaAux){
    int i;

    listaAux->tamanho = 0;
    listaAux->primeiro = -1;
    listaAux->ultimo = -1;

    for(i=0;i<MAX;i++){
        listaAux->elemento[i].numero=0;
        listaAux->elemento[i].proximo=-1;
        listaAux->pos_livre = 1;
    }
}

void insere (tipo_listaEE *listaAux)

/***************************main.c**********************************/

int main(){

return 0;
}
