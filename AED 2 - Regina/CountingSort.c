//AED 2 IB Regina 2018.1
//Daniel Costa
//112185

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void countingSort(int *vetor, int tmh){
    int i=0,j=0,k=0,max=0;
    max=vetor[i];

    for(i=1;i<tmh;i++){
        if(vetor[i]>max){
            max=vetor[i];
        }
    }
    max++;

    int *vetorAux = (int*)malloc(max*sizeof(int));
    int *vetorReturn = (int*)malloc(tmh*sizeof(int));

    for (i=0;i<max;i++){
        vetorAux[i]=0;
    }

    for(i=0;i<tmh;i++){
        vetorAux[vetor[i]]+=1;
    }

    int soma=0;
    for (i=0;i<max;i++){
        soma+=vetorAux[i];
        vetorAux[i]=soma;
    }

    for (i=0;i<max;i++){
        printf("%d ", vetorAux[i]);
    }

    for(i=tmh-1;i>=0;i--){
        vetorReturn[vetorAux[vetor[i]]-1]=vetor[i];
        vetorAux[vetor[i]]-=1;
    }

    for (i=0;i<tmh;i++){
        printf("%d ", vetorReturn[i]);
    }

}

int main(){
    int i=0,j=0,aux=0, tmh=0;
    scanf("%d", &tmh);

    int vetor[tmh];

    for (i=0;i<tmh;i++){
        scanf("%d", &aux);
        vetor[i] = aux;
    }

    countingSort(vetor,tmh);

return 0;
}
