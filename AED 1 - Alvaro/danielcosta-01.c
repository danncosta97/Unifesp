//Nome: Daniel Barbosa Silva Costa R.A.: 112185
//AED I Noturno (REOF)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){

    int tmhA=0, tmhB=0, i=0, j=0, contA=0, contB=0;         //Declara as variaveis
    int tmhrealZ=0, contcaract=0;
    char caract;
    char *stringX, *stringY, *stringZ;

    scanf("%d %d %c", &tmhA, &tmhB, &caract);               //Recebe os valores para as variaveis

    stringX = (char*) malloc((tmhA)*sizeof(char*));
    for(i=0;i<tmhA;i++){
        stringX[i] = '\0';
    }
    stringY = (char*) malloc((tmhB)*sizeof(char*));
    for(i=0;i<tmhB;i++){
        stringY[i] = '\0';
    }

    scanf("%s %s", stringX, stringY);                       //Recebe as strings



    for(i=0;i<tmhA;i++){                                    //Se o vetor 'i' da string for uma letra, contado de A
        if(stringX[i] != '\0'){                        //(n de letras na string X) soma 1
             contA++;
        }
    }

    for(i=0;i<tmhB;i++){                                    //Idem ao passo anterior, com variaveis diferentes
        if(stringY[i] != '\0'){
            contB++;
        }
    }



    tmhrealZ=(contA+contB);                                 //Quantidade real de letras, para que possa ser feito o alocamento
    stringZ = (char*) malloc((tmhrealZ)*sizeof(char*)); //da string Z

    for(i=0;i<tmhrealZ;i++){
        stringZ[i] = '\0';
    }

    for(i=0;i<tmhrealZ-contB;i++){                          //Tamanho Real - Tamanho Real de B = Tamanho Real de A
        if(stringX[i] != '\0'){                             //Se a posicao 'i' de X for uma letra, a posicao 'i' de Z
            stringZ[i] = stringX[i];                    //recebe o mesmo conteudo de X em 'i'
        }
    }

    for(i=(tmhrealZ-contB);i<tmhrealZ;i++){                 //Ideam ao passo anterior, com variaveis diferente
        if(stringY[j] != '\0'){
            stringZ[i] = stringY[j];
            j++;
        }
    }

    for(i=0;i<(tmhrealZ);i++){                              //Se for encontrado na string Z alguma ocorrencia do caracter
        if(stringZ[i] == caract){                       //solicitado pelo usuario, o contador soma 1;
            contcaract++;
        }
    }

    stringZ[tmhrealZ] = '\0';                               //Coloca '\0' na ultima posicao da string Z para identificar o final

    printf("%s", stringZ);
    printf("\n%d", tmhrealZ);
    printf("\n%d", contcaract);

return 0;
}
