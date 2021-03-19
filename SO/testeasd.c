#define _GNU_SOURCE
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>


struct node;

typedef struct elem {
	struct no* no;
	struct elem* prox;
} elem_t;

typedef struct lista {
	struct elem* inicio;
	int tamanho;
} list_t;

typedef struct no {
	pthread_t* linha;
	sem_t* sem;
	int tipo;
	int pintado;
	list_t* vizinhos;
} no_t;


list_t nos;

void insere_na_lista(list_t* lista, elem_t* elem) {
	elem_t* aux = lista->inicio;
	if (lista->inicio == NULL) {
		lista->inicio = elem;
	} else {
		while(aux->prox != NULL) {
			aux = aux->prox;
		}

		aux->prox = elem;
	}

	lista->tamanho++;
}

bool remove_da_lista(list_t* lista, no_t* no) {
	elem_t* aux = lista->inicio;
	while(aux != NULL && aux->prox != NULL) {

		if (aux->prox->no == no) {
			elem_t* libera = aux->prox;
			aux->prox = libera->prox;
			free(libera);
			lista->tamanho--;
			return true;
		}

		aux = aux->prox;
	}

	return false;
}

no_t* pega_no(int k, pthread_t* linha, sem_t* sem) {
	elem_t* aux = nos.inicio;

	while(aux != NULL) {

		if (aux->no->tipo == k && aux->no->linha == linha && aux->no->sem == sem) {
			return aux->no;
		}
		aux = aux->prox;
	}
}

void insere_no(int tipo, pthread_t* linha, sem_t* sem) {

	if(pega_no(tipo, linha, sem) != NULL)
		return;

	no_t* novo = (no_t*) malloc(sizeof(no_t));
	novo->tipo = tipo;
	novo->vizinhos = (list_t*) malloc(sizeof(list_t));
	novo->vizinhos->tamanho = 0;
	novo->vizinhos->inicio = NULL;
	novo->linha = linha;
	novo->sem = sem;
	novo->pintado = 0;

	elem_t* elem = (elem_t*) malloc(sizeof(elem_t));
	elem->no = novo;
	elem->prox = NULL;

	insere_na_lista(&nos, elem);

}



bool remover_no(int tipo, pthread_t* linha, sem_t* sem) {
	no_t* no = pega_no(tipo, linha, sem);

	elem_t* aux = nos.inicio;
	while(aux != NULL) {
		remove_da_lista(aux->no->vizinhos, no);
		aux = aux->prox;
	}

	remove_da_lista(&nos, no);
}

void criar_aresta(no_t* a, no_t* b) {
	elem_t* novo = (elem_t*) malloc(sizeof(elem_t));
	novo->no = b;
	novo->prox = NULL;
	insere_na_lista(a->vizinhos, novo);
}

void remover_aresta(no_t* a, no_t* b) {
	remove_da_lista(a->vizinhos, b);
}

void printa_grafo(no_t* a) {
	if (a->tipo == 0)
		printf("GRAFO [%lu]\n", a->linha);
	else
		printf("GRAFO [%lu]\n", a->sem);

	elem_t* aux = a->vizinhos->inicio;
	while(aux != NULL) {
		if (aux->no->tipo == 0)
			printf("-> CONECTA LINHA [%lu]\n", (long) aux->no->linha);
		else
			printf("-> CONECTA SEM [%lu]\n", (long) aux->no->sem);

		aux = aux->prox;
	}
}

bool ciclo(no_t* no, no_t* fim) {
	elem_t* aux = no->vizinhos->inicio;
	no_t* fi;

	if (no == fim)
		return true;

	if (no->pintado == 1)
		return false;

	no->pintado = 1;

	if (fim == NULL)
		fi = no;
	else
		fi = fim;

	while(aux != NULL) {
		if (ciclo(aux->prox, fi) == 1)
			return true;

		aux = aux->prox;
	}

	return false;
}

void tinner() {

	elem_t* aux = nos.inicio;

	while(aux != NULL) {
		aux->no->pintado = 0;
		aux = aux->prox;
	}
}

int main(int argc, char** argv) {

	long a = 1;
	long b = 2;
	long c = 3;

	printf("Valor %ld\n", &c);

	insere_no(0, &a, NULL);
	insere_no(0, &b, NULL);
	insere_no(1, NULL, &c);

	remover_no(0, &b, NULL);

	no_t* no1 = pega_no(0, &a, NULL);
	no_t* no2 = pega_no(1, NULL, &c);

	criar_aresta(no1, no2);

	printa_grafo(no1);
	no_t* no = pega_no(1, NULL, &c);
	printf("%ld\n", (long) no->sem);

	return 0;
}
