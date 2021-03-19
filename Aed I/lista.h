#define N 100
struct listaES
{
    int ultimo;
    int tamanhoLista;
    int lista[N];
};
typedef struct listaES tipoListaES;

void Inicializa (tipoListaES*);
void Imprima (tipoListaES*);
void Insira(tipoListaES*);
