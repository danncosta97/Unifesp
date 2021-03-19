#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int main(){
int a=8,b=8;
int x=0;
while(b > 0){
if(b % 2 == 1) x = x + a;
a= 2 * a;
b = floor(b / 2);
}
printf("%d",x);
}
