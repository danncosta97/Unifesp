#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

#define N 10
#define GROUPS_NUMBER 2

// Manager status
#define DOING_PAPERWORK 0
#define MANAGING_X 1
#define MANAGING_Y 2

// User status
#define INSIDE 0
#define OUTSIDE 1

typedef struct group {
    int group_id;
    sem_t mutex;
} group_t;

typedef struct user {
    int id;
    int group_id;
    int status;
    pthread_t ti;
} user_t;

typedef struct manager {
    int id;
    int status;
    int room;
    //pthread_t ti;
    sem_t mutex;
} manager_t;

manager_t* manager;
user_t* users;

sem_t* groups_mutex;

//manager_t manager;
//user_t users[N];

void showStatus(int status, int i) {
    if (status == 0) // Entrou
        printf("Entrou -> %d from group %d [%d]\n", i, users[i].group_id, manager->room);
    else // SAIU
        printf("Saiu   -> %d from group %d [%d]\n", i, users[i].group_id, manager->room);
}

void* user_func(void* arg) {
    int i = *(int*) arg;
    printf("Hello user %d from group %d\n", i, users[i].group_id);
    fflush(stdout);

    while(1) {

        // Verify if my team is being managed
        if (manager->status == users[i].group_id+1 && users[i].status == OUTSIDE) {
            //printf("[2] Hey %d && manager->status = %d && users[i].group_id+1 = %d\n", i, manager->status, users[i].group_id+1);
            //fflush(stdout);
            sem_wait(&manager->mutex);

            if (manager->status == users[i].group_id+1) { // If he is still managing my group, let's get in.
                manager->room = manager->room + 1;
                users[i].status = INSIDE;
            }

            sem_post(&manager->mutex);
        }

        // Verify if manager is doing some paper work.
        if (manager->status == DOING_PAPERWORK && users[i].status == OUTSIDE) {
            // This means that manager can see any user, so let's wait until he is able to return his updated status.
            sem_wait(&manager->mutex);

            if (manager->status == DOING_PAPERWORK) { // If he is still not managing any group, start managing my group.
                manager->status = users[i].group_id+1;
                manager->room = manager->room + 1;
                users[i].status = INSIDE;
                //printf("[1] Hey %d\n", i);
                //fflush(stdout);
            }

            sem_post(&manager->mutex);
        }

        if (users[i].status == INSIDE) { // I am inside, let's discuss some issues and get away as soon as possible.
            showStatus(0, i);
            //sleep(rand()%10);

            // Getting out
            sem_wait(&manager->mutex);
            manager->room = manager->room - 1;
            users[i].status = OUTSIDE;

            if (manager->room == 0) { // If manager's room is empty, change it's status.
                manager->status = 0;
            }

            sem_post(&manager->mutex);

            showStatus(1, i);
        }


    }

    pthread_exit(NULL);
}

void init() {
    users = (user_t*) malloc(N*sizeof(user_t));
    manager = (manager_t*) malloc(sizeof(manager_t));

    groups_mutex = (sem_t*) malloc(GROUPS_NUMBER*sizeof(sem_t));

    for (int i = 0; i<GROUPS_NUMBER; i++) {
        sem_init(&groups_mutex[i], 0, 0);
    }

    sem_init(&manager->mutex, 0, 1);
    //pthread_create(&manager->ti, NULL, manager_func, NULL);
    manager->room = 0;
    manager->status = 0;

    for (int i = 0; i<N; i++) {
        users[i].id = i;
        users[i].group_id = i%GROUPS_NUMBER;
        users[i].status = OUTSIDE;
        pthread_create(&users[i].ti, NULL, user_func, &users[i].id);
    }

}

void terminate() {
    //sleep(2);
}

int main(int argc, char** argv) {

    init();

    for (int i = 0; i<N; i++)
        pthread_join(users[i].ti, NULL);

    //pthread_join(manager->ti, NULL);

    terminate();

    return 0;
}
