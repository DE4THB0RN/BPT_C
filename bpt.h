#include <stdlib.h>
#include "lista.h"
#ifndef BPT_H
#define BPT_H

typedef struct NoBPT
{
    int marca;

    struct NoBPT *dir;
    struct NoBPT *esq;
    struct NoBPT *pai;

    int vertice;

    int de;
    int para;
    int peso;

} NoBPT;

typedef struct BPT
{
    NoBPT *raiz;
    NoBPT **folhas;

} BPT;

NoBPT *criar_no_bpt_v(int vertice)
{
    NoBPT *novo = (NoBPT *)malloc(sizeof(NoBPT));
    novo->vertice = vertice;
    novo->de = -1;
    novo->para = -1;
    novo->peso = -1;

    return novo;
}

NoBPT *criar_no_bpt_e(int de, int para, int peso)
{
    NoBPT *novo = (NoBPT *)malloc(sizeof(NoBPT));
    novo->de = de;
    novo->para = para;
    novo->peso = peso;
    novo->vertice = -1;

    return novo;
}

BPT *criar_bpt(int numV)
{
    BPT *novo = (BPT *)malloc(sizeof(BPT));
    novo->folhas = (NoBPT **)malloc(numV * sizeof(NoBPT));
    novo->raiz = NULL;

    return novo;
}

#endif // BPT_H