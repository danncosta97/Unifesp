#include <stdio.h>
#include <stdlib.h>

struct info{
    char caract;
    struct letra *prox;
    struct letra *ant;
};
typedef struct info tipo_letra;

struct ldde{
    tipo_letra *primeiro;
    tipo_letra *ultimo;
    int tamanhoLista;
};
typedef struct ldde tipo_ldde;

/******************************************************************/

void inicializa_lista (tipo_ldde *listaAux){
    listaAux->primeiro = NULL;
    listaAux->ultimo = NULL;
    listaAux->tamanhoLista = 0;
}

void insere_string (tipo_ldde *listaAux){
    char frase[100];

    scanf("%s", frase);

    int i, tmh;

    tipo_letra *nova_letra = (tipo_letra*) malloc(sizeof(tipo_letra));

    tmh = strlen(frase);

    for (i=0;i<tmh;i++){

        if (listaAux->tamanhoLista == 0){
            nova_letra->caract = frase[i];
            nova_letra->prox = NULL;
            nova_letra->ant = NULL;
            listaAux->primeiro = nova_letra;
            listaAux->ultimo = nova_letra;
        }

        else{
            nova_letra->caract = frase[i];
            nova_letra->prox = NULL;
            nova_letra->ant = listaAux->ultimo;
            listaAux->ultimo->prox = nova_letra;
            listaAux->ultimo = nova_letra;
        }
    }
    listaAux->tamanhoLista++;

    int j;
    char stringinvertida[100];

    for (j=0;j<listaAux->tamanhoLista;j++){
        stringinvertida[j] = listaAux->ultimo->caract;
    }
    printf ("%s", stringinvertida);
}

void imprime_invertido(tipo_ldde *listaAux){
    int j;
    char stringinvertida[100];

    for (j=0;j<listaAux->tamanhoLista;j++){
        stringinvertida[j] = listaAux->ultimo;
    }
    printf ("%s", stringinvertida);
}
/*********************************************************************/

int main(){
    tipo_ldde listaAux;

        void inicializa_lista(listaAux);

        void insere_string (listaAux);

        void imprime_invertido (listaAux);

return 0;
}
