// NOME: DANIEL BARBOSA SILVA COSTA   R.A.:112185
// AED I (REOF) NOTURNO 2017.1

#include <stdio.h>
#include <stdlib.h>

void main(){

    int i=0, j=0, cont=0, tmh=0;                        //Declara as variáveis

    tmh = rand()%100;                                   //Randomiza variavel tmh (tamanho)

    int vetor[tmh];

    for(i=0; i<tmh; i++){

        vetor[i] = rand()%100;                        //Preenche randomicamente os indices do vetor

        if(vetor[i]%2 == 0){
            cont++;                                     //Conta quantos numeros pares há no vetor
        }
    }

    printf("Vetor Original:\n");

    for(i=0; i<tmh; i++){
        printf("%d ",vetor[i]);
    }

    int *vetoraloc;                                     //Declara o ponteiro

    vetoraloc = (int*) malloc(cont*sizeof(int));        //Aloca espaco para o vetor com elementos pares

    for(i=0; i<tmh; i++){                               //Preenche com os pares do vetor o vetoraloc
        if(vetor[i]%2 == 0){
            vetoraloc[j] = vetor[i];
            j++;
        }
    }

    printf("\n\nVetor Alocado Dimnamicamente Com Pares:\n");

    for(i=0; i<cont; i++){
        printf("%d ",vetoraloc[i]);
    }
}
