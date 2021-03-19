#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct estacao {

  int id;
  struct estacao* proximo;

}estacao;

typedef struct lista {
    int tamanho;
    estacao* primeiro;
    estacao* ultimo;

}lista;

void iniciarLista(lista* list) {
    list->tamanho = 0;
    list->primeiro = NULL;
    list->ultimo = NULL;
}

void adicionarElemento(lista* list) {
    list->tamanho++;

    estacao* novoElemento = (estacao*) malloc(sizeof(estacao));
    novoElemento->id = list->tamanho;
    novoElemento->proximo = NULL;

    if (!list->primeiro) {
        list->primeiro = novoElemento;
        list->ultimo = novoElemento;
    } else {
        list->ultimo->proximo = novoElemento;
        list->ultimo = novoElemento;
    }

    novoElemento->proximo = list->primeiro;
}

int main() {
    lista list;

    iniciarLista(&list);

    srand(time(NULL));
    int i, j;
    for(i = 0; i<((rand()%5)+1); i++) {
        adicionarElemento(&list);
    }

    int tempo = 0;
    for(i=1; i<=50; i++) {

        estacao* aux = list.primeiro->proximo;
        while(aux != list.primeiro) {
            tempo += ( 15 + 2);
            aux = aux->proximo;
        }

        tempo += ( 15 + 2);

        int novosElementos = (rand()%5)+1;

        printf("[%d] Rodada %d => %d, novos elementos = %d\n", list.tamanho, i, tempo, novosElementos);

        for(j = 1; j<=novosElementos; j++) {
            adicionarElemento(&list);
        }
    }


}

