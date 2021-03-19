// NOME: DANIEL BARBOSA SILVA COSTA   R.A.:112185
// AED I (REOF) NOTURNO 2017.1

#include <stdio.h>
#include <stdlib.h>

void printa_matriz (int **matrizAux){

    int i,j;

    for(i=0; i<5; i++){
        for(j=0; j<5; j++){
            printf("%d ",matrizAux[i][j]);
        }
    printf("\n");
    }
}

void busca_elemento (int **matrizAux, int searchAux){

    int i,j,testAux=0;

    for(i=0; i<5; i++){
        for(j=0; j<5; j++){
            if(searchAux == matrizAux[i][j]){
                printf("\nELEMENTO ENCONTRADO - POSICAO EM:\nLINHA(%d) COLUNA(%d)", i+1, j+1);
                testAux = 1;
            }
        }
    }

    if(testAux == 0){
        printf("Nao ha' o elemento solicitado");
    }
}

void insere_elemento (int **matrizAux, int x, int y, int elementoAux){

    int i=x, j=y;

    matrizAux[i-1][j-1] = elementoAux;

}

int main(){

    int **matriz;
    int i=0,j=0,search;
    int test;

    matriz = (int**)malloc(5*sizeof(int*));

    for(i=0; i<5; i++){
        matriz[i] = (int*) malloc(5*sizeof(int*));
    }

    for(i=0; i<5; i++){
        for(j=0; j<5; j++){
            matriz[i][j] = rand()% 10;
            matriz[j][i] = matriz[i][j];
        }
    }

    printf("Deseja procurar elemento na matriz ? 1-Sim 0-Nao: ");
    scanf("%d", &test);

    while(test == 1){
        printf("\nDigite o elemento de procura: ");
        scanf("%d", &search);

        busca_elemento(&*matriz, search);

        printf("\n\nDeseja procurar outro elemento na matriz ? 1-Sim 0-Nao: ");
        scanf("%d", &test);
    }

    printf("\nDeseja inserir algum elemento na matriz ? 1-Sim 0-Nao: ");
    scanf("%d", &test);

    while(test == 1){
        int novo_elemento;

        printf("\nDigite a linha e a conluna para inserir (entre 1 e 5): ");
        scanf("%d %d", &i,&j);

        printf("\nInsira o elemento: ");
        scanf("%d", &novo_elemento);

        insere_elemento(&*matriz, i, j, novo_elemento);

        printf("\nDeseja inserir outro elemento na matriz ? 1-Sim 0-Nao: ");
        scanf("%d", &test);
    }

    printf("\n");

    printa_matriz(&*matriz);

return 0;
}
