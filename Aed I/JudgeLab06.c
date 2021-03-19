#include <stdio.h>
#include <stdlib.h>

typedef struct info{

    char info;
    struct info *ant;

}tipo_info;

typedef struct pilha{

    int tamanho_pilha;
    tipo_info *base;
    tipo_info *topo;

}tipo_pilha;

void inicia_pilha (tipo_pilha *pilhaAux){

    pilhaAux->base=NULL;
    pilhaAux->topo=NULL;
    pilhaAux->tamanho_pilha=0;

}

int pilha_vazia (tipo_pilha *pilhaAux){

    if ((pilhaAux->base == pilhaAux->topo) && (pilhaAux->topo == NULL)){
        return 1;
    }
    else{
        return 0;
    }

}

void calculadora (tipo_pilha *pilhaAux, char info){

    int x,y;

    tipo_info *informacao = (tipo_info*) malloc (sizeof(tipo_info));

    informacao->info = info;

    switch (info){

        case 'E':
                if (pilha_vazia (pilhaAux) == 1){
                    informacao->info = 48;
                    informacao->ant = NULL;
                    pilhaAux->base = informacao;
                    pilhaAux->topo = informacao;
                }

                else{
                    informacao->info = 48;
                    informacao->ant = pilhaAux->topo;
                    pilhaAux->topo = informacao;
                }



        case '0'||'1'||'2'||'3'||'4'||'5'||'6'||'7'||'8'||'9':
                    x = info-48;
                    y = pilhaAux->topo->info;
                    informacao->info = ((y*10) + x);
                    informacao->ant = pilhaAux->topo;
                    pilhaAux->topo = informacao;

                    pilhaAux->tamanho_pilha++;

        case '+':
                    x = pilhaAux->topo->info;
                    y = pilhaAux->topo->ant->info;
                    pilhaAux->topo = NULL;
                    pilhaAux->topo->ant->info = x+y;
                    printf("%d", pilhaAux->topo->ant->info);


    }
}

int main(){
    char ch;
    tipo_pilha pilha_main;
    inicia_pilha (&pilha_main);

    for(;;){
        scanf("%c", &ch);
        calculadora (&pilha_main, ch);
        if(ch=='C')
                break;
    }

return 0;
}
