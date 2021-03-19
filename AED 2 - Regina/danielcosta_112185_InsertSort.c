//AED 2 IB Regina 2018.1
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
        j=i-1;
        key = vetor[i];
        while(j>=0){

            if(key>vetor[j]){
                vetor[j+1]=key;
                j=0;
            }
            if(key<vetor[j]){
                vetor[j+1] = vetor[j];
                if(j==0){
                    vetor[0]=key;
                }
            }
            j--;
        }

        for (k=0;k<qtd;k++){
            printf("%d ", vetor[k]);
        }

        printf("\n");
    }

return 0;
}
