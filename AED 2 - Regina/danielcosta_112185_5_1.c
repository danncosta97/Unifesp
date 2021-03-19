//Daniel Costa 112185
//AED 2 Regina 2018.1 Exercicio 5 (Hash)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct no{
    int chave;
    struct no *prox;
}tipo_no;

typedef struct hash{
    tipo_no *primeiro,*ultimo;
}tipo_hash;

void inicia_hash(tipo_hash **h,int tmh){
    int i;

    for(i=0;i<tmh;i++){
        h[i]=malloc(sizeof(tipo_hash));
        h[i]->primeiro=NULL;
        h[i]->ultimo=NULL;
    }
}

tipo_no* cria_no(int k){
    tipo_no *n = (tipo_no*)malloc(sizeof(tipo_no));
    n->chave=k;
    n->prox=NULL;
    return n;
}

void insere_hash(tipo_hash *h[], int k,int tmh){
    int index = k%tmh;
    tipo_no *n = cria_no(k);

    if(h[index]->primeiro==NULL){
        h[index]->primeiro=n;
        h[index]->ultimo=n;
    }
    else{
        h[index]->ultimo->prox=n;
        h[index]->ultimo=h[index]->ultimo->prox;
    }
}

int pesquisa_hash(tipo_hash *h[],int k,int tmh){
    int index = k%tmh;
    tipo_no *n = h[index]->primeiro;

    while((n!=NULL) && (n->chave!=k)){
        n=n->prox;
    }

    if(n==NULL){
        return 0;
    }
    return 1;
}

void remove_hash(tipo_hash *h[],int k,int tmh){
    int index = k%tmh;
    tipo_no *n = h[index]->primeiro;
    tipo_no *b = h[index]->primeiro;

    while((n!=NULL) && (n->chave!=k)){
        b=n;
        n=n->prox;
    }

    if (n==h[index]->primeiro){
        h[index]->primeiro=n->prox;
        free(n);
    }
    else{
        b->prox=n->prox;
        free(n);
    }
}

void print(tipo_hash *h[],int tmh){
    int i=0;

    tipo_no *n;

    for(i=0;i<tmh;i++){
        n = h[i]->primeiro;
        printf("[%d]",i);
        while(n!=NULL){
            printf(" %d",n->chave);
            n=n->prox;
        }
        printf("\n");
    }
}

int main(){
    int i,key,tmh,qtd;

    scanf("%d",&tmh);
    scanf("%d",&qtd);

    tipo_hash **h = malloc(sizeof(tipo_hash)*tmh);

    inicia_hash(h,tmh);

    for(i=0;i<qtd;i++){
        scanf("%d", &key);
        insere_hash(h,key,tmh);
    }

    scanf("%d", &key);
    if(pesquisa_hash(h,key,tmh)==0){
        insere_hash(h,key,tmh);
    }
    else{
        remove_hash(h,key,tmh);
    }

    print(h,tmh);
return 0;
}



