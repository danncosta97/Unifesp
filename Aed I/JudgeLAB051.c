#include <stdio.h>
#include <stdlib.h>

typedef struct info{

    int duracao;
    struct info *prox;
    struct info *ant;

}temp_lig;

typedef struct fila{

    int tamanho_fila;
    temp_lig *primeiro;
    temp_lig *ultimo;

}tipo_fila;

void inicia_fila (tipo_fila *filaAux){

    filaAux->primeiro=NULL;
    filaAux->ultimo=NULL;
    filaAux->tamanho_fila=0;

}

//verifica se a lista esta vazia e se estiver retorna 1, senao retorna 0
int lista_vazia (tipo_fila *filaAux){

    if ((filaAux->primeiro == filaAux->ultimo) && (filaAux->ultimo == NULL)){
        return 1;
    }
    else{
        return 0;
    }

}

void insere_ultimo (tipo_fila *filaAux){

    int duracao;

    //aloca espaco do tamanho de 'temp_lig' na memoria
    temp_lig *nlig = (temp_lig*) malloc (sizeof(temp_lig));

    printf ("digite o tempo da chamada ");
    scanf("%d", &duracao);

    nlig->duracao = duracao;

    if (lista_vazia (filaAux) == 1){         //casso de lista vazia
        nlig->prox = nlig;
        nlig->ant = nlig;
        filaAux->primeiro = nlig;
        filaAux->ultimo = nlig;             //apenas 1 elemento, apontando para ele mesmo
    }
    else{
        nlig->prox = filaAux->primeiro;     //fila circular
        nlig->ant = filaAux->ultimo;
        filaAux->primeiro->ant = nlig;      //fila circular
        filaAux->ultimo->prox = nlig;       //futuro penultimo apota para o ultimo
        filaAux->ultimo = nlig;             //nlig entra na ultima posicao
    }

    filaAux->tamanho_fila++;                //aumento o tamanho da fila no contador
}

void retira_primeiro (tipo_fila *filaAux){
    //rearranja os ponteiros
    //faz o segundo apontar para o ultimo e o ultimo aportar para o segundo
    //por fim faz do segundo elemento, o primeiro da fila
    filaAux->primeiro->prox->ant = filaAux->ultimo;
    filaAux->ultimo->prox = filaAux->primeiro->prox;
    filaAux->primeiro = filaAux->primeiro->prox;

}

int main(){

    int i, qtd_vend, qtd_lig, aux, v[100], cont[100];

    for(i=0;i<100;i++){
        cont[i] = 0;                            //zera o tempo restante de cada vendedor
    }

    tipo_fila fila_main;

    inicia_fila (&fila_main);

    printf("digite qtd Vends e qtd de Ligs ");
    scanf("%d %d", &qtd_vend, &qtd_lig);

    for(i=0;i<qtd_lig;i++){
        insere_ultimo(&fila_main);              //insercao da duracao das chamadas em uma fila
    }

    for(i=0;i<qtd_vend;i++){
        v[i] = fila_main.primeiro->duracao;     //i-esima duracao na fila é passado ao i-esimo vendedor
        cont[i]++;                              //soma 1 na qtd de chamadas do i-esimo vendedor
        retira_primeiro(&fila_main);            //retira a primeira chamada da lista
        qtd_lig--;                              //diminui a qtd de chamadas restantes em 1
        if(qtd_lig==0){                         //caso o numero de chamdas seja menor q o numero de vededores, cairá nessa condicao
            for(i=0;i<qtd_vend;i++)
                printf("\n%d %d", i+1, cont[i]);
            return 0;//finaliza o programa
        }
    }
    printf("passou");


    for(;;){                                         //for infinito com condicoes internas
        for(i=0;i<qtd_vend;i++){
            v[i]--;                                 //tempo restante de chamda do vendedor i-esimo diminui em 1
            if(v[i] == 0){                          //caso o i-esimo vendedor acabe uma chamada
                v[i] = fila_main.primeiro->duracao; //o i-esimo vendedor recebera a primeira chamada disponivel
                retira_primeiro(&fila_main);        //retira a chamda passada da lista
                cont[i]++;                          //add +1 na qtd de chamdas do i-esimo vendedor
                qtd_lig--;                          //diminui a qtd de chamadas restantes em 1
                if(qtd_lig==0){                     //caso n haja mais chamdas disponiveis, sai do laco
                    break;
                }
            }
        }
        if(qtd_lig==0){                             //caso n haja mais chamdas disponiveis, sai do laco infinito
            break;
        }
    }

    for(i=0;i<qtd_vend;i++)                         //printa o vendedor e a qtd de chamadas realizadas
        printf("\n%d %d", i+1, cont[i]);

return 0;
}
