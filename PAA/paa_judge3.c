//Daniel Barbosa Silva Costa 112185
//PAA 2019.2 - Integral - Judge 03

#include <stdio.h>
#include <stdlib.h>

int counter=0;
int highest=0;

int horse_move(int **m, int a, int b, int *x, int *y, int lines){
	int i = 0;

	if(m[a][b] == 1){
        counter++;
	    m[a][b]=0;
		for(i = 0 ; i < 8 ; i++){
            printf("\nI'm Here m[%d][%d]. Going to ... ",a,b);
            int temp_a = a+x[i];
            int temp_b = b+y[i];
			if( (temp_a >= 0) && (temp_a < lines) && (temp_b >= 0) && (temp_b < 20) ){
			    printf("m[%d][%d]",temp_a,temp_b);
				horse_move(m, temp_a, temp_b, x, y, lines);
			}
            else printf("searching for able position");
		}
		printf("\n finished for m[%d][%d]\n,",a,b);
		if(counter>highest) highest=counter;
        counter--;
	}
	else printf (" I've already been here !!!");
}

int main(int argc, char **argv){
    while(1){
    counter = 0;
	int i = 0, j = 0, lines = 0, a = 0, b = 0, qtd = 0;
	scanf("%d", &lines);
	int **m = (int**) malloc(lines*sizeof(int*));
	for(i = 0; i < lines; i++){
		m[i] = (int*)malloc(20 * sizeof(int));
	}
	for(i = 0; i < lines; i++){
		for(j = 0; j < 20; j++){
			m[i][j]=0;
		}
	}
	for(i = 0; i < lines; i++){
		scanf("%d", &a);
		scanf("%d", &b);
		qtd+=b;
		for(j = 0; j < 20; j++){
			if(j >= a && j < (a+b))	m[i][j]=1;
		}
	}
	for(i = 0; i < lines; i++){
		printf("\n");
		for(j = 0; j < 20; j++){
			printf("%3d",m[i][j]);
		}
	}
	int x[8]={-2,-1,1,2,-2,-1,1,2};
	int y[8]={-1,-2,-2,-1,1,2,2,1};
	horse_move(m, 0, 0, x, y, lines);
	for(i = 0; i < lines; i++){
		printf("\n");
		for(j = 0; j < 20; j++){
			printf("%3d",m[i][j]);
		}
	}
	printf("\n[%d]\n",qtd);
    printf("\n[%d]\n",highest);
	printf("\n\n## %d ##\n\n",qtd-counter);



    char t;
    scanf("%c", &t);
    if(t=='n'){
        break;
    }
    }
    return 0;
}
