//AED 2 IB Regina 2018.1 Exercicio 1 Problema 1
//Daniel Costa
//112185

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main(){

    int qtd=0,i=0,j=0,k=0;
    int key=0, comp=0, aux=0;

    scanf("%d", &qtd);

    int vetor[qtd];

    for (i=0;i<qtd;i++){
        scanf("%d", &aux);
        vetor[i] = aux;
    }

    for(i=1;i<qtd;i++){
        key = vetor[i];

        for(j=i-1;j>=0;j--){
            if(key<vetor[j]){
                aux = vetor[j];
                vetor[j] = key;
                vetor[j+1] = aux;
            }
        }

        for(k=0;k<qtd;k++){
            printf("%d ", vetor[k]);
        }
        printf("\n");
    }

return 0;
}
