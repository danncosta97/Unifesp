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

    tipo_elemento *novo_elemento = calloc(1,sizeof(tipo_elemento));
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
        novo_elemento->prox=NULL;
        novo_elemento->ant=lista_Aux->ultimo;
        lista_Aux->ultimo->prox = novo_elemento;
        lista_Aux->ultimo = novo_elemento;
    }
    lista_Aux->tamanho_lista++;
}

void remove_ruido(tipo_lista *lista_Aux, tipo_elemento *elemento_remove){

    tipo_elemento *aux_remove;

    aux_remove = elemento_remove;

    if(elemento_remove->ant==NULL){
        lista_Aux->primeiro = elemento_remove->prox;
        lista_Aux->primeiro->ant = NULL;
        free(elemento_remove);
    }
    else{
        if(elemento_remove->prox==NULL){
            lista_Aux->ultimo = elemento_remove->ant;
            lista_Aux->ultimo->prox = NULL;
            free(elemento_remove);
        }
        else{
            elemento_remove->ant->prox = elemento_remove->prox;
            elemento_remove->prox->ant = elemento_remove->ant;
            free(elemento_remove);
        }
    }

    lista_Aux->tamanho_lista--;
}

void manipula(tipo_lista *lista_Aux){

    tipo_elemento *ruidocheck;
    ruidocheck = lista_Aux->primeiro;

    if(lista_Aux->primeiro->quantidade==1){
        if(lista_Aux->primeiro->prox->quantidade>1){
            ruidocheck->prox->quantidade++;
            remove_ruido(lista_Aux, ruidocheck);
            ruidocheck = lista_Aux->primeiro->prox;

        }
        else{
            ruidocheck = ruidocheck->prox;
        }
    }

    while(ruidocheck->prox!=NULL){
        if(ruidocheck->quantidade==1){
            if(ruidocheck->ant->quantidade==1 || ruidocheck->prox->quantidade==1){

            }
            else{
                if(ruidocheck->ant->quantidade >= ruidocheck->prox->quantidade){
                    ruidocheck->ant->quantidade++;
                    remove_ruido(lista_Aux,ruidocheck);
                }
                else{
                    if(ruidocheck->ant->quantidade < ruidocheck->prox->quantidade){
                        ruidocheck->prox->quantidade++;
                        remove_ruido(lista_Aux,ruidocheck);
                    }
                }
            }
        }ruidocheck=ruidocheck->prox;
    }

    if(lista_Aux->ultimo->quantidade==1){
        if(lista_Aux->ultimo->ant->quantidade>1){
            ruidocheck->ant->quantidade++;
            remove_ruido(lista_Aux, ruidocheck);
        }
    }


}

void print_lista(tipo_lista *lista_Aux){
    tipo_elemento *p;

    printf("%d\n", lista_Aux->tamanho_lista*2);
    for(p=lista_Aux->primeiro;p!=NULL;p=p->prox){
        printf("%d%c", p->quantidade,p->letra);
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

    print_lista(&lista_main);

    manipula(&lista_main);

    printf("\n");
    print_lista(&lista_main);

    return 0;
}
