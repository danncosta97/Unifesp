#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (){
    int i, tmh, cont;                           //i -> gene'rico, tmh -> tamanho frase, cont -> contador
    char stringA[256], cmp;                     //stringA -> string, cmp-> caraacter de compara��o (ser� iniciado em 65, 'A' ASCII)

    printf("Digite um frase: ");
    gets(stringA);                              //Conta os espa�os tbm, apesar de n reconhecer tamanho max armazenado

    tmh = strlen(stringA);                      //tmh da frase

    for (i=0;i<tmh;i++){
        stringA[i] = toupper(stringA[i]);       //Deixa tudo maiusculo
    }

    cmp=65;                                     //cmp (variavel char) recebe 65. Como � char, recebera o caracter na posicao 65
                                            //na tabela ASCII na base decimal, no casa o 'A'

    while (cmp<91){                             //Inicia-se o laco com cmp em 'A' (65)
        cont = 0;                               //Zera-se o contador
        for (i=0;i<tmh;i++){                    //Varia 'i' de 0 at� o tamanho da frase
            if (stringA[i] == cmp){             //Tomando como base i=0, ir� comparar stringA[0] com cmp=65 ('A'). Se stringA[0]
                cont++;                     //for A (65 - ASCII) o cont soma 1. Repete o la�o 'for' e agora i soma 1. Repete o
            }                               //procedimento, agora comparando cmp=65 ('A') com stringA[1]
        }
        printf ("%c -> %d\n", cmp, cont);       //Nesse ponto cmp=65 ('A') j� ter� sido comparado com toda a frase. Printa A e a qtd na frase
        cmp++;                                  //Soma-se 1 ao cmp, que � 'char', ent�o teremos cmp=66, caracter 'B' ASCII
    }                                           //Repete la�o while e verifica a condi��o imposta.

return 0;
}
