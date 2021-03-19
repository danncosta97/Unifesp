#include <stdlib.h>
#include <stdio.h>

typedef struct noArvoreBB {
    int chave;
    struct noArvoreBinaria* esq;
    struct noArvoreBinaria* dir;
}tipoABB;

void inicializa (int c, tipoABB *arvoreAux){
    arvoreAux->chave = c;
    arvoreAux->esq = NULL;
    arvoreAux->dir = NULL;
}

tipoABB* criaNo (int c) {
    tipoABB* novo = (tipoABB*) malloc(sizeof(tipoABB));
    novo->chave = c;
    novo->dir = NULL;
    novo->esq= NULL;
return novo;
}

void insere (tipoABB *arvoreAux){

}

void imprime (tipoABB *aux){
    if (aux!= NULL)
        printf("%c", aux->chave);
    if (aux->dir!= NULL)
        imprime(aux->dir);
    if (aux->esq!= NULL)
        imprime(aux->esq);
}

int main(){
    tipoABB arvore;
    int c;
    scanf ("%d", c);
    inicializa (c, &arvore);

    int op=0;
    scanf ("%d", op);

    while (op > 0){





    }
return 0;
}
