//Daniel Costa   112185   AED Noturno 2017.1

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#define INF INT_MAX
#define MAX 1024

typedef struct stackItem {
    int value;
    struct stackItem *next;
} stackItem;

typedef struct {
    stackItem *top;
} StackD;

void stackInit(StackD *stack) {
    stack->top = NULL;
}

int stackEmpty(StackD *stack) {
    if (stack->top == NULL)
        return 1;
    return 0;
}

void push(StackD *stack, int ch) {
  stackItem *newStackItem = (stackItem*)malloc(sizeof(stackItem));
  if (!newStackItem) {
    exit(-1);
  }
  newStackItem->value = ch;
  newStackItem->next = stack->top;
  stack->top = newStackItem;
}

int pop(StackD *stack) {
  int c;

  if (stackEmpty(stack)) {
    return -1;
  }

  stackItem *paux;
  paux = stack->top;
  stack->top = paux->next;
  c = paux->value;
  free(paux);

  return c;
}


typedef struct adjlist_node {
  int vert;
  int cost;
  struct adjlist_node *next;
} adjlist;

typedef struct graph_header {
  unsigned int size;
  adjlist **adj;
  int *info;
} graph;

graph *initGraph(unsigned int nvert) {
  graph *G;
  int i;
  G = (graph *)malloc(sizeof(graph));
  G->adj = (adjlist **)malloc(nvert * sizeof(adjlist*));
  for (i = 0; i < nvert;i++) G->adj[i] = NULL;
  G->info = (int *)malloc(nvert * sizeof(int));
  G->size = nvert;
  return G;
}

void initVertex(graph *G, unsigned int i, int data) {
  G->info[i] = data;
}

void graphAddEdge(graph* G, int v, int w, int weight) {
  adjlist *L;
  L = (adjlist*)malloc(sizeof(struct adjlist_node));
  L->vert = w;
  L->cost = weight;
  if (G->adj[v] == NULL) {
    L->next = G->adj[v];
    G->adj[v] = L;  }
  else {
    adjlist *N;
    N = G->adj[v];
    if (L->vert < N->vert) {
      L->next = G->adj[v];
      G->adj[v] = L;
    } else {
      while (N->next) {
	if (L->vert < N->next->vert) {
	  break;
	}
	N = N->next;
      }
      L->next = N->next;
      N->next = L;
    }
  }
}



void topologicalSortUtil(graph* G, int v, int visited[], StackD *stack) {

  visited[v] = 1;


  adjlist *L = G->adj[v];
  while (L) {
    if (!visited[L->vert])
      topologicalSortUtil(G, L->vert, visited, stack);
    L = L->next;
  }


  push(stack, v);
}


void relax(int u, int v, int weightEdge, int *dist,int restricao) {
  if ((dist[v] > dist[u] + weightEdge) && (weightEdge <= restricao))
    dist[v] = dist[u] + weightEdge;
}



void shortestPath(graph* G, int s,int restricao) {
  StackD Stack;
  int dist[MAX];

  stackInit(&Stack);


  int visited[MAX];
  int i;
  for (i = 0; i < G->size; i++)
    visited[i] = 0;




  for (i = s; i < G->size; i++)
    if (visited[i] == 0)
      topologicalSortUtil(G, i, visited, &Stack);




  for (i = 0; i < G->size; i++)
    dist[i] = INF;
  dist[s] = 0;

  adjlist *L;


  while (stackEmpty(&Stack) == 0) {

    int u = pop(&Stack);
    L = G->adj[u];


    if (dist[u] != INF) {
      while (L) {

	relax(u, L->vert, L->cost, dist, restricao);
	L = L->next;
      }
    }
  }

 for (i = 0; i < G->size; i++)
    if (dist[i]==INF);
    else printf("%d ", dist[i]);
  printf("\n");
}



int main()
{

 int V,restricao,N,M;

 scanf("%d",&V);

 scanf("%d",&restricao);

 scanf("%d %d",&N,&M);

 int v1,v2,peso;

 graph* g = initGraph(N);

 int i;

    for(i=0;i<M;i++){

        scanf("%d %d %d",&v1,&v2,&peso);

        graphAddEdge(g,v1,v2,peso);
    }



  shortestPath(g,V,restricao);

  return 0;
}
