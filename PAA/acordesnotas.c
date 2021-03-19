//Daniel Costa 112185
//PAA - Integral 2019.2
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

int main(){
	int a=0,b=0;
	scanf("%d %d",&a,&b);
	int *notas=(int*)malloc(b*sizeof(int));
	int *acorde=(int*)malloc(a*sizeof(int));
	for(int i=0;i<a;i++){
		acorde[i]=0;
	}
	for(int i=0;i<b;i++){
		notas[i]=0;
	}
	//printf("\nALOU");
	for(int i=0;i<b;i++){
		scanf("%d",&notas[i]);
	}
	for(int i=0;i<b;i++){
		acorde[notas[i]]=1;
	}

    /*printf("\nALOU2\n");
	for(int i=0;i<a;i++){
		printf("[%d]",acorde[i]);
	}*/

	struct timeval stop, start;

    gettimeofday(&start, NULL);



	int counter=0;
	int able=1;
	int rounder=0;

    if((b!=0) && (a/b>1)){
        for(int i=0;i<a;i++){
            able=1;
            /*printf("\n\nAttempt (%d)\n",i);
            for(int i=0;i<a;i++){
                printf("[%d]",acorde[(i+rounder)%a]);
            }
            printf("\n");*/
            for (int j=0;j<a;j+=a/b){
                for(int k=j;k<j+a/b;k++){
                    //printf("[%d]",acorde[(k+rounder)%a]);
                    if(acorde[(k+rounder)%a]==1){
                        counter++;
                    }
                }
                //printf("\n");
                if(counter!=0){
                    able=counter*able;
                }
                counter=0;
                if(able!=1){
                    break;
                }
            }
            //printf("LOOK AT THIS %d",able);
            if(able==1){
                break;
            }
            else{
                rounder++;
            }
        }
    } else able=1;

    if(able==1){
        printf("S");
    } else printf("N");
    gettimeofday(&stop, NULL);
    printf("\nDuration MS %.3f\n",
           ((double) (stop.tv_sec - start.tv_sec) * 1000 +
           (double) (stop.tv_usec - start.tv_usec) / 1000));
	return 0;
}
