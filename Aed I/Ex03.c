    #include <stdio.h>
    #include <stdlib.h>
    #define N 100
/*********************************************************/ //inicio programa
    typedef struct Time
    {
        int Nome;                                               //Nome do time sera representado por um numero
        int Time_jogados[20];
        int indice_proximo;
    }time;

    typedef struct Lista
    {
        int indice_primeiro;
        int indice_ultimo;
        int qntd;
        time vet[N];
        int livre[N];
    }Lista;

/**************************************************************/
//Funcao para iniciar minha lista
    void inicializa_Lista(Lista *l)
    {
        int i,j;
        l->indice_primeiro=-1;
        l->indice_ultimo=-1;
        l->qntd=0;
        for(i=0; i<N; i++)
        {   for(j=0;j<20;j++){
                l->vet[i].Time_jogados[j]=-2;
            }
            l->vet[i].Nome=-1;
            l->livre[i]=0;
        }
    }
//Funcao para imprimir
    void imprime_Lista(Lista *l,int n)
    {   int i,aux;

        printf("Jogos da %d rodada\n",n);
        aux=l->indice_primeiro;
        for(i=0;i<20;i++){
            printf("Time %d joga com Time ",l->vet[i].Nome);
            i++;
            printf("%d\n",l->vet[i].Nome);
        }
   }

//Funcao para imprimir
   /* void imprime_Lista(Lista *l,int n)
    {   int i,aux,j;

        for(i=0;i<20;i++){
            printf("\nTime %d jogou com os times ",l->vet[i].Nome);
            for(j=0;j<10;j++){
                printf(" %d",l->vet[i].Time_jogados[j]);
            }
        }
    }*/

//Funcao para verificar proxima posicao livre da lista
    int posicao_livre(Lista *l)
    {
        int pos=-1,i=0;
        while(pos==-1 && i<N)
        {
            if(l->livre[i]==0)
            {
                pos=i;
            }
            i++;
        }
        return pos;
    }

    //Funcao para inselir elemento no final
    void insere_Final(Lista *l,int n)
    {
        int pos,ultimo;
        pos=posicao_livre(l);
        if(pos==-1)
        {
            printf("LISTA CHEIA\n");
        }
        else
        {
            l->vet[pos].Nome=n;
            l->vet[pos].indice_proximo=-1;
            l->livre[pos]=1;
            if(l->qntd==0)
            {
                l->indice_primeiro=pos;
                l->indice_ultimo=pos;
                l->qntd++;
            }
            else
            {
                ultimo=l->indice_ultimo;
                l->vet[ultimo].indice_proximo=pos;
                l->indice_ultimo=pos;
                l->qntd++;
            }
        }
    }
    void Concatena(Lista *l ,int a ,int b){

        int i;
        time Aux;
        if(b>a)
            b--;
        //comcatenar em relacao "a"
        Aux=l->vet[a];
        for(i=a;i<19;i++){
            l->vet[i]=l->vet[i+1];
        }
        l->vet[19]=Aux;
       //comcatenar em relacao "b"
        Aux=l->vet[b];
        for(i=b;i<19;i++){
            l->vet[i]=l->vet[i+1];
        }
        l->vet[19]=Aux;
    }

    int Jodou_ou_jogou(Lista *l ,int a ,int b ,int n){

        int i=0;
        while(i!=n){
            if(l->vet[a].Time_jogados[i]==l->vet[b].Nome){
                return 1;
            }
            i++;
        }
        return 0;
    }
    /**********************************************************************/
    //Funcao main
    int main()
    {
        int n,i,j,k,cont=0,placa,indice,elemento,Aux,a=0,b=0,Jodou_ou_jogou_main=1; //Declaraçao de variaveis da main
        char EouS;
        Lista l;

        inicializa_Lista(&l);

        for(i=1;i<21;i++){
            insere_Final(&l,i);
        }

        Aux=20;
        for(i=0;i<2;i++){
            for(j=0;j<10;j++){
                Jodou_ou_jogou_main=1;
                a=0;
                b=0;

                while(a==b || Jodou_ou_jogou_main==1){
                                //Quando sair do while entao eles nao jogaram ainda
                    a=rand()%Aux;
                    b=rand()%Aux;
                    Jodou_ou_jogou_main = Jodou_ou_jogou(&l,a,b,i+1);
                }
                l.vet[a].Time_jogados[i]= l.vet[b].Nome;
                l.vet[b].Time_jogados[i]= l.vet[a].Nome;
                Concatena(&l,a,b);
                Aux--;
                Aux--;
            }
            imprime_Lista(&l,i+1);

             Aux=20;
         }


    return 0; // fim programa
    }
