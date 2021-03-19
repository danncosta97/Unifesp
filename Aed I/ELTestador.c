#include <stdio.h>
#include <stdlib.h>

int main(){
    int a,b,res;
    char x,y,z,h;

    scanf("%c %c %c", &x,&y,&z);

    a = 0;
    b = x-48;
    res = (a*10)+(x-48);

    h = res;
    printf("int%d char%c",h,h);
    a = h;
    b = y-48;
    res = (a*10)+(y-48);

    a = res;
    b = z-48;
    res = (a*10)+(z-48);

    printf("%d", res);
}
