//Daniel Costa 112185
//AED 2 Regina 2018.1 Exercicio 4 (Arvore AVL)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct no{
    struct no *esq,*dir;
    int valor;
    int fb;
} tipo_no;

tipo_no* cria_no(int valor){
    tipo_no *no=(tipo_no*)malloc(sizeof(tipo_no));
    no->esq=NULL;no->dir=NULL;
    no->valor=valor;
    no->fb=0;
    return no;
}

int altura(tipo_no *arvore){
    if (arvore == NULL)
        return -1;
    else
    {
        int he = altura (arvore->esq);
        int hd = altura (arvore->dir);
        if (he < hd)
        {
            return (hd+1);
        }
        else
        {
            return (he+1);
        }
    }
}

int fator_Balanceamento(tipo_no *no){
    if(no==NULL){
        return 0;
    }
    else{
        int l=0,r=0;
        l = altura(no->esq);
        r = altura(no->dir);
        return (l-r);
    }
}

tipo_no* rotaciona_dir(tipo_no *no){
    tipo_no *pA = no, *pB;
    pB = pA->esq;
    pA->esq = pB->dir;
    pB->dir = pA;
    pA = pB;

    return pA;
}

tipo_no* rotaciona_esq(tipo_no *no){
    tipo_no *pA = no, *pB;
    pB = pA->dir;
    pA->dir = pB->esq;
    pB->esq = pA;
    pA = pB;
    return pA;
}

tipo_no* rotaciona_dupla_dir(tipo_no *no){
    tipo_no *pA = no, *pB, *pC;

    pB = pA->esq;
    pC = pB->dir;
    pB->dir = pC->esq;
    pC->esq = pB;
    pA->esq = pC->dir;
    pC->dir = pA;
    pA = pC;

    return pA;
}

tipo_no* rotaciona_dupla_esq(tipo_no *no){
    tipo_no *pA = no, *pB, *pC;

    pB = pA->dir;
    pC = pB->esq;
    pB->esq = pC->dir;
    pC->dir = pB;
    pA->dir = pC->esq;
    pC->esq = pA;
    pA = pC;

    return pA;
}

tipo_no* insere_no(tipo_no *no,int valor){

    if(no==NULL){
        return cria_no(valor);
    }

    if(valor < no->valor){
        no->esq = insere_no(no->esq,valor);
    }
    else{
        no->dir = insere_no(no->dir,valor);
    }

    no->fb = fator_Balanceamento(no);

    if(no->fb>1){
        if(no->esq->fb>=0){
            return rotaciona_dir(no);
        }
        else{
            return rotaciona_dupla_dir(no);
        }
    }

    if(no->fb<-1){
        if(no->dir->fb<=0){
            return rotaciona_esq(no);
        }
        else{
            return rotaciona_dupla_esq(no);
        }
    }

return no;
}

tipo_no* busca_arvore(tipo_no *no, int valor){

    if(no == NULL || valor == no->valor){
        return no;
    }

    if (valor < no->valor){
        return busca_arvore(no->esq,valor);
    }
    else{
        return busca_arvore(no->dir,valor);
    }
}

tipo_no* menorSubDir(tipo_no *no){

    tipo_no *aux = no->dir;

    while(aux->esq!=NULL){
        aux=aux->esq;
    }

    return aux;
}

tipo_no* remove_no(tipo_no *no, int valor){
    if (no == NULL){
        return no;
    }

    if (valor < no->valor){
        no->esq = remove_no(no->esq, valor);
    }
    else if (valor > no->valor){
        no->dir = remove_no(no->dir, valor);
    }

    else{
        if (no->esq == NULL && no->dir == NULL){
            free(no);
            no = NULL;
        }
        else if (no->esq == NULL){
            tipo_no *temp = no;
            no = no->dir;
            free(temp);
        }
        else if (no->dir == NULL) {
            tipo_no *temp = no;
            no = no->esq;
            free(temp);
        }
        else {
            tipo_no *temp = menorSubDir(no);
            no->valor = temp->valor;
            no->dir = remove_no(no->dir, temp->valor);
        }
        return no;
    }

    no->fb = fator_Balanceamento(no);

    if(no->fb>1){
        if(no->esq->fb>=0){
            return rotaciona_dir(no);
        }
        else{
            return rotaciona_dupla_dir(no);
        }
    }

    if(no->fb<-1){
        if(no->dir->fb<=0){
            return rotaciona_esq(no);
        }
        else{
            return rotaciona_dupla_esq(no);
        }
    }

return no;
}

void imprime_preOrdem(tipo_no *no){
    if(no==NULL){
        return;
    }
    printf("%d ",no->valor);
    imprime_preOrdem(no->esq);
    imprime_preOrdem(no->dir);
}

void imprime_emOrdem(tipo_no *no){
    if(no==NULL){
        return;
    }
    imprime_emOrdem(no->esq);
    printf("%d ", no->valor);
    imprime_emOrdem(no->dir);
}

int main(){
    tipo_no *arvore=NULL;
    int x=0,qtd=0,busca=0,i=0;


    scanf("%d",&x);
    while(x>=0){
        if(arvore==NULL)
            arvore=cria_no(x);
        else
            arvore = insere_no(arvore,x);
        scanf("%d",&x);
    }
    imprime_preOrdem(arvore);
    printf("\n");
    printf("%d",altura(arvore));
    printf("\n");


    scanf("%d",&x);
    while(x>=0){
        arvore = remove_no(arvore,x);
        scanf("%d",&x);
    }
    imprime_preOrdem(arvore);
    printf("\n");
    printf("%d",altura(arvore));

return 0;
}
