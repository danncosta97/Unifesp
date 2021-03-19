//AED 2 IB Regina 2018.1 QuickSort
//Daniel Costa
//112185

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

Imprime(int *A, int n){
    int i;printf("\n");
    for (i=0;i<n;i++){
        printf("%d ", A[i]);
    }
}

int particiona(int *vetor, int inicio, int fim){
    int j=0,aux=0;

    int i=inicio-1;
    int pivo=vetor[fim];

    for(j=inicio;j<fim;j++){
        if(vetor[j]<pivo){
            i++;
            aux=vetor[i];
            vetor[i]=vetor[j];
            vetor[j]=aux;
        }
    }

    vetor[fim]=vetor[i+1];
    vetor[i+1]=pivo;

    return (i+1);
}

void quickSort(int *vetor, int inicio, int fim, int tmh){
    if(inicio<fim){
        int particao = particiona(vetor, inicio, fim);
        if (fim < tmh-1){
            Imprime(vetor, tmh);
        }
        quickSort(vetor,inicio,particao-1,tmh);
        quickSort(vetor,particao+1,fim,tmh);
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

    quickSort(vetor,0,tmh,tmh);

return 0;
}
