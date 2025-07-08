#include <stdlib.h>
#include <stdbool.h>

typedef struct NoLista
{
    int vertice;
    int peso;
    bool mst;
    bool removida;
    struct NoLista *prox;
} NoLista;

typedef struct Lista
{
    NoLista *begin;
    NoLista *end;
    int tam;
} Lista;

void inserir_no(int vertice, int peso, Lista *lista);
void inserir_no2(int vertice, Lista *lista);
void remover_no(int vertice, Lista *lista);
Lista *nova_lista();

void inserir_no(int vertice, int peso, Lista *lista)
{
    NoLista *tmp = lista->begin;
    while (tmp != NULL)
    {
        if (tmp->vertice == vertice)
            return;
        tmp = tmp->prox;
    }

    tmp = (NoLista *)malloc(sizeof(NoLista));
    tmp->peso = peso;
    tmp->vertice = vertice;
    tmp->prox = NULL;
    tmp->mst = false;
    tmp->removida = false;

    if (lista->begin == NULL)
    {
        lista->begin = tmp;
        lista->end = lista->begin;
    }
    else
    {
        lista->end->prox = tmp;
        lista->end = tmp;
    }
    lista->tam++;
}

void inserir_no2(int vertice, Lista *lista)
{
    NoLista *tmp = lista->begin;
    while (tmp != NULL)
    {
        if (tmp->vertice == vertice)
            return;
        tmp = tmp->prox;
    }

    tmp = (NoLista *)malloc(sizeof(NoLista));
    tmp->vertice = vertice;
    tmp->prox = NULL;
    tmp->mst = false;
    tmp->removida = false;

    if (lista->begin == NULL)
    {
        lista->begin = tmp;
        lista->end = lista->begin;
    }
    else
    {
        lista->end->prox = tmp;
        lista->end = tmp;
    }
    lista->tam++;
}

void remover_no(int vertice, Lista *lista)
{

    NoLista *tmp = lista->begin;
    if (tmp != NULL && tmp->vertice == vertice)
    {
        lista->begin = lista->begin->prox;
        tmp->prox = NULL;
        free(tmp);
        return;
    }

    while (tmp->prox != NULL)
    {
        if (tmp->prox->vertice == vertice)
        {
            NoLista *tmp2 = tmp->prox;
            tmp->prox = tmp2->prox;
            tmp2->prox = NULL;
            free(tmp2);
            return;
        }
    }
}

Lista *nova_lista()
{
    Lista *novo = (Lista *)malloc(sizeof(Lista *));
    novo->begin = NULL;
    novo->end = NULL;
    novo->tam = 0;
    return novo;
}