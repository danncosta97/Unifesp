//AED 2 IB Regina 2018.1 Exercicio 1 Problema 2
//Daniel Costa
//112185

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main(){
    int qtd=0,i=0,j=0,k=0;
    int index=0, comp=0, aux=0;

    scanf("%d", &qtd);

    int vetor[qtd];

    for (i=0;i<qtd;i++){
        scanf("%d", &aux);
        vetor[i] = aux;
    }


    for(i=0;i<qtd-1;i++){
        index=i;
        for(j=i+1;j<qtd;j++){
            if(vetor[j] < vetor[index]){
                index = j;
            }
        }
        aux = vetor[i];
        vetor[i] = vetor[index];
        vetor[index] = aux;

        for (k=0;k<qtd;k++){
            printf("%d ", vetor[k]);
        }

        printf("\n");
    }


return 0;
}

