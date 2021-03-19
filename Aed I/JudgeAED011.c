#include <stdio.h>
#define MAX 20
//************************************************/

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
        printf ("##### ESTACIONAMENTO LOTADO #####");
    }
}

void retirarLista(Lista* listaAux, int pos, Carro x){
    int i, mov=0;

    if (pos >= listaAux->qtd)
    {
        inserirLista(listaAux, x);
    }
    else
    {
        for (i = pos; i < listaAux->qtd; i++){
            listaAux->vet[i-1] = listaAux->vet[i];
            mov++;
        }
    listaAux -> qtd = listaAux -> qtd-1;
    }
    printf ("%d Manobras", mov);
}

void buscarposLista(Lista* listaAux, Carro x){}

void imprimeLista(Lista* listaAux){
    int i;
    Carro x;
    printf ("Qtd de carros: %d\n", listaAux->qtd);
    for(i=0;i<(listaAux->qtd);i++){
        x = listaAux->vet[i];
        printf("Placa: %d", x.placa);
        printf("\n");
    }
}
//************************************************/

int main()
{
    int opp=0,test=0, pos=0, contmain=0;
    Lista listaAux;
    Carro x;

    printf("Quantas operações ira' realizar ?");
    scanf("%d", &opp);


    do{
        printf ("\n1 - Criar Lista");
        printf ("\n2 - Inserir Carro");
        printf ("\n3 - Retirar Carro");
        printf ("\n4 - Imprimir\n");
        scanf("%d", &test);
            switch(test){
            case 1:
                    inicializarLista(&listaAux);
                break;
            case 2:
                    contmain++;
                    printf("Placa:");
                    scanf("%d", &x.placa);
                    inserirLista(&listaAux, x);
                break;
            case 3:
                    contmain++;
                    printf("Placa:");
                    scanf("%d", &x.placa);
                    printf("Posicao:");
                    scanf("%d", &pos);
                    retirarLista(&listaAux, pos, x);
                break;
            case 4:
                    contmain++;
                    imprimeLista(&listaAux);
                break;
        }
    }while(test!=0);
return 0;
}
