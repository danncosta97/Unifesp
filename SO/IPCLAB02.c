//IPC - LAB02 SO 2019.1 Integral
//Daniel Costa 112185
//Lucas Daher 114830
//sleep() desativados

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>

int aux;
int room = 0;

sem_t s_room;


#define R_EMPTY 0
#define R_WITH_X 1
#define R_WITH_Y 2

#define OUTSIDE 0
#define INSIDE 1

#define N 10

int R_STATE;

struct person{
    int id;
    char type;
    int state;
};
struct person gp[N];

void entrar(int i){


    if(gp[i].type=='x' && R_STATE==R_EMPTY){
        R_STATE=R_WITH_X;
    }
    if(gp[i].type=='y' && R_STATE==R_EMPTY){
        R_STATE=R_WITH_Y;
    }

    if(gp[i].type=='x' && R_STATE==R_WITH_X && gp[i].state==0){
        room++;
        printf("\nUsuario %d do grupo %c ENTROU ---- quantidade na sala [%d]", i, gp[i].type, room);
        gp[i].state=1;


    }
    if(gp[i].type=='y' && R_STATE==R_WITH_Y && gp[i].state==0){
        room++;
        printf("\nUsuario %d do grupo %c ENTROU ---- quantidade na sala [%d]", i, gp[i].type, room);
        gp[i].state=1;


    }

}

void ser_ouvido(int i){
    if(gp[i].state==1){
        printf("\nUsuario %d do grupo %c ESTA SENDO OUVIDO", i, gp[i].type);
    }
}

void sair_da_sala(int i){
    if(gp[i].state==1){
        gp[i].state=0;
        room--;
        printf("\nUsuario %d do grupo %c SAIU ---- quantidade na sala [%d]", i, gp[i].type,room);

    }
}

void *person_routine(void *args){
    int i = *(int*)args;
    while(1){
        sem_wait(&s_room);
        entrar(i);
        sem_post(&s_room);
        ser_ouvido(i);
        sem_wait(&s_room);
        sair_da_sala(i);
        sem_post(&s_room);
        //sleep(rand()%10);
    }
}



void *moderator(){
    while(1){
        //sem_getvalue(&s_room,&aux);

        if(room==0){
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
        //sleep(1);
    }
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
    pthread_t p[N];


    sem_init(&s_room, 0, 1);

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
