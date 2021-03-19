//AED 2 IB Regina 2018.1
//Daniel Costa
//112185

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main(){

    int qtd=0,i=0,j=0,k=0;
    int key=0, anyChange=0, aux=0;

    scanf("%d", &qtd);

    int vetor[qtd];

    for (i=0;i<qtd;i++){
        scanf("%d", &aux);
        vetor[i] = aux;
    }

    printf("\n");

    for(i=0;i<qtd;i++){
        anyChange=0;
        for(j=0;j<qtd-1;j++){
            if(vetor[j] > vetor[j+1]){
                anyChange=1;
                aux = vetor[j+1];
                vetor[j+1] = vetor[j];
                vetor[j] = aux;
            }
        }
        for (k=0;k<10;k++){
            printf("%d ", vetor[k]);
        }
        if(anyChange==0){
            break;
        }
    }

    for (k=0;k<10;k++){
        printf("%d ", vetor[k]);
    }

return 0;
}

