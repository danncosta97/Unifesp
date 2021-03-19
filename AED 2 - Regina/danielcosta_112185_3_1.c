    //Daniel Costa 112185
    //AED 2 Regina 2018.1 Exercicio 3 (arvore binaria de busca)

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <math.h>

    typedef struct no{
        struct no *esq,*dir;
        int valor;
    } tipo_no;

    tipo_no* cria_no(int valor){
        tipo_no *no=(tipo_no*)malloc(sizeof(tipo_no));
        no->esq=NULL;no->dir=NULL;
        no->valor=valor;
        return no;
    }

    void insere_no(tipo_no *no,int valor){

        if(valor < no->valor){
            if(no->esq!=NULL){
                insere_no(no->esq,valor);
            }
            else{
                no->esq = cria_no(valor);
            }
        }
        else{
            if(no->dir!=NULL){
                insere_no(no->dir,valor);
            }
            else{
                no->dir = cria_no(valor);
            }
        }
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
                insere_no(arvore,x);
            scanf("%d",&x);
        }

        scanf("%d",&busca);

        if(busca_arvore(arvore,busca)==NULL){
            insere_no(arvore,busca);
        }
        else{
            arvore = remove_no(arvore,busca);
        }


        imprime_preOrdem(arvore);
        printf("\n");
        imprime_emOrdem(arvore);
        printf("\n");

    return 0;
    }
