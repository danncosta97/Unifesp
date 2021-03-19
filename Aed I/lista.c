#include <stdio.h>
#include "lista.h"

#define N 100
int i=0;
void Inicializa(tipoListaES *listaAux)



{
// zera a lista
    listaAux->tamanhoLista =0;
    for (int i=0; i<N; i++)
        listaAux->lista[i]=0;
// inicializa o último
    listaAux->ultimo = 0;
}
void Insira(tipoListaES *listaAux)
{
    // atualiza a lista
    listaAux->tamanhoLista++;
// insere elemento ao final da lista
    scanf("%d", &listaAux->lista[listaAux->tamanhoLista-1]);
// atualiza o último
    listaAux->ultimo = listaAux->tamanhoLista-1;
}
void Imprima(tipoListaES *listaAux)
{
    for(int i=0;i<listaAux->tamanhoLista;i++)
    {
        printf("%d",listaAux->lista[i]);
    }
}
