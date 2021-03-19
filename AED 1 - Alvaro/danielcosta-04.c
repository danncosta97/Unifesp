//Daniel Barbosa Silva Costa    112185
//AED NOTURNO 2017.1

#include <stdlib.h>
#include <stdio.h>

typedef struct cliente{
    int tempo;
    int senha;
    struct cliente *ant;
}tipo_cliente;

typedef struct atendente{
    int numero;
    int temporestante;
    int atendimentos;
    int senha [1023];
    struct atendente *ant;
}tipo_atendente;



typedef struct listacl{
    tipo_cliente *primeiro;
    tipo_cliente *ultimo;
    int tamanho;
}tipo_listaCL;

typedef struct listaat{
    tipo_atendente *primeiro;
    tipo_atendente *ultimo;
    int tamanho;
}tipo_listaAT;



void inicia_listaCL(tipo_listaCL *lista_aux){
    lista_aux->primeiro=NULL;
    lista_aux->ultimo=NULL;
    lista_aux->tamanho=0;
}

void inicia_listaAT(tipo_listaAT *lista_aux){
    lista_aux->primeiro=NULL;
    lista_aux->ultimo=NULL;
    lista_aux->tamanho=0;
}

void insere_cliente(tipo_listaCL *lista_aux, int tempo_void, int senha_void){

    tipo_cliente *novo_cliente = (tipo_cliente*) malloc(sizeof(tipo_cliente));

    novo_cliente->tempo = 0;
    novo_cliente->senha = 0;

    novo_cliente->tempo = tempo_void;
    novo_cliente->senha = senha_void;

    if(lista_aux->primeiro == NULL){
        novo_cliente->ant = NULL;
        lista_aux->primeiro = novo_cliente;
        lista_aux->ultimo = novo_cliente;
    }
    else{
        novo_cliente->ant = NULL;
        lista_aux->ultimo->ant = novo_cliente;
        lista_aux->ultimo = novo_cliente;
    }

    lista_aux->tamanho=senha_void;
}

int remove_cliente(tipo_listaCL *lista_aux){

    if(lista_aux->primeiro == NULL){
        return 0;
    }
    else{
        lista_aux->primeiro = lista_aux->primeiro->ant;
    }

    lista_aux->tamanho--;

    return 1;
}

void insere_atendente(tipo_listaAT *lista_aux){
    int i;
    tipo_atendente *novo_atendente = (tipo_atendente*) malloc(sizeof(tipo_atendente));

    novo_atendente->temporestante = 0;
    for(i=0;i<1023;i++){
        novo_atendente->senha[i] = 0;
    }
    novo_atendente->atendimentos=0;

    if(lista_aux->primeiro == NULL){
        novo_atendente->ant = NULL;
        lista_aux->primeiro = novo_atendente;
        lista_aux->ultimo = novo_atendente;
    }
    else{
        novo_atendente->ant = NULL;
        lista_aux->ultimo->ant = novo_atendente;
        lista_aux->ultimo = novo_atendente;
    }

    lista_aux->tamanho++;
    novo_atendente->numero=lista_aux->tamanho;
}

void buscalivre_e_atribui(tipo_listaCL *lista_auxCL, tipo_listaAT *lista_auxAT){
    int i=0, k;
    tipo_cliente *c;
    tipo_atendente *a;
    c = lista_auxCL->primeiro;

    while(lista_auxCL->tamanho>0){

        a = lista_auxAT->primeiro;

        while(a != NULL){
            if(a->temporestante==0){
                a->atendimentos++;
                k=0;
                while(a->senha[k] != 0){
                    k++;
                }
                a->senha[k] = c->senha;
                a->temporestante = c->tempo;
                remove_cliente(lista_auxCL);
                if(lista_auxCL->primeiro == NULL){
                    a=NULL;
                }
                c = lista_auxCL->primeiro;
            }
            else{
                a = a->ant;
            }
        }
        a = lista_auxAT->primeiro;

        while(a != NULL){
            if(a->temporestante>0){
                a->temporestante--;
            }
            a = a->ant;
        }
    }
}

void imprime(tipo_listaAT *lista_auxAT){
    int i, k;
    tipo_atendente *a;

    a = lista_auxAT->primeiro;

    for(i=0;i<lista_auxAT->tamanho;i++){
        printf("\n%d: ",a->numero);
        if(a->atendimentos>0){
            for (k=0;k<a->atendimentos;k++){
                printf("%d ", a->senha[k]);
            }
        }
        a=a->ant;
    }
}



int main(){

    int senha=0,qtdcliente=0,tempocliente=0,i=0;
    int qtdatendente=0;

    tipo_listaCL lista_cliente;
    tipo_listaAT lista_atendente;

    inicia_listaCL(&lista_cliente);
    inicia_listaAT(&lista_atendente);

    scanf("%d %d",&qtdcliente,&qtdatendente);

    for(i=0;i<qtdcliente;i++){
        senha++;
        scanf("%d", &tempocliente);
        insere_cliente(&lista_cliente,tempocliente,senha);
    }

    for(i=0;i<qtdatendente;i++){
        insere_atendente(&lista_atendente);
    }

    buscalivre_e_atribui(&lista_cliente, &lista_atendente);

    imprime(&lista_atendente);

return 0;
}
