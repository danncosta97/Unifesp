#include<stdio.h>
#include<stdlib.h>
#define N 20

/*************Tad.h***************************************/

typedef struct Elemento{                             //Estrutura da lista estatica encadeada
    int info;
    int prox;
}elemento;

typedef struct Lista{
    int qnt;
    int primeiro;
    int ultimo;
    int pos_livre[N];
    elemento vet[N];
}lista;

void Inicia_lista (lista *l);
int  Procura_pos_livre(lista *l);
void Insere_elemento(lista *l,int elemento);
int  Retorna_pos_ant(lista *,int elemento_a_procurar);
void remove_elemento(lista *l,int pos_ant);
void Imprime(lista *l);

/*************Tad.c***************************************/

void Inicializa_Lista(lista *l){
    int i;
    l->qnt=0;
    l->primeiro=-1;
    l->ultimo=-1;
    for(i=0;i<N;i++){
        l->pos_livre[i]=1;                                 // 1 pos está vazia
        l->vet[i].prox=-1;
        l->vet[i].info=0;
    }
}
int Procura_pos_livre(lista *l){                           //na estatica como nao se alloca memoria a lista e inserida em um vetor e em um outro vetor e verificada se aquela posicao esta ocupada ou nao
    int i;
    for(i=0;i<N;i++){
        if(l->pos_livre[i]==1){
            return i;
        }
    }
    return -1;
}

void Insere_elemento(lista *l, int elemento){
    int pos;
    pos=Procura_pos_livre(l);                         // se a Procura_pos_livre retornar -1 quer dizer q a lista esta cheia
    if(pos==-1){
        printf("Lista Cheia");
    }
    else{
        if(l->qnt==0){
            l->primeiro=pos;
        }
        else{
            l->vet[l->ultimo].prox=pos;
        }
         l->ultimo=pos;
         l->vet[pos].prox=-1;
         l->vet[pos].info=elemento;
         l->pos_livre[pos]=0;
         l->qnt++;
    }
}

int Retorna_pos_ant(lista *l,int elemento_a_procurar){     // pos_ant e usada para achar o elemento a ser retirado por exemplo,para remover e preciso saber o anterior para reajustar os ponteiros
    int i,ant;
    ant=-1;
    for(i=l->primeiro;i!=-1;i=l->vet[i].prox){
        if(elemento_a_procurar == l->vet[i].info){
            return ant;
            break;
        }
        ant=i;
    }
    return -2;                                             // Elemento não encontrado
}

void remove_elemento(lista *l,int pos_ant){
    int aux,pos;
    pos=l->vet[pos_ant].prox;
    l->vet[pos_ant].prox=l->vet[pos].prox;
    l->vet[pos].info=0;
    l->vet[pos].prox=-1;
    l->pos_livre[pos]=1;
    l->qnt--;
}
void Imprime(lista *l){
    int i,cont=1;
    i=l->primeiro;
    while(i!=-1){
        printf("%d elemento e == %d\n",cont,l->vet[i].info);
        cont++;
        i=l->vet[i].prox;
    }
}
int main(){
    lista l;
    int a;
   //fazer qualquer operacao com os procedimentos acima

return 0;

}















































