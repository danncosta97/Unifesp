//Daniel Costa 112185 AED NOTURNO 2017.1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct No{
    char nome[16];
    int indice;
}TipoNo;

typedef struct lista{
    TipoNo listaestatica[1024];
    int qtd;
}TipoLista;

typedef struct grafo_mtx_adj{
    TipoLista listagraf;
    long int mtxadj[32][32];
}TipoGrafoMtxAdj;

int insere_no_lista(TipoLista *listaAux, char *nome_void){

    if (listaAux->qtd == 1024){
        return -1;
    }
    else{
        strcpy(listaAux->listaestatica[listaAux->qtd].nome,nome_void);
        listaAux->listaestatica[listaAux->qtd].indice = listaAux->qtd;
        listaAux->qtd++;
        return 1;
    }
}

int verifica_nome (TipoLista *listaAux, char *nome_void){
    int i;

    for (i=0;i<listaAux->qtd;i++){
        if(strcmp(listaAux->listaestatica[i].nome, nome_void)==0){
            return 1;
        }
    }

    return 0;
}

int busca_no(TipoLista *listaAux, char *nome_void){
    int i;
    for(i=0;i<listaAux->qtd;i++){
        if(strcmp(listaAux->listaestatica[i].nome, nome_void)==0){
            return listaAux->listaestatica[i].indice;
        }
    }
    return -1;
}

int cria_aresta(TipoGrafoMtxAdj *grafo, char *nome1, char *nome2){

    int i1 = busca_no(&grafo->listagraf, nome1);
    int i2 = busca_no(&grafo->listagraf, nome2);

    if(i1 < 0|| i2 < 0){
        return -1;
    }
    else{
        grafo->mtxadj[i1][i2] = 1;
        grafo->mtxadj[i2][i1] = 1;
    }
    return 1;
}

void inicia_grafo(TipoGrafoMtxAdj *grafo){

    int i,j;

    grafo->listagraf.qtd=0;

    for(i=0; i<32; i++){
        for(j=0; j<32; j++){
            grafo->mtxadj[i][j]=0;
        }
    }
}

int main(){

    int i,j;

    TipoGrafoMtxAdj Grafo;

    inicia_grafo(&Grafo);

    char nome1[16], nome2[16];

    scanf("%s", nome1);
    insere_no_lista(&Grafo.listagraf, nome1);

    int V,E;
    scanf("%d %d", &V, &E);

    for(i=0;i<E;i++){

        for(j=0;j<16;j++){
            nome1[j]='\0';
            nome2[j]='\0';
        }

        scanf("%s %s", nome1, nome2);

        if(verifica_nome(&Grafo.listagraf,nome1)==0){
            insere_no_lista(&Grafo.listagraf, nome1);
        }

        if(verifica_nome(&Grafo.listagraf,nome2)==0){
            insere_no_lista(&Grafo.listagraf, nome2);
        }

        cria_aresta(&Grafo, nome1, nome2);
    }

    for(i=0; i<V; i++)
    {
        for(j=0; j<V; j++)
        {
           printf("%d ",Grafo.mtxadj[i][j]);
        }
        printf("\n");
    }

return 0;
}





