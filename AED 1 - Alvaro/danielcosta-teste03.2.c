//Nome: Daniel Barbosa Silva Costa      R.A.: 112185
//AED Noturno 2017/1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*typedef struct dados{
    char dado;
}tipo_dado;

typedef struct lista{
    tipo_dado *dados;
    int qtd;
}tipo_listaSD;*/

int verificacao(){

}

int main(){

    int i=0,tmhexpress=0,test=0;

    char expressao[1024], opertest;

    for(i=0;i<1024;i++){
        expressao[i]='\0';
    }

    scanf("%s", expressao);

    free(expressao);

    for(i=0;i<1024;i++){
        if (expressao[i]!='\0')
            tmhexpress++;
        else break;
    }

    if (tmhexpress == 0){
        return 0;
    }

    for(i=0;i<tmhexpress;i++){
        opertest = expressao[i+1];
        if (expressao[i]=='(' && expressao[i+2] == '('){
            if(opertest == '/'||'*'||'-'||'+'){
                printf ("Invalid Expression");
                return 0;
            }
        }
    }

    for(i=0;i<tmhexpress;i++){
        opertest = expressao[i+1];
        if (expressao[i]==')' && expressao[i+2] == ')'){
            if (opertest == '/'||'*'||'-'||'+'){
                printf ("Invalid Expression");
                return 0;
            }
        }
    }

    for(i=0;i<tmhexpress;i++){
        if (expressao[i] == '(' || expressao[i] == ')'){
            test++;
        }
    }

    if (test%2 != 0){
        printf ("Unbalanced Parenthesis");
        return 0;
    }

return 0;
}
