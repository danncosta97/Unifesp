//Daniel Costa 112185
//Judge 02 PAA Integral 2019
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

int counter=0;
int pos=0;

struct node{
    int vertex;
    struct node* next;
};

struct node* createNode(int v);

struct Graph{
    int numVertices;
    int* visited;
    int control;
    struct node** adjLists;

int DFS(struct Graph* g, int vertex, int initial) {
        struct node* adjList = g->adjLists[vertex];
        struct node* temp = adjList;

        //printf("Visited %d \n", vertex);

        while(temp!=NULL) {
            //printf("here01");
            if(temp->vertex==initial){
                    //printf("cycle detected");
                    g->control=1;
                    break;
            }
            int connectedVertex = temp->vertex;

            if(g->visited[connectedVertex] == 0) {
                g->visited[connectedVertex]=1;
                    //printf("here02");
                DFS(g, connectedVertex, initial);
            }

            temp = temp->next;
        }
        if(g->control==1){
            return  counter++;
        }
        else
            return 0;
}

void DFSlongest(struct Graph* g, int vertex, int initial, int *cycle) {
        struct node* adjList = g->adjLists[vertex];
        struct node* temp = adjList;
        cycle[pos]=vertex+1;
        pos++;
        //printf("%d ", vertex+1);

        while(temp!=NULL) {
            if(temp->vertex==initial){
                    break;
            }
            int connectedVertex = temp->vertex;

            if(g->visited[connectedVertex] == 0) {
                g->visited[connectedVertex]=1;
                DFSlongest(g, connectedVertex, initial, cycle);
            }
            temp = temp->next;
        }
}


struct node* createNode(int v){
    struct node* newNode = malloc(sizeof(struct node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

struct Graph* createGraph(int vertices){
    struct Graph* g = malloc(sizeof(struct Graph));
    g->numVertices = vertices;
    g->control=0;

    g->adjLists = malloc(vertices * sizeof(struct node*));

    g->visited = malloc(vertices * sizeof(int));

    int i;
    for (i = 0; i < vertices; i++) {
        g->adjLists[i] = NULL;
        g->visited[i] = 0;
    }
    return g;
}

void addEdge(struct Graph* g, int src, int dest){
    struct node* newNode = createNode(dest);
    newNode->next = g->adjLists[src];
    g->adjLists[src] = newNode;
}

void printGraph(struct Graph* g){
    int v;
    for (v = 0; v < g->numVertices; v++){
        struct node* temp = g->adjLists[v];
        printf("\n Adjacency list of vertex %d\n ", v);
        while (temp){
            printf("%d -> ", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}

void quickSort(int *cycle,int left,int right){
   int i=0,j=0,p=0,temp=0;

   if(left<right){
      p=left;
      i=left;
      j=right;

      while(i<j){
         while(cycle[i]<=cycle[p]&&i<right){
            i++;
         }
         while(cycle[j]>cycle[p]){
            j--;
        }
         if(i<j){
            temp=cycle[i];
            cycle[i]=cycle[j];
            cycle[j]=temp;
         }
      }

      temp=cycle[p];
      cycle[p]=cycle[j];
      cycle[j]=temp;
      quickSort(cycle,left,j-1);
      quickSort(cycle,j+1,right);
   }
}


int main(){
    int i=0,j=0,k=0,qtd=0,s=0,d=0,count=0,large=0,longestv=-1;
    scanf("%d",&qtd);
    struct Graph* g = createGraph(qtd);

    struct timeval stop, start;


    for (i=0;i<qtd;i++){
        scanf("%d %d",&s,&d);
        addEdge(g,s-1,d-1);
    }

    //printGraph(g);
    //gettimeofday(&start, NULL);
    //search the vertex with longest cycle
    for (i=0;i<qtd;i++){
        counter=0;
        g->control=0;
        k=DFS(g,i,i);
        if(large<k){
            longestv=i;
            large=k;
        }
        for (j=0;j<qtd;j++) {
            g->visited[j] = 0;
        }
        if(large+1>=qtd-i){
            break;
        }
    }
    if(longestv>=0){
        int *cycle=calloc(large+1,sizeof(int));
        DFSlongest(g,longestv,longestv,cycle);
        quickSort(cycle,0,large);
        //printf("\n\n");
        //gettimeofday(&stop, NULL);
        for (j=0;j<large+1;j++) {
            printf("%d ",cycle[j]);
        }

        //printf("\nDuration MS %.3f\n",
           //((double) (stop.tv_sec - start.tv_sec) * 1000 +
           //(double) (stop.tv_usec - start.tv_usec) / 1000));
    }

    return 0;
}
