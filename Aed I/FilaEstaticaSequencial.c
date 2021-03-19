#include <stdio.h>
#include <stdlib.h>
#define MAX 10

struct filaCircular{
    int primeiro;
    int ultimo;
    int elementos[MAX];
};

typedef struct filaCircular tipoFC;

void inicializaFila (tipoFC *filaAux)
{
    int i;
// inicializa a fila
    filaAux->primeiro = -1;
    filaAux->ultimo = -1;
    for (i=0; i<MAX; i++)
        filaAux->elementos[i]=0;
}

int filaVazia(tipoFC *filaAux){
    if ((filaAux->primeiro==filaAux->ultimo) && (filaAux->ultimo==-1))
        return 1; // fila está vazia
    else return 0; // fila não está vazia
}

int filaCheia (tipoFC *filaAux){
    if (((filaAux->ultimo + 1) % MAX) == filaAux->primeiro)
        return 1; // fila está cheia
    else return 0; // fila não está cheia
}

void insereElemento (tipoFC *filaAux, int info){
    int i;

    if (filaVazia(filaAux) == 1){
        scanf("%d",filaAux->elementos[0]);
        filaAux->primeiro=filaAux->elementos[0];
        filaAux->ultimo=filaAux->elementos[1];
    }
    if (filaCheia(filaAux) == 1){
        printf("FILA CHEIA");
    }
    else{
        for (i=0;i=MAX;i++){
            if(filaAux->elementos[i] = 0);
        }
    }
}
