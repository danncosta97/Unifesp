//AED 2 IB Regina 2018.1
//Daniel Costa
//112185

#include <stdlib.h>
#include <stdio.h>
#include <math.h>


void merge(int vetor[], int inicio, int meio, int fim)
{
    int i, j, k;
    int tmh1 = meio - inicio + 1;
    int tmh2 =  fim - meio;

    /* create temp arrays */
    int *firstHalf = malloc(tmh1*sizeof(int));
    int secondHalf[tmh2];

    /* Copy data to temp arrays firstHalf[] and secondHalf[] */
    for (i = 0; i < tmh1; i++)
        firstHalf[i] = vetor[inicio+i];
    for (j = 0; j < tmh2; j++)
        secondHalf[j] = vetor[meio+1+j];

    /* Merge the temp arrays back into vetor[firstHalf..secondHalf]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = inicio; // Initial index of merged subarray
    while (i < tmh1 && j < tmh2)
    {
        if (firstHalf[i] <= secondHalf[j])
        {
            vetor[k] = firstHalf[i];
            i++;
        }
        else
        {
            vetor[k] = secondHalf[j];
            j++;
        }
        k++;
    }

    while (i < tmh1)
    {
        vetor[k] = firstHalf[i];
        i++;
        k++;
    }

    while (j < tmh2)
    {
        vetor[k] = secondHalf[j];
        j++;
        k++;
    }
    free(firstHalf);
}

void mergeSort(int *vetor, int inicio, int fim){
    if (inicio < fim) {
        int meio = (fim+inicio)/2;

        mergeSort(vetor, inicio, meio);
        mergeSort(vetor, meio+1, fim);
        merge(vetor, inicio, meio, fim);
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

    mergeSort(vetor,0,tmh);

    for (i=0;i<tmh;i++){
        printf("%d ", vetor[i]);
    }

return 0;
}
