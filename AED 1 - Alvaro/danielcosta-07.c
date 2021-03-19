//Daniel Barbosa Silva Costa    112185
//AED Noturno 2017.1

#include <stdio.h>
#include <stdlib.h>

typedef struct TipoNo
{
    struct TipoNo *esq,*dir;
    int num;
} TipoNo;

TipoNo *criaNo(int num)
{
    TipoNo *no = malloc(sizeof(TipoNo));
    no->num = 0;
    no->num = num;
    no->dir = NULL;
    no->esq = NULL;
    return no;
}

void insereNo(TipoNo *no, int num)
{
    if(num < no->num)
    {
        if(no->esq!=NULL)
        {
            insereNo(no->esq,num);
        }
        else
        {
            no->esq = criaNo(num);
        }
    }
    else
    {
        if(no->dir!=NULL)
        {
            insereNo(no->dir,num);
        }
        else
        {
            no->dir = criaNo(num);
        }
    }
}

void imprime_preOrdem(TipoNo *no)
{
    if(no==NULL)
    {
        return;
    }
    printf("%d ",no->num);
    imprime_preOrdem(no->esq);
    imprime_preOrdem(no->dir);
}

void imprime_emOrdem(TipoNo *no)
{
    if(no==NULL)
    {
        return;
    }
    imprime_emOrdem(no->esq);
    printf("%d ",no->num);
    imprime_emOrdem(no->dir);
}

void imprime_posOrdem(TipoNo *no)
{
    if(no==NULL)
    {
        return;
    }
    imprime_posOrdem(no->esq);
    imprime_posOrdem(no->dir);
    printf("%d ",no->num);
}

void busca_arvore(TipoNo *no, int x)
{
    printf("%d ", no->num);
    if(no==NULL || x==no->num)
    {
        return no;
    }

    if (x<no->num)
    {
        return busca_arvore(no->esq,x);
    }
    else
    {
        return busca_arvore(no->dir,x);
    }
}

int altura (TipoNo *arvore)
{

    if (arvore == NULL)
        return -1;
    else
    {
        int he = altura (arvore->esq);
        int hd = altura (arvore->dir);
        if (he < hd)
        {
            return hd + 1;
        }
        else
        {
            return he + 1;
        }
    }
}

int main()
{
    TipoNo *arvore;
    int num,qtd,busca,i;

    arvore=NULL;

    scanf("%d %d", &qtd, &busca);

    for(i=0; i<qtd; i++)
    {
        scanf("%d",&num);
        if(arvore==NULL)
        {
            arvore=criaNo(num);
        }
        else
        {
            insereNo(arvore,num);
        }
    }

    imprime_preOrdem(arvore);
    printf("\n");
    imprime_emOrdem(arvore);
    printf("\n");
    imprime_posOrdem(arvore);
    printf("\n");

    busca_arvore(arvore, busca);
    printf("\n");
    printf("%d", altura(arvore));

    return 0;
}
