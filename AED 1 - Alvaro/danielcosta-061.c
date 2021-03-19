#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct elemento{
    char letra;
    int quantidade;
    struct elemento *prox;
    struct elemento *ant;
}tipo_elemento;

typedef struct lista{
    tipo_elemento *primeiro;
    tipo_elemento *ultimo;
    int tamanho_lista;
}tipo_lista;

void inicia_lista(tipo_lista *lista_Aux){
    lista_Aux->primeiro=NULL;
    lista_Aux->ultimo=NULL;
    lista_Aux->tamanho_lista = 0;
}

void insere(tipo_lista *lista_Aux, char letter, int qtd){

    tipo_elemento *novo_elemento = calloc(1, sizeof(tipo_elemento));
    novo_elemento->letra = '\0';
    novo_elemento->quantidade = 0;
    novo_elemento->letra = letter;
    novo_elemento->quantidade = qtd;

    if(lista_Aux->tamanho_lista == 0){
        novo_elemento->prox = NULL;
        novo_elemento->ant = NULL;
        lista_Aux->primeiro = novo_elemento;
        lista_Aux->ultimo = novo_elemento;
    }
    else{
        novo_elemento->ant = lista_Aux->ultimo;
        novo_elemento->prox = NULL;
        lista_Aux->ultimo->prox = novo_elemento;
        lista_Aux->ultimo = novo_elemento;
    }
    lista_Aux->tamanho_lista++;
}

void remove_ruido(tipo_lista *lista_Aux, tipo_elemento *elemento_remove){

    if(elemento_remove->ant==NULL){
        lista_Aux->primeiro = elemento_remove->prox;
        lista_Aux->primeiro->ant = NULL;
        lista_Aux->primeiro->quantidade++;
        free(elemento_remove);
    }
    if(elemento_remove->prox==NULL){
        lista_Aux->ultimo = elemento_remove->ant;
        lista_Aux->ultimo->prox = NULL;
        lista_Aux->ultimo->quantidade++;
        free(elemento_remove);
    }
    else{
        elemento_remove->ant->prox = elemento_remove->prox;
        elemento_remove->prox->ant = elemento_remove->ant;
        free(elemento_remove);
    }
    lista_Aux->tamanho_lista--;
}

int busca_ruido(tipo_lista *lista_Aux, tipo_elemento *elemento_void){

    if(elemento_void->prox==NULL && elemento_void->quantidade==1 && elemento_void->ant->quantidade==1){
        return 0;
    }
    printf("\npassouSaporra");
    printf("\npassouCaraloh%c", elemento_void->letra);

    if(elemento_void->prox->quantidade == 1 && elemento_void->ant->quantidade == 1){
        elemento_void=elemento_void->prox;
    }

    else{
        if(elemento_void->quantidade == 1){

            if(elemento_void->prox->quantidade > elemento_void->ant->quantidade){
                elemento_void->prox->quantidade++;
            }
            else{
                if(elemento_void->ant->quantidade > elemento_void->prox->quantidade){
                elemento_void->ant->quantidade++;
                }
            }
            remove_ruido(lista_Aux, elemento_void);
        }
    }
}

void manipula(tipo_lista *lista_Aux){
    int x;

    tipo_elemento *ruidocheck;
    ruidocheck = lista_Aux->primeiro;


    if(ruidocheck->ant==NULL && ruidocheck->quantidade==1 && ruidocheck->prox->quantidade==1){
        ruidocheck = ruidocheck->prox;
    }


    while(ruidocheck!=NULL){
        printf("\npassou");
        printf("\nANTES BUSCA %c", ruidocheck->letra);
        busca_ruido(lista_Aux, ruidocheck);
        printf("\nPOS BUSCA %c", ruidocheck->letra);
        ruidocheck=ruidocheck->prox;
    }
}

int main(){

    tipo_lista lista_main;
    inicia_lista(&lista_main);
    tipo_elemento *p;

    int i,cont=0,tmhstring=0;

    char stringA[1023];
    scanf("%s", stringA);
    tmhstring = strlen(stringA);

    for(i=0;i<tmhstring;i++){
        if(stringA[i]==stringA[i+1]){
            cont++;
        }
        else{
            cont++;
            insere(&lista_main, stringA[i], cont);
            cont=0;
        }
    }

    p = lista_main.primeiro;

    printf("%d\n", lista_main.tamanho_lista*2);

    for(i=0;i<lista_main.tamanho_lista;i++){
        printf("%d%c", p->quantidade,p->letra);
        p=p->prox;
    }

    manipula(&lista_main);

    return 0;
}
