#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/************************************************/
struct aluno

{
    char nome[15] ;
    int matricula;
    float prova[3];

    struct aluno *prox;

};

typedef struct aluno tipoAluno;


struct listaDE

{

    tipoAluno *primeiro;

    tipoAluno *ultimo;

    int tamanhoLista;

};

typedef struct listaDE tipoLDE;


void inicializaLista(tipoLDE*);
void insereElemento(tipoLDE*,tipoAluno*);
void mostraLista(tipoLDE*);

/************************************************/
void inicializaLista (tipoLDE *listaAux)
{
    listaAux->primeiro = NULL;

    listaAux->ultimo = NULL;

    listaAux->tamanhoLista=0;
}
void insereElemento(tipoLDE *listaAux,tipoAluno *alunoAux2)
{
    int i;
    tipoAluno *aluno =(tipoAluno*) malloc(sizeof(tipoAluno));
    strcpy(aluno->nome, alunoAux2->nome);
    aluno->matricula=alunoAux2->matricula;
    aluno->prova[0]=alunoAux2->prova[0];
    aluno->prova[1]=alunoAux2->prova[1];
    aluno->prova[2]=alunoAux2->prova[2];
    tipoAluno *alunoTeste=listaAux->primeiro;
    if (listaAux->tamanhoLista == 0)
    {
        aluno->prox = NULL;
        listaAux->primeiro= aluno;
        listaAux->ultimo= aluno;
    }
    float media;

    tipoAluno *cont = listaAux->primeiro;
    tipoAluno *cont2 = listaAux->primeiro;

    media = (aluno->prova[0]+aluno->prova[1]+aluno->prova[2])/3;

        for(i=0; i<listaAux->tamanhoLista; i++)
        {
            if(i==0)
            {
                if((cont->prova[0]+cont->prova[1]+cont->prova[2])/3 < media)
                {
                    aluno->prox = listaAux->primeiro;
                    listaAux->primeiro = aluno;
                    media = 0;
                    i = listaAux->tamanhoLista;
                }
            }
            else if((cont->prova[0]+cont->prova[1]+cont->prova[2])/3 < media)
            {
                aluno->prox = cont;
                cont2->prox = aluno;

                media = 0;
            }
            cont2 = cont;
            cont = cont->prox;
        }

        if(media != 0)
        {
            aluno->prox = NULL;
            listaAux->ultimo->prox = aluno;
            listaAux->ultimo = aluno;
        }
    listaAux->tamanhoLista++;

}
void mostraLista(tipoLDE *listaAux)
{
    int i;
    float media;
    int teste,media2;
    tipoAluno *pontAux;
    pontAux=listaAux->primeiro;
    for( i=0;i<listaAux->tamanhoLista;i++)
    {
        printf("%s ", (pontAux->nome));
        printf( "%d ", (pontAux->matricula));
        media = (pontAux->prova[0] + pontAux->prova[1] +pontAux->prova[2]) /3;
        teste = (media*10)/5;

        media2=media;
        media=media2;

        if(teste%2 == 0)
        {
            printf("%.1f\n",media);
        }
        else
        {
            media = media + 1;
            printf("%.1f\n",media);
        }
        pontAux=pontAux->prox;
    }
}
/************************************************/
int main()
{
    int n,i;
    tipoLDE listaAux;
    inicializaLista(&listaAux);
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        tipoAluno alunoAux;
        scanf("%s %d %f %f %f",alunoAux.nome,&alunoAux.matricula,&alunoAux.prova[0],&alunoAux.prova[1],&alunoAux.prova[2]);
        if(((alunoAux.prova[0]+alunoAux.prova[1]+alunoAux.prova[2])/3)>=5)
        {
        insereElemento(&listaAux,&alunoAux);
        }
    }
    mostraLista(&listaAux);

    return 0;
}
