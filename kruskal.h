#include <stdlib.h>
#include "bpt.h"
#include "grafo.h"
#ifndef KRSUKAL_H
#define KRSUKAL_H

int find(int *parent, int q)
{
    int r = q, tmp;

    while (parent[r] >= 0)
        r = parent[r];
    while (parent[q] >= 0)
    {
        tmp = q;
        q = parent[q];
        parent[tmp] = r;
    }

    return r;
}

void swap(int *rank, int x, int y)
{
    int temp = rank[x];
    rank[x] = rank[y];
    rank[y] = temp;
}

void union_k(int *parent, int *rank, int x, int y)
{
    if (rank[x] > rank[y])
        swap(rank, x, y);
    if (rank[x] == rank[y])
        rank[y]++;
    parent[x] = y;
}

int compara_peso(const void *a, const void *b)
{
    MST_Edge *no1 = (MST_Edge *)a;
    MST_Edge *no2 = (MST_Edge *)b;

    if (no1->peso < no2->peso)
        return -1;
    else if (no1->peso > no2->peso)
        return 1;
    else
        return 0;
}

BPT *kruskal(Grafo *gr)
{
    int num_vertices = gr->numVertices;
    BPT *bpt = criar_bpt(num_vertices);

    MST_Edge_List *lista_arestas = arestas_MST(gr);

    qsort(lista_arestas->arestas, lista_arestas->numArestas, sizeof(MST_Edge), compara_peso);

    if (lista_arestas->arestas == NULL)
    {
        free(bpt);
        printf("Erro ao alocar memória para arestas.\n");
        return NULL;
    }

    int *parent = (int *)malloc(sizeof(int) * num_vertices);
    int *rank = (int *)malloc(sizeof(int) * num_vertices);

    NoBPT **raizes = (NoBPT **)malloc(sizeof(NoBPT *) * num_vertices);

    for (int i = 0; i < num_vertices; i++)
    {
        parent[i] = -1;
        rank[i] = 0;
    }

    int edge_count = 0;
    int index = 0;
    int x, y;
    NoBPT *pai1, *pai2;
    MST_Edge proxima;

    while (edge_count < num_vertices - 1)
    {
        proxima = lista_arestas->arestas[index++];

        // if (proxima.de == 1431677248 || proxima.para == 1431677248)
        // {
        //     printf("Erro: Aresta inválida encontrada.\n");
        //     printf("de: %d, para: %d, peso: %d\n", proxima.de, proxima.para, proxima.peso);
        // }

        x = find(parent, proxima.de);
        y = find(parent, proxima.para);

        // if (index == lista_arestas->numArestas)
        //     printf("O limite era aqui\n");

        if (x != y)
        {

            if (bpt->folhas[proxima.de] == NULL)
            {
                bpt->folhas[proxima.de] = criar_no_bpt_v(proxima.de);
                raizes[proxima.de] = bpt->folhas[proxima.de];
            }

            if (bpt->folhas[proxima.para] == NULL)
            {
                bpt->folhas[proxima.para] = criar_no_bpt_v(proxima.para);
                raizes[proxima.para] = bpt->folhas[proxima.para];
            }

            NoBPT *novo_no = criar_no_bpt_e(proxima.de, proxima.para, proxima.peso);

            pai1 = raizes[x];
            pai2 = raizes[y];

            raizes[x] = novo_no;
            raizes[y] = novo_no;

            novo_no->esq = pai1;
            novo_no->dir = pai2;
            pai1->pai = novo_no;
            pai2->pai = novo_no;

            marcar_mst(proxima.de, proxima.para, gr);

            union_k(parent, rank, x, y);

            edge_count++;
        }
    }

    int root = find(parent, 0);
    bpt->raiz = raizes[root];

    free(lista_arestas->arestas);
    free(lista_arestas);
    free(parent);
    free(rank);
    free(raizes);

    return bpt;
}

#endif // KRSUKAL_H
