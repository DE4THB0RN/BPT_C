#include <stdlib.h>
#include "bpt.h"
#include "grafo.h"

int find(int *parent, int q);
void swap(int *rank, int x, int y);
void union_k(int *parent, int *rank, int x, int y);
BPT *kruskal(Grafo *gr);

int find(int *parent, int q)
{
    int r = q;
    int tmp;
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
    NoLista *no1 = (NoLista *)a;
    NoLista *no2 = (NoLista *)b;

    if (no1->peso < no2->peso)
        return -1;
    else if (no1->peso > no2->peso)
        return 1;
    else
        return 0;
}

BPT *kruskal(Grafo *gr)
{
}
