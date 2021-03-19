#include <stdlib.h>
#include <stdio.h>

typedef struct{
    int base;
    int expoente;
}TipoItem;

typedef struct{
    TipoItem *itens;
    int tamanho;
}TipolistaLinearSD;

void inicializa_lista(TipolistaLinearSD *lista_auxiliar, int tamanhoAux){

    lista_auxiliar->tamanho = 0;

    lista_auxiliar->itens = malloc(tamanhoAux*sizeof(TipoItem));
}

void insere_no_final(TipolistaLinearSD *lista_auxiliar){

    int pos = lista_auxiliar->tamanho, i;
    TipoItem novo_item;

    scanf("%d %d", &novo_item.base, &novo_item.expoente);

    lista_auxiliar->itens[pos] = novo_item;

    lista_auxiliar->tamanho++;
}

void organiza(TipolistaLinearSD *lista_auxiliar){

    int i,j;

    TipoItem auxexpo;

    for(i=0;i<lista_auxiliar->tamanho;i++){
        for(j=0;j<lista_auxiliar->tamanho;j++){
            if(lista_auxiliar->itens[i].expoente < lista_auxiliar->itens[j].expoente){
                auxexpo = lista_auxiliar->itens[i];
                lista_auxiliar->itens[i] = lista_auxiliar->itens[j];
                lista_auxiliar->itens[j] = auxexpo;
            }
        }
    }
}

void soma_base(TipolistaLinearSD *lista_auxiliar){

    int i,j,temp;

    for(i=0;i<lista_auxiliar->tamanho;i++){
        for(j=i+1;j<lista_auxiliar->tamanho;j++){
            if(lista_auxiliar->itens[i].expoente == lista_auxiliar->itens[j].expoente){
                lista_auxiliar->itens[i].base += lista_auxiliar->itens[j].base;
                temp=j;
                while(temp<lista_auxiliar->tamanho){
                    lista_auxiliar->itens[j] = lista_auxiliar->itens[j+1];
                    temp++;
                }
                lista_auxiliar->tamanho--;
            }
        }
    }
}

int main(){

    int tmh, i, j;
    TipolistaLinearSD lista_main;

    scanf("%d", &tmh);

    inicializa_lista(&lista_main,tmh);

    for(i=0;i<tmh;i++){
        insere_no_final(&lista_main);
    }

    organiza(&lista_main);

    soma_base(&lista_main);

    for(i=0;i<lista_main.tamanho;i++){
        printf("%d %d ", lista_main.itens[i].base, lista_main.itens[i].expoente);
    }

return 0;
}
