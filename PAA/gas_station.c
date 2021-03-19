//Daniel Barbosa Silva Costa 112185
//PAA 2019.2 - Integral - Problema 05 (Extra via Moodle)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GAS_STATIONS 8

typedef struct tnode{
    int gas_num;
    int km_dist;
    struct node *next;
}node;

typedef struct lista{
    node *first;
    node *last;
    int tamanho;
}list;

void list_init(list *l){
    l->first=NULL;
    l->last=NULL;
    l->tamanho=0;
}

void insert_gas_station(list *l, int num, int km){

    node *n = (node*)malloc(sizeof(node));
    n->gas_num=num;
    n->km_dist=km;

    if(l->tamanho==0){
        n->next = NULL;
        l->first = n;
        l->last = n;
    }
    else{
        n->next=NULL;
        l->last->next = n;
        l->last = n;
        }
    l->tamanho++;
}

int gas_station_greedy(int *gas_station_dist, int max_dist, int gas_qtd, list *l){
    int last_gas_station=0,i=0;

    if(gas_station_dist[0]-last_gas_station > max_dist){
        printf("Impossible to start travelling! ");
        printf("\nNO SOLUTION");
        return 0;
    }
    for(i=1; i<gas_qtd; i++){
        if((gas_station_dist[i]-last_gas_station) > max_dist){
            insert_gas_station(l, i, gas_station_dist[i-1]);
            last_gas_station = gas_station_dist[i-1];
            if(gas_station_dist[i]-gas_station_dist[i-1] > max_dist){
                printf("Impossible to complete the travel! ");
                printf("Gas station %d[%dkm] unreachable\n",i+1,gas_station_dist[i]);
                printf("Can go until gas station %d[%dkm]\n",l->last->gas_num,l->last->km_dist);
                printf("\nPARTIAL SOLUTION: ");
                printf_list(l);
                return 0;
            }
        }
        //including last gas station at max_dist from last stop
        if(i==gas_qtd-1 && gas_station_dist[i]-gas_station_dist[i-1] == max_dist){
            insert_gas_station(l, i+1, gas_station_dist[i]);
        }
        //printf("In %d at %dkm \n", i, gas_station_dist[i]);
        //printf("Last stop at %dkm\n", last_gas_station);
    }
    return 1;

}

void printf_list(list *l){
    node *aux = l->first;

    while(aux!=NULL){
        printf("%d[%dkm] ", aux->gas_num, aux->km_dist);
        aux=aux->next;
    }

}

int main(int argc, char **argv){
    list l;
    list_init(&l);

    int max_dist=0;
    //printf("Autonomia do carro: \n");
    scanf("%d", &max_dist);

    int gas_qtd=0, i=0, ok=0;
    //printf("Quantidade de postos: \n");
    scanf("%d", &gas_qtd);

    int *gas_dist = (int*)calloc(gas_qtd,sizeof(int));
    for(i=0; i<gas_qtd; i++){
        scanf("%d", &gas_dist[i]);
    }

    if(gas_station_greedy(gas_dist, max_dist, gas_qtd, &l)){
        printf("SOLUTION: ");
        printf_list(&l);
    }

    return 0;
}

//-
