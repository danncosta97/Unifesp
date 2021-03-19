#include <stdio.h>
#include <stdlib.h>

int main(){
    int i,j;
    int *p;

    **p = (int**) malloc(sizeof(int)*20);

    for (i=0; i<20; i++){
        **(p+i) = rand()%100;
        for (j=0; j<20; i++){
            *(p+j) = rand()%100;
        }
    }

    for (i=0; i<20; i++){
        printf ("%2d", p[i]);
    }

return 0;
}
