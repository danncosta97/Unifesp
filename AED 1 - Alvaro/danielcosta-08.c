//Daniel Costa 112185 AED NOTURNO 2017.1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct no
{
    struct no *esq,*dir;
    char letra;
    int frequencia;
}tipo_no;

tipo_no* cria_no(int freq, char letra)
{
    tipo_no *no = (tipo_no*) malloc(sizeof(tipo_no));
    no->dir=NULL;
    no->esq=NULL;
    no->letra = letra;
    no->frequencia = freq;
}

void insere_no (tipo_no *no, int freq, char letra){
    if(freq < no->frequencia)
    {
        if(no->esq!=NULL)
        {
            insere_no(no->esq, freq, letra);
        }
        else
        {
            no->esq = cria_no(freq, letra);
        }
    }
    else
    {
        if(no->dir!=NULL)
        {
            insere_no(no->dir, freq, letra);
        }
        else
        {
            no->dir = cria_no(freq, letra);
        }
    }
}

tipo_no* BuscaAnterior(tipo_no *noaux2, tipo_no *noaux, int freq, char c){

    if(noaux->dir->letra == noaux2->letra || noaux2->esq->letra == noaux->letra){
        return noaux2;
    }

    if (freq < noaux2->frequencia){
        return BuscaAnterior(noaux2->esq, noaux, freq, c);
    }
    else{
        return BuscaAnterior(noaux2->dir, noaux, freq ,c);
    }
}

tipo_no* BuscaArvore(tipo_no *no, int freq, char c){

    if(no==NULL || c==no->letra){
        return no;
    }

    if (freq < no->frequencia){
        return BuscaArvore(no->esq, freq, c);
    }
    else{
        return BuscaArvore(no->dir, freq, c);
    }
}

void remove_no(tipo_no *no, int freq, char a){

    tipo_no *aux, *aux2;

    aux = BuscaArvore(no, freq, a);

    if(aux==NULL){
    }
    else{
        if(aux->dir==NULL && aux->esq==NULL){
            aux=NULL;
        }
        if(aux->dir==NULL && aux->esq!=NULL){
            aux2 = BuscaAnterior(no, aux, freq, a);

        }
    }
}

void imprime_EmOdem(tipo_no *no)
{
    if(no==NULL)
    {
        return;
    }

    imprime_EmOdem(no->esq);
    printf("%c%d ", no->letra,no->frequencia);
    imprime_EmOdem(no->dir);
}

int main()
{
    tipo_no *arvore;

    char stringmain[1024], a, b;
    int i,l,cont=0,contA=0,contB=0,tmh;

    arvore = NULL;

    scanf("%c %c", &a, &b);
    scanf("%s", stringmain);

    tmh = strlen(stringmain);

    for(l=65; l<=90; l++)
    {
        for(i=0; i<tmh; i++)
        {
            if (l==stringmain[i])
            {
                cont++;
            }
        }

        if(l==a){
            contA = cont;
        }
        if(l==b){
            contB = cont;
        }

        if(cont>0)
        {
            if (arvore == NULL)
            {
                arvore = cria_no(cont, l);
            }
            else
            {
                insere_no(arvore, cont, l);
            }
        }

        cont = 0;
    }

    imprime_EmOdem(arvore);

    remove_no(arvore, cont, a);

    imprime_EmOdem(arvore);

    return 0;
}
