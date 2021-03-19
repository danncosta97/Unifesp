#include <stdio.h>
#define MAX 20

//************************************************//

typedef struct{
    int placa
}Carro;

typedef struct{
    Carro vet[MAX];
    int qtd;
}Lista;

//************************************************//

void inicializarLista(Lista* listaAux){
    listaAux -> qtd = 0;
}

void inserirLista(Lista* listaAux, Carro x){
    listaAux -> vet[listaAux -> qtd] = x;
    listaAux -> qtd = listaAux -> qtd+1;
    if (listaAux -> qtd == 9){
        printf ("Estacionamento lotado");
    }
}

void retirarLista(Lista* listaAux){
    int placa, i;
    scanf ("%d", &placa);
    for (i=0;i<=listaAux->qtd; i++){
        if(placa == listaAux->vet[i].placa){
            listaAux->vet[i] = listaAux->vet[i+1];
        }
    }
    listaAux -> qtd = listaAux -> qtd-1;
}

void imprimeLista(Lista* listaAux){
    int i;
    Carro x;
    for(i=0;i<(listaAux->qtd);i++){
        x = listaAux->vet[i];
        printf("O carro %d foi estacionado", x.placa);
        printf("\n");
    }
}
//************************************************//

int main(){
    int opp=0, pos=0;
    char test;
    Lista listaAux;
    Carro x;

    printf("Quantas operacoes ira' realizar ? ");
    scanf("%d", &opp);

    inicializarLista(&listaAux);

    do{
        scanf("%c", &test);
            if (test == 'E'){
                scanf("\%d", &x.placa);
                inserirLista(&listaAux, x);
                opp--;
            }
            if (test == 'S'){
                retirarLista(&listaAux);
                opp--;
            }
    }while(opp!=0);

    imprimeLista(&listaAux);

return 0;
}
