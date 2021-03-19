//Nome: Daniel Barbosa Silva Costa      R.A.: 112185
//AED Noturno 2017/1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct dados{
    char dado;
}tipo_dado;

typedef struct lista{
    tipo_dado *info;
    int qtd;
}tipo_lista;

void inicializa(tipo_lista *lista_auxilixar, int tmh){
    lista_auxilixar->info = malloc(tmh*sizeof(tipo_dado));
    lista_auxilixar->qtd = 0;
}

int verificacao(char *string, int tmhstring){
    int i, test=0;
    char opertest='\0';

    for(i=0;i<tmhstring;i++){
        opertest = string[i+1];
        if (string[i]=='(' && string[i+2] == '('){
            if(opertest == '/'||'*'||'-'||'+'){
                printf ("Invalid Expression");
                return 0;
            }
        }
    }

    for(i=0;i<tmhstring;i++){
        opertest = string[i+1];
        if (string[i]==')' && string[i+2] == ')'){
            if (opertest == '/'||'*'||'-'||'+'){
                printf ("Invalid Expression");
                return 0;
            }
        }
    }

    for(i=0;i<tmhstring;i++){
        if (string[i] == '(' || string[i] == ')'){
            test++;
        }
    }

    if (test%2 != 0){
        printf ("Unbalanced Parenthesis");
        return 0;
    }


}

void string_para_lista(tipo_lista *lista_auxiliar, char *string, int tmh){
    int i;

    lista_auxiliar->info[0].dado = '(';
    lista_auxiliar->info[tmh-1].dado = ')';

    for(i=0;i<tmh-2;i++){
        lista_auxiliar->info[i+1].dado = string[i];
    }

    for(i=0;i<tmh;i++){
        printf("%c",lista_auxiliar->info[i].dado);
    }
}

void infix_para_rpn(tipo_lista *lista_auxiliar, int tmh){
    int i=0, valuek=0, j=0, k=0, l=0, m=0, pos=0, posaux=0, qtdoper=0, qtdparesq=0, posparesq = 0 ;

    tipo_lista lista_operador, lista_rpn;

    for(i=0;i<tmh;i++){
        if (lista_auxiliar->info[i].dado<48 || lista_auxiliar->info[i].dado>57){
            qtdoper++;
        }
    }
    printf("\nWTF%d\n", qtdoper);

    for(i=0;i<tmh;i++){
        if (lista_auxiliar->info[i].dado==')'){
            qtdparesq++;
        }
    }

    lista_operador.info = malloc(qtdoper*sizeof(tipo_dado));
    lista_rpn.info = malloc(tmh*sizeof(tipo_dado));
    posparesq = malloc(qtdparesq*sizeof(int));

    /*for(i=0;i<tmh;i++){
        if (lista_auxiliar->info[i].dado==')'){
            posparesq[j] = i;
            j++;
        }
    }*/

    j=0;

    for (i=0;i<tmh;i++){
        lista_operador.info[i].dado = '\0';
    }
    for (i=0;i<tmh;i++){
        lista_rpn.info[i].dado = '\0';
    }



    for(i=0;i<tmh;i++){
        printf("%c",lista_operador.info[i].dado);
    }

    printf("\n\n");

    for (i=0;i<tmh;i++){

        if (lista_auxiliar->info[i].dado<48 || lista_auxiliar->info[i].dado>57){
            lista_operador.info[j].dado = lista_auxiliar->info[i].dado;
            j++;
        }

        if (lista_auxiliar->info[i].dado>=48 && lista_auxiliar->info[i].dado<=57){
            lista_rpn.info[pos].dado = lista_auxiliar->info[i].dado;
            pos++;
        }

        for (k=0;k<qtdoper;k++){
            for (l=0;l<qtdoper;l++){
                if (lista_operador.info[k].dado=='(' && lista_operador.info[l].dado==')'){
                    valuek = k;
                    for (k=valuek+1;k<l;k++){
                        lista_rpn.info[pos].dado = lista_operador.info[k].dado;
                        pos++;
                    }
                    for (k=valuek;k<=l;k++){
                        lista_operador.info[k].dado = '\0';
                        lista_operador.info[k].dado = lista_operador.info[k+1].dado;
                    }
                }
            }
        }
    }

    for(i=0;i<tmh;i++){
        printf("%c",lista_rpn.info[i].dado);
    }
}

int main(){
    int i=0,tmhexpress=0;
    char expressao[1024];

    for(i=0;i<1024;i++){
        expressao[i]='\0';
    }
    scanf("%s", expressao);

    for(i=0;i<1024;i++){
        if (expressao[i]!='\0')
            tmhexpress++;
        else break;
    }

    if (tmhexpress<=2){
        printf ("Invalid Expression");
        return 0;
    }

    tmhexpress+=2;

    verificacao(expressao, tmhexpress);

    tipo_lista lista_main;
    inicializa(&lista_main, tmhexpress);
    string_para_lista(&lista_main, expressao, tmhexpress);
    infix_para_rpn(&lista_main, tmhexpress);
return 0;
}
