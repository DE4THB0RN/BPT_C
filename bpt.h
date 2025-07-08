#include <stdlib.h>
#include "lista.h"

typedef struct NoBPT
{
    int marca;

    struct NoBPT *dir;
    struct NoBPT *esq;
    struct NoBPT *pai;

    int vertice;

    NoLista *aresta;

} NoBPT;

typedef struct BPT
{
    NoBPT *raiz;
    NoBPT **folhas;

} BPT;

NoBPT *criar_no_bpt_v(int vertice);
NoBPT *criar_no_bpt_e(NoLista *aresta);
BPT *criar_bpt(int numV);

NoBPT *criar_no_bpt_v(int vertice)
{
    NoBPT *novo = (NoBPT *)malloc(sizeof(NoBPT));
    novo->vertice = vertice;
    novo->aresta = NULL;

    return novo;
}

NoBPT *criar_no_bpt_e(NoLista *aresta)
{
    NoBPT *novo = (NoBPT *)malloc(sizeof(NoBPT));
    novo->vertice = -1;
    novo->aresta = aresta;

    return novo;
}

BPT *criar_bpt(int numV)
{
    BPT *novo = (BPT *)malloc(sizeof(BPT));
    novo->folhas = (NoBPT **)malloc(numV * sizeof(NoBPT));
    novo->raiz = NULL;

    return novo;
}
