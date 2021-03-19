#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>
#include <windows.h>

sem_t s_room;
sem_t s_moderator;
sem_t s_person;

#define R_EMPTY 0
#define R_WITH_X 1
#define R_WITH_Y 2

#define OUTSIDE 0
#define INSIDE 1

#define N 5

int R_STATE;
char syntax_helper[2]={'x','y'};
int aux;

struct person{
    int id;
    char type;
    int state;
};
struct person gp[N];

//um indivíduo só sai coma chegada de outro e só entra
//caso uma pessoa do mesmo grupo estiver lá

int k=-1;
void *person_routine(void *args){
    while(1){
    int i = *(int*)args;
    //printf("\nPerson %d from group %c", gp[i].id, gp[i].type);
    if(gp[i].type=='x' && R_STATE==R_EMPTY){
        R_STATE=R_WITH_X;
        //sem_post(&s_moderator);
    }
    if(gp[i].type=='y' && R_STATE==R_EMPTY){
        R_STATE=R_WITH_Y;
        //sem_post(&s_moderator);
    }

    if(gp[i].type=='x' && R_STATE==R_WITH_X && gp[i].state==0){
        sem_post(&s_room);
        //sem_post(&s_moderator);
        //(&s_person);
        gp[i].state=1;
        printf("\nPerson %d from group %c ENTERED", gp[i].id, gp[i].type);
        Sleep(rand()%5*1000);
        gp[i].state=0;
        sem_wait(&s_room);
        printf("\nPerson %d from group %c HAS GONE", gp[i].id, gp[i].type);
        Sleep(rand()%5*1000);
    }
    else if(gp[i].type=='y' && R_STATE==R_WITH_Y && gp[i].state==0){
        sem_post(&s_room);
        //sem_post(&s_moderator);
        //sem_post(&s_person);
        gp[i].state=1;
        printf("\nPerson %d from group %c ENTERED", gp[i].id, gp[i].type);
        Sleep(rand()%5*1000);
        gp[i].state=0;
        sem_wait(&s_room);
        printf("\nPerson %d from group %c HAS GONE", gp[i].id, gp[i].type);
        Sleep(rand()%5*1000);
    }
    else{
        printf("\nPerson %d from group %c WAITING", gp[i].id, gp[i].type);
        gp[i].state=0;
        Sleep(500);
    }
    Sleep(500);
    //sem_getvalue(&s_room,&aux);

    }
}

void entrar(){
    if()
    printf("Usuario %d do grupo %c ENTROU");
}

void ser_ouvido(){
    printf("Usuario %d do grupo %c ESTÁ SENDO OUVIDO");
    Sleep(rand()%5*1000);
}

void sair_da_sala(){

}

void *moderator(){
    while(1){
        //sem_wait(&s_moderator);
        //Sleep(1000+rand()%2*1000);
        //sem_wait(&s_person);
        sem_getvalue(&s_room,&aux);
        //if((aux)==0){
         //  printf("\nmoderator waiting");
        //}
        if(aux==0){
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
        Sleep(1000);
        //sem_wait(&s_moderator);
    }
}



void init(){
    sem_init(&s_room, 0, 0);
    sem_init(&s_moderator, 0, 0);
    sem_init(&s_person, 0, 0);
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

