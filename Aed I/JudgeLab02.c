#include <stdio.h>
#include <stdlib.h>

struct info{
    char nome[15];
    int ra;
    float prova[3];
    struct info *proximo;
};
typedef struct info tipoAluno;

struct lista{
    tipoAluno *primeiro;
    tipoAluno *ultimo;
    int tamanholista;
};
typedef struct lista listaDE;

void inicializaLista (listaDE *listaAux);
void insereAluno (listaDE *listaAux, tipoAluno *aluno);
/**********************************************************************/

void inicializaLista (listaDE *listaAux){
    listaAux->primeiro = NULL;
    listaAux->ultimo = NULL;
    listaAux->tamanholista=0;
}

void insereAluno (listaDE *listaAux, tipoAluno *aluno){
    int i;
    float media, media1, media2;

    // Alocando espaço
    tipoAluno *novoAluno = (tipoAluno*) malloc(sizeof(tipoAluno));

    // Atribuindo os dados
    for (i=0;i<15;i++){
        novoAluno->nome[i] = aluno->nome[i];
    }
    novoAluno->ra = aluno->ra;
    for (i=0;i<3;i++){
        novoAluno->prova[i] = aluno->prova[i];
    }

    media = (novoAluno->prova[0]+novoAluno->prova[1]+novoAluno->prova[2])/3;

    //inserindo o aluno
    if (listaAux->tamanholista == 0){
        novoAluno->proximo = NULL;
        listaAux->primeiro = novoAluno;
        listaAux->ultimo = novoAluno;
    }
    else {
        novoAluno->proximo = NULL;
        listaAux->ultimo->proximo = novoAluno;
        listaAux->ultimo = novoAluno;
    }

    //declarando alunos para comparacao de me'dias
    tipoAluno *alunoAux1 = listaAux->primeiro;
    media1 = (alunoAux1->prova[0]+alunoAux1->prova[1]+alunoAux1->prova[2])/3;
    tipoAluno *alunoAux2 = listaAux->primeiro;
    media2 = (alunoAux2->prova[0]+alunoAux2->prova[1]+alunoAux2->prova[2])/3;

    //ordenando em funcao das me'dias finais
    for(i=0; i<listaAux->tamanholista; i++){
        if(i==0){
            if(media1 < media){
                novoAluno->proximo = listaAux->primeiro;
                listaAux->primeiro = novoAluno;
                media = 0;
                i = listaAux->tamanholista;
            }
        }
        else{
            if(media2 < media){
                novoAluno->proximo = alunoAux1;
                alunoAux2->proximo = novoAluno;
                media = 0;
            }
        }

        if(media != 0)
        {
            novoAluno->proximo = NULL;
            listaAux->ultimo->proximo = novoAluno;
            listaAux->ultimo = novoAluno;
        }

        alunoAux2 = alunoAux1;
        alunoAux1 = alunoAux1->proximo;
    }

    //soma +1 no tamanho da lista
    listaAux->tamanholista++;
}

void imprimeLista(listaDE *listaAux)
{
    int i, test, mediaarrend;
    float mediafinal;

    tipoAluno *assistAluno;

    assistAluno = listaAux -> primeiro;

    for(i=0;i<listaAux->tamanholista;i++)
    {
        printf("%s %d ", assistAluno->nome, assistAluno->ra);
        mediafinal = (assistAluno->prova[0] + assistAluno->prova[1] + assistAluno->prova[2]) /3;
        mediaarrend = mediafinal;
        mediafinal = mediaarrend;

        //verifica o arredondamento
        test = (mediafinal*10)/5;
        if(test%2 == 0)
        {
            printf("%.1f\n",mediafinal);
        }
        else
        {
            mediafinal = mediafinal + 1;
            printf("%.1f\n",mediafinal);
        }
    assistAluno=assistAluno->proximo;
    }
}

/********************************************/

int main(){
    int n,i;
    listaDE listaAux;
    inicializaLista(&listaAux);

    scanf("%d",&n);

    for(i=0;i<n;i++)
    {
        tipoAluno aluno;
        scanf("%s %d %f %f %f",aluno.nome,&aluno.ra,&aluno.prova[0],&aluno.prova[1],&aluno.prova[2]);
        if(((aluno.prova[0]+aluno.prova[1]+aluno.prova[2])/3)>=5)
        {
            insereAluno(&listaAux,&aluno);
        }
    }
    imprimeLista(&listaAux);

return 0;
}
