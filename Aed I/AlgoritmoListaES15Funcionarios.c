#include <stdlib.h>
#include <stdio.h>
#define MAX 15

//Struct com dados do funcionario
struct info{
    char nome[15];
    int pay;
};
typedef struct info tipofuncionario;

//Struct com dados da lista
struct listaES{
    tipofuncionario ultimo;
    int tmh;
    tipofuncionario lista[MAX];
};
typedef struct listaES tipoListaES;

//Funcao para iniciar a lista
void inicializa_lista (tipoListaES* listaAux){
    int i;

    //zera o salario da lista
    for(i=0;i<MAX;i++){
        listaAux->lista[i].pay = 0;
    }

    //zera tamanho
    listaAux->tmh=0;
}

void registra_funcionario (tipoListaES* listaAux){
    tipofuncionario x;

    //coleta os dados do funcionario
    printf("Digite o nome (sem espacos) e o salario ");
    scanf("%s %d",x.nome,&x.pay);

    //envia os dados coletados para a ultima posicao vetor da lista
    listaAux->lista[listaAux->tmh] = x;

    //atualiza tamanho
    listaAux->tmh++;

    //atualiza o ultimo
    listaAux->ultimo = x;
}

void ordena_salario (tipoListaES *listaAux){
    int i;

    tipofuncionario aux1, aux2;

    aux1 = listaAux->lista[listaAux->tmh];

    for (i=0; i<=listaAux->tmh; i++){
        if(aux1.pay < listaAux->lista[i].pay){
            aux2 = listaAux->lista[i];
            listaAux->lista[i] = listaAux->lista[listaAux->tmh];
            listaAux->lista[listaAux->tmh] = aux2;
        }
    }
}

int main(){
    int i,qtd,qtd1;
    tipoListaES listagem;

    printf ("Qnts funcionarios deseja inserir ? ");
    scanf ("%d", &qtd1);

    qtd = qtd1;

    inicializa_lista (&listagem);

    while(qtd>0){
        registra_funcionario (&listagem);

        qtd--;
    }

    ordena_salario (&listagem);

    for(i=0;i<qtd1;i++){
        printf ("\n");
        printf ("Funcionario: %s \nSlaraio: %d", listagem.lista[i].nome, listagem.lista[i].pay);
    }

return 0;
}
