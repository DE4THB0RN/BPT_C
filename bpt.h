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
    novo->marca = 0;

    return novo;
}

BPT *criar_bpt(int numV)
{
    BPT *novo = (BPT *)malloc(sizeof(BPT));
    novo->folhas = (NoBPT **)malloc(numV * sizeof(NoBPT));
    novo->raiz = NULL;

    return novo;
}

void adicionar_seeds(int *seeds, int numseeds, BPT *bpt, Grafo *gr)
{
    NoBPT *tmp;
    bool cortou = false;
    for (int i = 0; i < numseeds; i++)
    {
        tmp = bpt->folhas[seeds[i]];
        while (tmp != bpt->raiz)
        {
            tmp = tmp->pai;
            tmp->marca++;

            if (tmp->marca == 2)
            {
                NoLista *aresta = buscar_aresta(tmp->de, tmp->para, gr);
                aresta->removida = true;
               // cortou = true;
            }
        }

        colorir_grafo(gr, seeds[i]);
        // cortou = false;
    }

    // Aqui eu mandaria colorir
}

void remover_seeds(int *seeds, int numseeds, BPT *bpt, Grafo *gr)
{
    NoBPT *tmp;

    for (int i = 0; i < numseeds; i++)
    {
        tmp = bpt->folhas[seeds[i]];
        while (tmp != bpt->raiz && tmp->marca != 1)
        {
            tmp = tmp->pai;
            tmp->marca--;

            if (tmp->marca == 1)
            {
                NoLista *aresta = buscar_aresta(tmp->de, tmp->para, gr);
                if (aresta)
                {
                    aresta->removida = false;
                }
                // Talvez recolorir direto aqui, progressivamente
            }
        }
    }
    // Mas também estou considerando recolorir aqui
}

void mostrar_bpt(BPT *bpt)
{

    if (bpt == NULL || bpt->raiz == NULL)
    {
        printf("Não tem nada aqui\n");
        return;
    }

    printf("BPT:\n");
}

int processar_seed(Grafo *gr, int x, int y)
{

    int vertice = y * gr->width + x;
    if (vertice < 0 || vertice >= gr->numVertices)
    {
        printf("Esse número aí não tá valendo\n");
        return -1;
    }
    return vertice;
}

#endif // BPT_H