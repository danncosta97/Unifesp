#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct processo {

    int id;
    int prioridade;
    int ciclos;
    struct processo* prox;

} processo;

typedef struct fila {

    int tamanho;
    processo* primeiro;
    processo* ultimo;

} fila;


void iniciarFila(fila* fil) {

    fil->primeiro = NULL;
    fil->ultimo = NULL;

    fil->tamanho = 0;
}
processo* getProcessInPosition(fila* fil, int pos) {

    if (pos < 0) {
        return NULL;
    }

    processo* process = fil->primeiro;

    int i;
    for(i = 0; i<pos; i++) {
            process = process->prox;
    }

    return process;
}

int getHigherPriorityProcessPos(fila* fil) {
    int maximaPrioridade = 0;
    int pos = 0;

    int i;
    for(i=0; i<fil->tamanho; i++) {
        processo* pro = getProcessInPosition(fil, i);
        if (pro->prioridade > maximaPrioridade) {
            maximaPrioridade = pro->prioridade;
            pos = i;
        }
    }

    return pos;

}

void adicionarElemento(fila* fil, int ciclos, int id, int prioridade) {

    fil->tamanho++;

    processo* novoProcesso = (processo*) malloc(sizeof(processo));
    if(!fil->primeiro) {
        fil->primeiro = novoProcesso;
        fil->ultimo = novoProcesso;
    } else {
        fil->ultimo->prox = novoProcesso;
        fil->ultimo = novoProcesso;
    }

    novoProcesso->prox = NULL;

    novoProcesso->prioridade = prioridade;
    novoProcesso->ciclos = ciclos;
    novoProcesso->id = id;

}

void removerElementoNaPosicao(fila* fil, int pos) {

    processo* pro = getProcessInPosition(fil, pos);
    processo* proAnt = getProcessInPosition(fil, pos-1);

    if (pro == fil->primeiro) {
        if (pro->prox != NULL) {
            fil->primeiro = pro->prox;
        }

    }
    if (pro == fil->ultimo) {
        if (proAnt != NULL) {
            fil->ultimo = proAnt;
        }
    }

    if (proAnt != NULL) {
        proAnt->prox = pro->prox;
    }

    fil->tamanho--;
    free(pro);

}

void printAll(fila* fil, int ciclos) {
    int i;

    printf("[%d]\n", ciclos);
    for(i=0; i<fil->tamanho; i++) {
        processo* pro = getProcessInPosition(fil, i);
        printf("[%d] ciclos = %d, prioridade = %d\n", pro->id, pro->ciclos, pro->prioridade);
    }
}

int main() {

    int ids = 0;
    fila fil;

    iniciarFila(&fil);

    srand(time(NULL));
    int i;
    for(i=0; i<(rand()%5)+1;i++) {
        adicionarElemento(&fil, (rand()%5)+1, ids, (rand()%3)+1);
        ids++;
    }


    processo* pros = getProcessInPosition(&fil, getHigherPriorityProcessPos(&fil));

    int contador = 0;
    int ciclos = 50;

    while(ciclos != 0) {

        pros->ciclos--;

        if (pros->ciclos == 0)
            removerElementoNaPosicao(&fil, getHigherPriorityProcessPos(&fil));

        contador++;

        if (contador == 3) {
            contador = 0;

            for(i=0; i<(rand()%5)+1; i++) {
                adicionarElemento(&fil, (rand()%5)+1, ids, (rand()%3)+1);
                ids++;
            }
        }

        ciclos--;

        printAll(&fil, 50-ciclos);
        printf("\n\n\n");

        pros = getProcessInPosition(&fil, getHigherPriorityProcessPos(&fil));
    }

    printAll(&fil, 999);


    return 0;
}


