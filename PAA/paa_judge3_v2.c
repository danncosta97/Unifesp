//Daniel Barbosa Silva Costa 112185
//PAA 2019.2 - Integral - Judge 03

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <windows.h>

int counter=0;
int highest=0;

int horse_move(int **m, int a, int b, int *x, int *y, int lines, int qtd){
	int i = 0;
        counter++;
	    m[a][b]=0; //set current position as a visited position;

		for(i = 0 ; i < 8 ; i++){
            int temp_a = a+x[i];
            int temp_b = b+y[i];
			if( (temp_a >= 0) && (temp_a < lines) && (temp_b >= 0) && (temp_b < 20)){
			    if(m[temp_a][temp_b]==1){
                    //printf("\nI'm Here m[%d][%d]. Going to ... m[%d][%d] | MOVEMENTS (%d)",a,b,temp_a,temp_b,counter);
                    horse_move(m, temp_a, temp_b, x, y, lines, qtd);
			    }
			}
			if (highest==qtd){break;}
            //else printf("\nSearching for able position");
		}
		//printf("\nFinished for m[%d][%d]\n",a,b);

		//since theres no more able moves for a position
		//set it as unvisited and return to the position that brought here
		//checking if its the highest tour and decrementing counter
		//because its returning one position
		m[a][b]=1;
		//printf("\nCOUNTER %d", counter);
		//Sleep(50);
		if(counter>highest) highest=counter;
        counter--;
        if(highest == qtd) {
                //printf("TOP");
                return 1;
        }    //all positions were visited, we can stop
        if(a == 0 && b == 0) return 0;
}

int main(int argc, char **argv){
    struct timeval stop, start;
    gettimeofday(&start, NULL);
    counter = 0;
	int i = 0, j = 0, lines = 0, a = 0, b = 0, qtd = 0, h=0;
	scanf("%d", &lines);

	//allocate the matrix of 10X20 (max possible)
	int **m = (int**) malloc(lines*sizeof(int*));
	for(i = 0; i < lines; i++){
		m[i] = (int*)malloc(20 * sizeof(int));
	}

	for(i = 0; i < lines; i++){
		for(j = 0; j < 20; j++){
			m[i][j]=0;
		}
	}
	//set 1 to true positions in the matrix (able for move)
	for(i = 0; i < lines; i++){
		scanf("%d", &a);
		scanf("%d", &b);
		qtd+=b;
		for(j = 0; j < 20; j++){
			if(j >= a && j < (a+b))	m[i][j]=1;
		}
	}

	/*for(i = 0; i < lines; i++){
		printf("\n");
		for(j = 0; j < 20; j++){
			printf("%3d",m[i][j]);
		}
	}*/
	//all possible movies (displacements from and certain position)
	int x[8]={-2,-1,1,2,-2,-1,1,2};
	int y[8]={-1,-2,-2,-1,1,2,2,1};
	gettimeofday(&start, NULL);

	//make all possible moves to find the tour with more movements possible
	h=horse_move(m, 0, 0, x, y, lines, qtd);

	/*for(i = 0; i < lines; i++){
		printf("\n");
		for(j = 0; j < 20; j++){
			printf("%3d",m[i][j]);
		}
	}*/
	//printf("\n[%d]\n",qtd);
    //printf("\n[%d]\n",highest);

    //get the qtd position not able to reach trough the longest tour
	if (h==1) printf("0");  //could reach all positions
	else printf("%d",qtd-highest);

	gettimeofday(&stop, NULL);
	printf("\nDuration MS %.3f\n",
           ((double) (stop.tv_sec - start.tv_sec) * 1000 +
           (double) (stop.tv_usec - start.tv_usec) / 1000));


    return 0;
}
