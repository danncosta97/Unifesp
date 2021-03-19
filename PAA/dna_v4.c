//Daniel Barbosa Silva Costa 112185
//PAA 2019.2 - Integral - Judge 04

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv){

    char *dna=calloc(2000,sizeof(char));
    int i=0,j=0,k=0,l=0,m=0;

    scanf("%s",dna);
    int size_dna = strlen(dna);

    scanf("%d",&m);
    int *mut = (int*)calloc(size_dna,sizeof(int));

    int p=0;
    for(i=0; i<m; i++){
        scanf("%d",&p);
        mut[p-1]=1;
    }

    //stores the palindrome size
    int **table = (int**) malloc(size_dna*sizeof(int*)+1);
    for(i = 0; i < size_dna; i++){
        table[i] = (int*)calloc(size_dna,sizeof(int));
    }

    //stores the qtt of mutations for a palindrome
    int **table_bases = (int**) malloc(size_dna*sizeof(int*)+1);
    for(i = 0; i < size_dna; i++){
        table_bases[i] = (int*)calloc(size_dna,sizeof(int));
    }

     // only 1 letter
    for(i=0; i<size_dna; i++){
        table[i][i]=1;
        table_bases[i][i]=mut[i];
    }

    // 2 letters
    for(i=0; i<size_dna-1; i++){
        if(dna[i]==dna[i+1]){
            table[i][i+1]=2;
            table_bases[i][i+1]=mut[i]+mut[i+1];
        }
        else{
            table[i][i+1]=1;
            if(mut[i]==1 || mut[i+1]==1) table_bases[i][i+1]=1;
            else table_bases[i][i+1]=0;
        }
    }

    /*for(k=0; k<size_dna; k++){
                for(l=0; l<size_dna; l++){
                    printf("%d ", table[k][l]);
                }
                printf("\n");
            }printf("\n");

            for(k=0; k<size_dna; k++){
                for(l=0; l<size_dna; l++){
                    printf("%d ", table_bases[k][l]);
                }
                printf("\n");
            }printf("\n############\n");*/

    // 3 or more letters
    //checar qual tem mais bases
    int most_bases=0, longest_palindrome=0;
    for(i=2; i<size_dna; i++){
        for(j=0; j<size_dna-i; j++){
            if( dna[j] == dna[j+i]){//printf("if");
                table[j][j+i] = 2 + table[j+1][j+i-1];
                if(mut[j]+mut[j+i]+table_bases[j+1][j+i-1]<table_bases[j][j+i-1]){
                    table_bases[j][j+i] = mut[j]+mut[j+i]+table_bases[j][j+i-1];
                }
                else if(mut[j]+mut[j+i]+table_bases[j+1][j+i-1]<table_bases[j+1][j+i]){
                    table_bases[j][j+i] = mut[j]+mut[j+i]+table_bases[j+1][j+i];
                }
                else{
                    table_bases[j][j+i] = mut[j]+mut[j+i]+table_bases[j+1][j+i-1];
                }
                //printf("\ncase0 [%d]%d [%d]%d %d\n",j,mut[j],j+i,mut[j+i],table_bases[j+1][j+i-1]);
            }
            else{
                //printf("else");
                if(table_bases[j][j+i-1]>table_bases[j+1][j+i]){
                    table[j][j+i] = table[j][j+i-1];
                    table_bases[j][j+i] = table_bases[j][j+i-1];
                    //printf("\ncase1\n");
                }
                else if(table_bases[j][j+i-1]<table_bases[j+1][j+i]){
                    table[j][j+i] = table[j+1][j+i];
                    table_bases[j][j+i] = table_bases[j+1][j+i];

                    //printf("\ncase2\n");
                }
                else if(table[j][j+i-1]>table[j+1][j+i]){
                    table[j][j+i] = table[j][j+i-1];
                    table_bases[j][j+i] = table_bases[j][j+i-1];
                    //printf("\ncase3\n");
                }
                else if(table[j][j+i-1]<table[j+1][j+i]){
                    table[j][j+i] = table[j+1][j+i];
                    table_bases[j][j+i] = table_bases[j+1][j+i];
                    //printf("\ncase4\n");
                }
                else{
                    //printf("equal");
                    table[j][j+i] = table[j+1][j+i];
                    table_bases[j][j+i] = table_bases[j+1][j+i];
                }
            }

            /*for(k=j; k<=j+i; k++){

                    printf("%c", dna[k]);
            }printf("\n");

            for(k=0; k<size_dna; k++){
                for(l=0; l<size_dna; l++){
                    printf("%d ", table[k][l]);
                }
                printf("\n");
            }printf("\n");

            for(k=0; k<size_dna; k++){
                for(l=0; l<size_dna; l++){
                    printf("%d ", table_bases[k][l]);
                }
                printf("\n");
            }printf("\n############\n");*/
        }
    }

    k=0; l=0;
    for(k=0; k<size_dna; k++){
        for(l=k; l<size_dna; l++){
            //printf("\n**%d**\n",most_bases);
            if(most_bases<table_bases[k][l]){
                longest_palindrome=table[k][l];
                most_bases=table_bases[k][l];
            }
            if(most_bases==table_bases[k][l]){
                //printf("\n b[%d][%d] (%d) $$ p[%d][%d] (%d)\n", k,l,table_bases[k][l],k,l,table[k][l]);
                if(longest_palindrome<table[k][l]){
                    longest_palindrome=table[k][l];
                }
            }
        }
    }

    /*for(k=0; k<size_dna; k++){
        for(l=0; l<size_dna; l++){
            printf("%d ", table[k][l]);
        }
        printf("\n");
    }printf("\n");

    for(k=0; k<size_dna; k++){
        for(l=0; l<size_dna; l++){
            printf("%d ", table_bases[k][l]);
        }
        printf("\n");
    }printf("\n############\n");*/

    printf("%d",longest_palindrome);

return 0;
}
