    #include <stdio.h>
    #include <stdlib.h>

    /***********************TAD.h**************************/

    typedef struct Info{
        int altura;
        struct Info *prox;
        struct Info *ant;
    }info;

    typedef struct Lista{
        info *primeiro;
        info *ultimo;
        int tamanho_lista;
    }lista;

    /**********************TAD.c*******************************/

    void iniciar (lista *l){
        l->primeiro = NULL;
        l->ultimo = NULL;
        l->tamanho_lista = 0;
    }

    void insere (lista *l){

        //aloca espaco na memoria

        int altura;

        scanf("%d", &altura);

        info* novo = (info*) malloc (sizeof(info));
        novo->altura = altura;

        //inserindo elementos, se a lista estiver vazia
        if (l->tamanho_lista == 0){
            novo->prox = novo;
            novo->ant = novo;
            l->primeiro = novo;
            l->ultimo = novo;

        }
        //inserindo elementos
        else{
            novo->prox = l->primeiro;
            novo->ant = l->ultimo;
            l->primeiro->ant = novo;
            l->ultimo->prox = novo;
            l->ultimo = novo;
        }

        //aumenta o tamanho da lista
        l->tamanho_lista++;
    }

    info* busca_maior (lista *l){
        //declara struct aux para comparar com struct Maior
        info *aux, *Maior;

        int i;

        aux = l->primeiro;
        Maior = l->primeiro;

        //percorre a lista atualizando o aux para o proximo
        for(i=0;i<l->tamanho_lista;i++){
            if(aux->altura > Maior->altura){
                Maior = aux;
            }
            aux = aux->prox;
        }
        //retorna o maior elemento
    return Maior;
    }

    info* busca_menor (lista *l){
        //declara struct aux para comparar com struct Menor
        info *aux, *Menor;
        int i;

        aux = l->primeiro;
        Menor = l->primeiro;

        //percorre a lista atualizando o aux para o proximo
        for(i=0;i<l->tamanho_lista;i++){
            if(aux->altura < Menor->altura){
                Menor = aux;
            }
            aux = aux->prox;
        }
        //retorna o menor elemento
    return Menor;
    }

    void retira (lista *l, info *elemento_pra_retirar){
        //retira o elemento passado como parametro e rearranja os enderecos apontados

        info *elemento_anterior, *elemento_posterior;

        if (elemento_pra_retirar == l->primeiro){
            l->primeiro = elemento_pra_retirar->prox;
        }

        elemento_pra_retirar->ant = elemento_pra_retirar->prox;

        elemento_pra_retirar->prox = elemento_pra_retirar->ant;

        free(elemento_pra_retirar);
        l->tamanho_lista--;
    }

    /***********************main.c******************************/

    int main(){

        int i, qtd_aluno=0;
        float q;

        lista lista_main;
        info *maior, *menor;

        iniciar (&lista_main);

        scanf("%d", &qtd_aluno);

        for (i=0; i<qtd_aluno; i++){
            insere (&lista_main);
        }

        q=lista_main.tamanho_lista/2.0;

        for (i=0;i<q; i++){
            if(lista_main.tamanho_lista==1){
               printf("%d",lista_main.primeiro->altura);
            }else{
            maior = busca_maior(&lista_main);
            printf("%d ", maior->altura);
            retira (&lista_main, maior);

            menor = busca_menor(&lista_main);
            printf("%d ", menor->altura);
            retira (&lista_main, menor);
            }
        }

    return 0;
    }
