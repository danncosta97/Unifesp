#include "lista.h"
#include <stdio.h>
int main()
{
    int resposta=1;
    tipoListaES listaAux;
    Inicializa(&listaAux);
    while(resposta!=0){
        printf("\n####################### MENU ##################");
        printf("\nO que deseja..:2-Imprimir,1-Inserir,0-Sair\n");
        printf("###############################################\n");
        scanf("%d",&resposta);
        if(resposta==2)
        {
            Imprima(&listaAux);
        }
        if(resposta==1)
        {
            Insira(&listaAux);
        }
    }
    return 0;
}
