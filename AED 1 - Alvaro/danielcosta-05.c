        //Daniel Barbosa Silva Costa    112185
        //AED Noturno 2017.1

        #include <stdio.h>
        #include <stdlib.h>
        #include <string.h>

        typedef struct base
        {
            char basenitrogenada;
            struct base *prox;
            struct base *ant;
        } tipo_base;

        typedef struct lista_dupla_encad
        {
            tipo_base *primeiro;
            tipo_base *ultimo;
            int tamanho;
        } tipo_lista;

        void inicia_lista (tipo_lista *lista_aux)
        {
            lista_aux->primeiro=NULL;
            lista_aux->ultimo=NULL;
            lista_aux->tamanho=0;
        }

        int lista_vazia (tipo_lista *lista_aux)
        {
            if (lista_aux->primeiro == NULL && lista_aux->ultimo == NULL)
            {
                return 1;
            }
            else
                return 0;
        }

        void insere_base (tipo_lista *lista_aux, char base_void)
        {

            tipo_base *nova_base = malloc(sizeof(tipo_base));

            nova_base->basenitrogenada=0;
            nova_base->basenitrogenada = base_void;

            if(lista_vazia(lista_aux) == 1)
            {
                nova_base->prox = NULL;
                nova_base->ant = NULL;
                lista_aux->primeiro = nova_base;
                lista_aux->ultimo = nova_base;
            }
            else
            {
                nova_base->prox=NULL;
                nova_base->ant=lista_aux->ultimo;
                lista_aux->ultimo->prox = nova_base;
                lista_aux->ultimo = nova_base;
            }
            lista_aux->tamanho++;
        }
        void remove_base (tipo_lista *lista_Aux, tipo_base *base_remove)
        {

            tipo_base  *aux;

            if(base_remove->ant==NULL)
            {
                lista_Aux->primeiro=base_remove->prox;
                lista_Aux->primeiro->ant=NULL;
                free(base_remove);
            }
            else
            {
                if(base_remove->prox==NULL)
                {
                    lista_Aux->ultimo=base_remove->ant;
                    lista_Aux->ultimo->prox=NULL;
                    free(base_remove);
                }
                else
                {
                    base_remove->ant->prox = base_remove->prox;
                    base_remove->prox->ant = base_remove->ant;
                    free(base_remove);
                }
            }
            lista_Aux->tamanho--;
        }

        int busca_base (tipo_lista *lista_aux, char subbase[])
        {

            int i,j,cont=0;
            tipo_base *b, *aux, *bs;
            int tmhsb = strlen(subbase);

            if(tmhsb == lista_aux->tamanho){
                bs = lista_aux->primeiro;

                for(i=0; i<tmhsb ; i++){
                    if(bs->basenitrogenada == subbase[i]){
                    }
                    else{
                        break;
                    }
                    bs=bs->prox;
                }



                if(i == tmhsb){

                    for(i=0; i<tmhsb ; i++){
                        bs = lista_aux->primeiro;
                        lista_aux->primeiro = lista_aux->primeiro->prox;
                        free(bs);
                    }
                return 1;
                }
            }
            else{
                b = lista_aux->primeiro;
                for(b = lista_aux->primeiro; b != NULL ; b=b->prox)
                {
                    if(b->basenitrogenada == subbase[0])
                    {
                        if(b->prox != NULL)
                        {
                            aux=b;
                            for (i=1; i<tmhsb; i++)
                            {
                                aux=aux->prox;
                                if(aux->basenitrogenada != subbase[i])
                                {
                                    break;
                                }
                            }
                            if (i==tmhsb){
                                cont++;
                                for(j=0; j<i; j++)
                                {
                                    remove_base(lista_aux,aux);
                                    aux=aux->ant;
                                }
                            }

                        }
                        else
                        {
                            if (1==tmhsb)
                            {
                                remove_base(lista_aux,b);
                                break;
                            }
                        }
                    }
                }
            }
            return cont;
        }

        void printf_base(tipo_lista *lista_aux)
        {
            tipo_base *aux;

            for(aux=lista_aux->primeiro; aux!= NULL; aux=aux->prox)
            {
                printf("%c",aux->basenitrogenada);
            }
        }

        int main()
        {

            int i=0,tmhfita=0,tmhsubfita=0, x=0;
            char fita[1023], subfita[1023];
            tipo_lista lista_main;

            inicia_lista(&lista_main);
            for(i=0; i<1023; i++)
            {
                fita[i]=0;
            }
            for(i=0; i<1023; i++)
            {
                subfita[i]=0;
            }
            scanf("%s\n%s", fita, subfita);
            tmhfita = strlen(fita);
            tmhsubfita = strlen(subfita);

            if(tmhfita < tmhsubfita)
            {
                for(i=0; i<tmhfita; i++)
                {
                    printf("%c", fita[i]);
                }
                return 0;
            }
            for(i=0; i<tmhfita; i++)
            {
                insere_base(&lista_main, fita[i]);
            }
            x = busca_base(&lista_main, subfita);
            printf("%d\n", x);
            printf_base(&lista_main);
            return 0;
        }
