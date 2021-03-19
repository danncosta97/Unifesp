#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define TRUE 1
#define FALSE 0

int is_a_solution(int a[], int k, int n)
{
return (k == n); /* is k == n? */
}

void construct_candidates(int a[], int k, int n, int c[], int
*ncandidates)
{
c[0] = TRUE;
c[1] = FALSE;
*ncandidates = 2;
}

void process_solution(int a[], int k)
{
int i; /* counter */
printf("{");
for (i=1; i<=k; i++)
if (a[i] == TRUE) printf(" %d",i);
printf(" }\n");
}

bool finished = FALSE; /* found all solutions yet? */
int l=0;
int backtrack(int a[], int k, int input){
    int c[10]; /* candidates for next position */
    int ncandidates; /* next position candidate count */
    int i; /* counter */
    if (is_a_solution(a,k,input))
        process_solution(a,k);
    else {
        k = k+1;
        construct_candidates(a,k,input,c,&ncandidates);
        for (i=0; i<ncandidates; i++) {
            a[k] = c[i];
            l=0;
            printf("[");
            printf("%d",a[0]);
            printf("%d",a[1]);
            printf("%d",a[2]);
            printf("%d",a[3]);
            printf("%d",a[4]);
            printf("]");
            //make_move(a,k,input);
            backtrack(a,k,input);
            //unmake_move(a,k,input);
            if (finished) return 1; /* terminate early */
        }
    }
}

void generate_subsets(int n)
{
    int *a=(int*)calloc(10, sizeof(int)); /* solution vector */
    backtrack(a,0,n);
}

int main(){
    generate_subsets(4);
    return 0;
}
