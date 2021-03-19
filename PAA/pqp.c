#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

int counter=0;
int pos=0;

struct node{
    int vertex;
    struct node* next;
};

struct node *createNode(int v){
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

struct llist{
    struct node *f;
    struct node *l;
    int tamanho;
};

void init_list(struct llist *l){
    l->f=NULL;
    l->l=NULL;
    l->tamanho=0;
}

void insert_sort(struct llist *l, int v){
    struct node *n = createNode(v);
    struct node *temp = l->f;

    if(l->tamanho==0){
        l->f=n;
        l->l=n;
    }
    else{
        if((temp->vertex)>v){
            n->next=temp;
            temp=n;
            l->f=n;
        }
        else{
            while(temp->next!=NULL && temp->next->vertex<v){
                temp=temp->next;
            }
            n->next=temp->next;
            temp->next=n;
            if(n->next==NULL){
                l->l=n;
            }
        }
    }
    l->tamanho++;
}




void printf_list(struct llist *l){
    struct node *n = l->f;
    printf("\n\n");
    while(n!=NULL){
          printf(" %d", n->vertex);
          n=n->next;
    }
}

int main(){
    int i=0,j=0,k=0,qtd=0,s=0,d=0,count=0,large=0,longestv=-1;


    struct llist *l;
    l=(struct llist*)malloc(sizeof(struct llist));
    init_list(l);
    struct node *temp=l->f;
    if(temp==NULL) printf("babaninha");
    insert_sort(l,5);
    printf_list(l);
    insert_sort(l,10);
    printf_list(l);
    insert_sort(l,15);
    printf_list(l);
    insert_sort(l,2);
    printf_list(l);
    insert_sort(l,3);
    printf_list(l);
    insert_sort(l,7);
    printf_list(l);
    insert_sort(l,6);
    printf_list(l);

    return 0;
}
