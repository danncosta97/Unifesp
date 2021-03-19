#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>

struct node{
    long value;
    struct node* next;
};

struct node* createNode(long v);

struct graph{
    int numVertices;
    int* visited;
    struct node** adjLists;
    int* map_aux;
};

struct graph* g;

sem_t t;

int control;
int k;
int listcounter;

struct node* createNode(long v)
{
    struct node* newNode = malloc(sizeof(struct node));
    newNode->value = v;
    newNode->next = NULL;
    return newNode;
}

int busca_profundidade(struct graph* g, long value) {
        int i=0;
        while(g->map_aux[i]!=value && i<g->numVertices-1){
            i++;
        }

        struct node* adjList = g->adjLists[i];
        struct node* temp = adjList;
        g->visited[i] = 1;
        printf("Visited %ld \n", value);

        while(temp!=NULL) {
            long connectedvalue = temp->value;
            i=0;
            while(g->map_aux[i]!=value && i<g->numVertices){
                i++;
            }
            if(g->visited[connectedvalue] == 0) {
                busca_profundidade(g, connectedvalue);
            }
            else return -1;

            temp = temp->next;
        }

    return 0;
}

int undo_busca_profundidade(struct graph* g, long value) {
        int i=0;
        while(g->map_aux[i]!=value && i<g->numVertices-1){
            i++;
        }

        struct node* adjList = g->adjLists[i];
        struct node* temp = adjList;
        g->visited[i] = 0;
        printf("Visited %ld \n", value);

        while(temp!=NULL) {
            long connectedvalue = temp->value;
            i=0;
            while(g->map_aux[i]!=value && i<g->numVertices){
                i++;
            }
            if(g->visited[connectedvalue] == 1) {
                busca_profundidade(g, connectedvalue);
            }

            temp = temp->next;
        }

    return 0;
}
struct graph* createGraph(long vertices)
{
    struct graph* g = malloc(sizeof(struct graph));
    g->numVertices = vertices;

    g->adjLists = malloc(vertices * sizeof(struct node*));

    g->visited = malloc(vertices * sizeof(long));

    g->map_aux = malloc(vertices * sizeof(long));

    long i;
    for (i = 0; i < vertices; i++) {
        g->adjLists[i] = NULL;
        g->visited[i] = 0;
        g->map_aux[i] = -1;
    }
    return g;
}

void addEdge(struct graph* g, long src, long dest)
{
    int i;
    i=0;
    while(g->map_aux[i]!=src && g->map_aux[i]!=-1){
        i++;
        if(g->numVertices==i) break;
    }

    if(g->numVertices==i){
        i=0;
        while(g->map_aux[i]!=-1){
            i++;
            if(g->numVertices==i) break;
        }

    }
    if(g->map_aux[i]==src){
        struct node* newNode = createNode(dest);
        newNode->next = g->adjLists[i];
        g->adjLists[i] = newNode;

    }else{
        struct node* newNode = createNode(dest);
        newNode->next = g->adjLists[i];
        g->adjLists[i] = newNode;
        g->map_aux[i] = src;
        listcounter++;
    }
}

void removeEdge(struct graph* g, long src, long trg)
{
    struct node* aux;

    int i=0;
    while(g->map_aux[i]!=src && g->map_aux[i]!=-1){
        i++;
        if(g->numVertices==i) break;
    }

    aux=g->adjLists[i];

    if(aux->next==NULL){
        g->adjLists[i]=NULL;
    }
    else{
        while(aux->next->value!=trg && aux->next!=NULL){
            aux=aux->next;
        }
    }

    if(aux!=NULL && aux->next!=NULL){
        aux->next=aux->next->next;
    }
}

void printGraph(struct graph* g)
{
    int v;
    for (v = 0; v < g->numVertices; v++)
    {
        struct node* temp = g->adjLists[v];
        printf("\n Adjacency list of value %d\n ", v);
        while (temp)
        {
            printf("%ld -> ", temp->value);
            temp = temp->next;
        }
        printf("\n");
    }
}

int main(){
	g = createGraph(10);
	printf("elk");
	k=0;
	listcounter=0;

    printGraph(g);
    busca_profundidade(g,200);

    control=1

    return 0;
}
