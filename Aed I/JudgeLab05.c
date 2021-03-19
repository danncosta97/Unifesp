#include <stdio.h>
#include <stdlib.h>

typedef struct info{

    int duracao;
    struct info *prox;
    struct info *ant;

}temp_lig;

typedef struct fila{

    int tamanho_fila;
    temp_lig *primeiro;
    temp_lig *ultimo;

}tipo_fila;

void inicia_fila (tipo_fila *filaAux){

    filaAux->primeiro=NULL;
    filaAux->ultimo=NULL;
    filaAux->tamanho_fila=0;

}

int lista_vazia (tipo_fila *filaAux){

    if ((filaAux->primeiro == filaAux->ultimo) && (filaAux->ultimo == NULL)){
        return 1;
    }
    else{
        return 0;
    }

}

void insere_ultimo (tipo_fila *filaAux){

    int duracao;

    temp_lig *nlig = (temp_lig*) malloc (sizeof(temp_lig));

    printf ("digite o tempo da chamada");
    scanf("%d", &duracao);

    nlig->duracao = duracao;

    if (lista_vazia (filaAux) == 1){
        nlig->prox = nlig;
        nlig->ant = nlig;
        filaAux->primeiro = nlig;
        filaAux->ultimo = nlig;
    }
    else{
        nlig->prox = filaAux->primeiro;
        nlig->ant = filaAux->ultimo;
        filaAux->primeiro->ant = nlig;
        filaAux->ultimo->prox = nlig;
        filaAux->ultimo = nlig;
    }

    filaAux->tamanho_fila++;
}

void retira_primeiro (tipo_fila *filaAux){

    filaAux->primeiro->prox->ant = filaAux->ultimo;
    filaAux->ultimo->prox = filaAux->primeiro->prox;
    filaAux->primeiro = filaAux->primeiro->prox;

}

int main(){

    int i, qtd_vend, qtd_lig, duracao, v[100], cont[100];

    for(i=0;i<100;i++){
        cont[i] = 0;
    }

    tipo_fila fila_main;

    inicia_fila (&fila_main);

    printf("digite qtd vends e qtd de ligs");
    scanf("%d %d", &qtd_vend, &qtd_lig);

    for(i=0;i<qtd_lig;i++){

        insere_ultimo(&fila_main);
    }

    for(i=0;i<qtd_vend;i++){
        v[i] = fila_main.primeiro->duracao;
        cont[i]++;
        retira_primeiro(&fila_main);
        qtd_lig--;
        if(qtd_lig==0)
            break;
    }
    printf("passou");
    do{
        for(i=0;i<qtd_vend;i++){
            if (v[i] == 0){
                v[i] == fila_main.primeiro;
                cont[i]++;
                qtd_lig--;
            }
        }
        for(i=0;i<qtd_vend;i++){
            v[i]--;
        }

    }while (qtd_lig>0);

    for(i=0;i<qtd_vend;i++)
        printf("\n%d %d", i+1, cont[i]);

return 0;
}
