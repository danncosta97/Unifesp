#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>
#include <windows.h>

sem_t s_room;

#define R_EMPTY 0
#define R_WITH_X 1
#define R_WITH_Y 2

#define OUTSIDE 0
#define INSIDE 1

#define N 5

int R_STATE;
int r=0;
int aux=0;

struct person{
    int id;
    char type;
    int state;
};
struct person gp[N];

void entrar(int i){
    if(gp[i].type=='x' && r==0){
        R_STATE=R_WITH_X;
    }
    if(gp[i].type=='y' && r==0){
        R_STATE=R_WITH_Y;
    }

    sem_wait(&s_room);
    if(gp[i].type=='x' && R_STATE==R_WITH_X && gp[i].state==0){
        printf("\nUsuario %d do grupo %c ENTROU", i, gp[i].type);
        //sem_post(&s_room);
        gp[i].state=1;
      //  r++;
    }
    if(gp[i].type=='y' && R_STATE==R_WITH_Y && gp[i].state==0){
        printf("\nUsuario %d do grupo %c ENTROU", i, gp[i].type);
        //sem_post(&s_room);
        gp[i].state=1;
       // r++;
    }
    r++;
    sem_post(&s_room);

}

void ser_ouvido(int i){
    if(gp[i].state==1){
        printf("\nUsuario %d do grupo %c ESTA SENDO OUVIDO", i, gp[i].type);
        //Sleep(((rand()%5)+3)*1000);
    }
}

void sair_da_sala(int i){
    if(gp[i].state==1){
        printf("\nUsuario %d do grupo %c SAIU", i, gp[i].type);
        gp[i].state=0;
        //sem_wait(&s_room);
    }
    sem_wait(&s_room);
}

void *person_routine(void *args){
    int i = *(int*)args;
    while(1){
        //sem_wait(&s_room);
        entrar(i);
        ser_ouvido(i);
        sair_da_sala(i);
        sem_post(&s_room);
        r--;
    }
}



void *moderator(){
    while(1){
        //sem_wait(&s_room);
        sem_getvalue(&s_room,&aux);
        if(aux==1){
            R_STATE=R_EMPTY;
        }

        if(R_STATE==R_WITH_X){
            printf("\nGroup X is talking");
        }
        if(R_STATE==R_WITH_Y){
            printf("\nGroup Y is talking");
        }

        if(R_STATE==0){
            printf("\nEMPTY");
        }

        fflush(stdout);
        //Sleep(500);
    }
}



void init(){
    sem_init(&s_room, 0, 1);
}

void init_person(){
    for (int i=0; i<N/2; i++) {
        gp[i].id=i;
        gp[i].state=0; //waiting
        gp[i].type='x';
    }
    for (int i=N/2; i<N; i++) {
        gp[i].id=i;
        gp[i].state=0; //waiting
        gp[i].type='y';
    }
}

int main(){

    pthread_t mod;
    pthread_t p[5];
    init();

    init_person();

    pthread_create(&mod, NULL, moderator, NULL);

    for (int i=0; i<N; i++) {
        pthread_create(&p[i], NULL, person_routine, &gp[i].id);
    }

    pthread_join(mod,NULL);
    for (int i=0; i<N; i++) {
        pthread_join(p[i],NULL);

    }

}
