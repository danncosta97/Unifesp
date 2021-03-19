#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>


#define PENSANDO 0
#define FOME 1
#define COMENDO 2

#define ESQ(i) (i+1)%N
#define DIR(i) (i-1+N)%N

#define N 6

struct filo_t{
	int i;
	pthread_t ti;
	int estado;
	sem_t s;
};

struct filo_t f[N];
sem_t mutex;

void pode_pegar(int i){
	if(f[i].estado == FOME &&
	   f[ESQ(i)].estado != COMENDO &&
	   f[DIR(i)].estado != COMENDO)
	{
		f[i].estado = COMENDO;
		sem_post(&f[i].s);
	}
}

void deixa_garfos(int i){
	sem_wait(&mutex);
	f[i].estado = PENSANDO;
	pode_pegar(ESQ(i));
	pode_pegar(DIR(i));
	sem_post(&mutex);
}

void pega_garfos(int i){
	sem_wait(&mutex);
	f[i].estado = FOME;
	pode_pegar(i);
	sem_post(&mutex);
	sem_wait(&f[i].s);
}


void pensando(int i){
	printf("Filo %d PENSANDO\n", i);
	fflush(stdout);
}

void comendo(int i){
	printf("Filo %d COMENDO\n", i);
	fflush(stdout);
}

void *filosofo(void *args){
	int i = *(int *)args;
	while(1) {
		pensando(i);
		pega_garfos(i);
		comendo(i);
		Sleep(2000);
		deixa_garfos(i);
	}
	pthread_exit(NULL);
}

void init(void){
	sem_init(&mutex, 0, 1);
	int k;
	for(k=0; k<N; k++){
		f[k].i = k;
		f[k].estado = PENSANDO;
		sem_init(&f[k].s, 0, 0);
	}
}

int main(int argc, char **argv){
	int k;
	init();
	for (k=0; k<N; k++){
		pthread_create(&f[k].ti,
			NULL,
			filosofo,
			&f[k].i);
	}
	for (k=0; k<N; k++){
		pthread_join(f[k].ti, NULL);
	}
	return 0;
}
