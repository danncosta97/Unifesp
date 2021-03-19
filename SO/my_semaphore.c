#define _GNU_SOURCE
#include <stdlib.h>
#include <dlfcn.h>
#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#define EDGES 6
int (*real_sem_wait)(sem_t *) = NULL;
int (*real_sem_post)(sem_t *) = NULL;



///-----------------------------------------------------------------------------------------------------------

typedef struct {
    long first;
    long second;
} edge;

const unsigned int order = 6; /* Vertices */
const unsigned int n = 6; /* Edges */
unsigned int c;

int i = 0;
//edge *edges = malloc(n*sizeof(edge));
edge edges[EDGES];






static unsigned int cyclic_recursive(const edge *edges, unsigned int n, unsigned int *visited,
        unsigned int order, unsigned int vertex, unsigned int predecessor)
{
    unsigned int i;
    unsigned int cycle_found = 0;
    visited[vertex] = 1;
    for (i = 0; i < n && !cycle_found; i++) {
        if (edges[i].first == vertex || edges[i].second == vertex) {
            /* Adjacent */
            const unsigned int neighbour = edges[i].first == vertex ?
                    edges[i].second : edges[i].first;
            if (visited[neighbour] == 0) {
                /* Not yet visited */
                cycle_found = cyclic_recursive(edges, n, visited, order, neighbour, vertex);
            }
            else if (neighbour != predecessor) {
                /* Found a cycle */
                cycle_found = 1;
            }
        }
    }
    return cycle_found;
}

unsigned int cyclic(const edge *edges, unsigned int n, unsigned int order)
{
    unsigned int *visited = calloc(order, sizeof(unsigned int));
    unsigned int cycle_found;
    if (visited == NULL) {
        return 0;
    }
    cycle_found  = cyclic_recursive(edges, n, visited, order, 0, 0);
    free(visited);
    return cycle_found;
}

///-----------------------------------------------------------------------------------------------------------

void insere_aresta(long t, long s){

  edges[i].first = t;
  edges[i].second = s;
  i++;

}


int sem_wait(sem_t *sem){         //quando o processo chamar o sem_wait, ele vai capturar a aplicacao e executar esse semwait

  if(!real_sem_wait){
    real_sem_wait = dlsym(RTLD_NEXT,"sem_wait");       //chamando a sem_wait original, aqui tera o tratamento previo
  }
  printf("Dentro da caralha da sem_wait(%p)...\n", sem);




  insere_aresta((long) pthread_self(), (long) sem);

  if(cyclic(edges, n, order)){

    printf("Deu muita bosta\n");
    return -1;

  }

/*  //qual o recurso em questão : semaforo
    //processo: pthread_self()

    insere_arco(G, p, r)  grafo G processo P requisitando R
    if(existe_ciclo(G)){ tem deadlock
      remove_arco(g,p,r);
      errno = X;
      return -1;
   }

   aqui pode prosseguir...
*/

   return(real_sem_wait(sem));

}


int sem_post(sem_t *sem){

  if(!real_sem_post){
    real_sem_post = dlsym(RTLD_NEXT,"sem_post");
  }

  printf("Dentro do sem_post\n");

  return(real_sem_post(sem));

}
