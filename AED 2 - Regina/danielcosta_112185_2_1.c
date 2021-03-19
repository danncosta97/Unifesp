//AED 2 IB Regina 2018.1 HEAPSORT
//Daniel Costa
//112185

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void imprime(int *vetor, int tmh){
    int i=0;
    for (i=0;i<tmh;i++){
        printf("%d ", vetor[i]);
    }printf("\n");
}

void refaz(int *vetor, int i, int tmh){
    int esq = ((i+1)*2)-1;
    int dir = (i+1)*2;
    int aux = vetor[i];

    if(dir<tmh && ( (vetor[i]<vetor[dir]) || (vetor[i]<vetor[esq]) )){
        if(vetor[esq]>vetor[dir]){
            vetor[i] = vetor[esq];
            vetor[esq] = aux;
            refaz(vetor, esq, tmh);
        }
        else{
            vetor[i] = vetor[dir];
            vetor[dir] = aux;
            refaz(vetor, dir, tmh);
        }
    }
    else{
        if(esq<tmh && (vetor[i]<vetor[esq])){
            vetor[i] = vetor[esq];
            vetor[esq] = aux;
            refaz(vetor, esq, tmh);
        }
    }

}

void constroi(int *vetor, int tmh){
    int i=0;

    for(i=((tmh/2)-1);i>=0;i--){
        refaz(vetor,i,tmh);
    }
}

void heapSort(int *vetor, int tmh){
    int aux = 0;
    int m = tmh-1;

    constroi(vetor,tmh);
    imprime(vetor,tmh);

    while(m>0){
        aux = vetor[0];
        vetor[0] = vetor[m];
        vetor[m] = aux;

        refaz(vetor,0,m);
        imprime(vetor,tmh);

        m--;
    }
}

int main(){

    int tmh=0,i=0,aux=0;
    scanf("%d", &tmh);
    int vetor[tmh];

    for (i=0;i<tmh;i++){
        scanf("%d", &aux);
        vetor[i] = aux;
    }

    imprime(vetor,tmh);

    heapSort(vetor, tmh);

return 0;
}

