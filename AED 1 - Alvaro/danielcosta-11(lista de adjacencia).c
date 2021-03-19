#include <stdio.h>
#include <stdlib.h>

typedef struct adjlist_node adjlist;

struct adjlist_node
{
    int vert; //vertice de ligacao
    adjlist *next;
};

typedef struct graph_header graph;
struct graph_header
{
    unsigned int size; //qde vertices
    adjlist **adj;
    int *info; //Info de cada nó // qualquer info
};

graph * initGraph(unsigned int nvert)
{
    int i;
    graph *G;

    G = (graph *) malloc(sizeof(graph));

    G->adj = (adjlist **) malloc(nvert*sizeof(adjlist*));

    for(i=0; i<nvert; i++){
        G->adj[i] = NULL;
    }

    G->info = (int *) malloc(nvert*sizeof(int));
    G->size = nvert;
    return G;
}

void initVertex(graph *G, unsigned int i, int data)
{
    G->info[i]=data;
}

void graphAddEdge(graph* G, int v, int w)
{
    adjlist *L;
    L = (adjlist*) malloc(sizeof(struct adjlist_node));
    L->vert = w;
    L->next = G->adj[v];
    G->adj[v] = L;
}

int graphHasEdge(graph* G, int v, int w)
{
    adjlist *L = G->adj[v];
    while(L != NULL)
    {
        if(L->vert == w) return 1;
        L = L->next;
    }
    return 0;
}

void showGraph(graph* G)
{
    int i, nvert = G->size;
    adjlist *L;
    for(i=0; i<nvert; i++)
    {
        printf("Vertice (%d) -> ", i);
        L = G->adj[i];
        while(L != NULL)
        {
            printf("%d ", L->vert);
            L = L->next;
        }
        printf("\n");
    }
}

/*************************************************************/
void BuscaEmProfundidadeUtil(graph *G, int v, int *visited){
    visited[v] = 1;
    printf("%d ", v);

    adjlist *ListaAdj = G->adj[v];

     while(ListaAdj){
        if (!visited[ListaAdj->vert]){
            BuscaEmProfundidadeUtil(G, ListaAdj->vert, visited);
        }
        ListaAdj = ListaAdj->next;
    }
}

void BuscaEmProfundidade(graph *G, int v){
    int *visited = (int*) malloc(G->size*sizeof(int));
    unsigned int i;

    for (i=0; i<G->size; i++){
        visited[i]=0;
    }

    BuscaEmProfundidadeUtil(G, v, visited);
    printf("\n");
}

/**************************************************************/
typedef struct tipoitemfila{
    int valor;
    struct tipoitemfila *prox;
}TipoItemFila;

typedef struct Fila{
    TipoItemFila *primeiro;
    TipoItemFila *ultimo;
    int tamanhofila;
}TipoFila;

void inicializarFila(TipoFila *FilaAux){
    FilaAux->primeiro=NULL;
    FilaAux->ultimo=NULL;
    FilaAux->tamanhofila=0;
}

int filaVazia (TipoFila *FilaAux){
    if(FilaAux->tamanhofila==0){
        return 1;
    }
    else{
        return 0;
    }
}

void inserirFila (TipoFila *FilaAux, int v){

    int i;

    TipoItemFila *aux = malloc (sizeof(TipoItemFila));

    aux->valor = v;

    i = filaVazia(FilaAux);

    if(i == 1){
        aux->prox=NULL;
        FilaAux->primeiro = aux;
        FilaAux->ultimo = aux;
    }
    else{
        aux->prox=NULL;
        FilaAux->ultimo->prox = aux;
        FilaAux->ultimo = aux;
    }

    FilaAux->tamanhofila++;
}

void removerFila (TipoFila *FilaAux){
    FilaAux->primeiro=FilaAux->primeiro->prox;
    FilaAux->tamanhofila--;
}

void BuscaEmLargura(graph *G, int v){
    int *visited = (int*) malloc(G->size*sizeof(int));
    unsigned int i;

    for(i=0;i<G->size; i++){
        visited[i]=0;
    }

    TipoFila fila;
    inicializarFila(&fila);

    visited[v]=1;

    inserirFila(&fila, v);

    adjlist *ListaAdj;

    while(filaVazia(&fila)==0){

        printf("%d ", fila.primeiro->valor);

        ListaAdj=G->adj[fila.primeiro->valor];

        removerFila(&fila);

        while(ListaAdj!=NULL){
            if(visited[ListaAdj->vert]==0){
                visited[ListaAdj->vert] = 1;
                v = ListaAdj->vert;
                inserirFila(&fila, v);
            }
            ListaAdj = ListaAdj->next;
        }
    }
}

int main(void){

    int VertInicial=0, nos=0, arestas=0, qtd=0, i=0, j=0, n1=0, n2=0;

    scanf("%d %d %d", &VertInicial, &nos, &arestas);

    graph *G = initGraph(nos);

    for(i=0;i<arestas;i++){
        scanf("%d %d", &n1, &n2);
        graphAddEdge(G, n1, n2);
    }

    for(i=0;i<nos;i++){

        adjlist *aux, *aux2;

        aux = G->adj[i];

        while(aux!=NULL){
            aux2=aux->next;
            while(aux2!=NULL){
                if(aux->vert > aux2->vert){
                    j = aux->vert;
                    aux->vert = aux2->vert;
                    aux2->vert = j;
                }
                aux2=aux2->next;
            }
            aux=aux->next;
        }
    }

    showGraph(G);
    printf("\n");
    BuscaEmLargura(G, VertInicial);
    printf("\n");
    BuscaEmProfundidade(G, VertInicial);

    return 0;
}
