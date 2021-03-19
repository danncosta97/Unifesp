#include <stdlib.h>
#include <stdio.h>

struct pessoa{
    int idade;
    char nome [20];
    struct pessoa *prox;
};
typedef struct pessoa tipo_pessoa;

struct listade{
    int tamanho_lista;
    tipo_pessoa *primeiro;
    tipo_pessoa *ultimo;
};
typedef struct listade tipo_lista;

/********************************************************/

void inicia_lista (tipo_lista *listaAux){
    listaAux->primeiro = NULL;
    listaAux->ultimo = NULL;
    listaAux -> tamanho_lista = 0;
}

void insere_na_lista (tipo_lista *listaAux){
    int i, idade;
    char nome[20];

    printf("Digite um nome: ");
    scanf("%s", nome);
    printf("Digite a idade: ");
    scanf("%d", &idade);

    //aloca memoria
    tipo_pessoa *nova_pessoa = (tipo_pessoa*) malloc(sizeof(tipo_pessoa));

    //completa os dados
    strcpy(nova_pessoa->nome, nome);

    nova_pessoa->idade = idade;

    //Se, lista sem elementos
    if (listaAux->tamanho_lista == 0){
        nova_pessoa->prox = NULL;
        listaAux->primeiro = nova_pessoa;
        listaAux->ultimo = nova_pessoa;
    }

    //Senao
    else{
        nova_pessoa->prox = NULL;
        listaAux->ultimo->prox = nova_pessoa;
        listaAux->ultimo = nova_pessoa;
    }

    listaAux->tamanho_lista++;

}


void imprime (tipo_lista *listaAux){
    int tmh;

    tipo_pessoa *pontAux;

    pontAux = listaAux->primeiro;

    tmh = listaAux->tamanho_lista;

    while(tmh > 0){
        printf("\n");
        printf("Nome :%s    Idade: %d anos", pontAux->nome, pontAux->idade);
        pontAux = pontAux->prox;
        tmh--;
    }
}

    //Remover//

    //ORDENAR//

int main(){

    int i, idade, qtd, test=1;
    char nome[20];

    tipo_lista lista_main;

    inicia_lista (&lista_main);

    printf("Qunatas pessoas deseja inserir? ");
    scanf("%d", &qtd);

    for(i=0;i<qtd;i++){
        insere_na_lista (&lista_main);
    }

    imprime (&lista_main);

return 0;
}
