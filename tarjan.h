#include <stdlib.h>
#include "bpt.h"
#include "grafo.h"
#ifndef KRSUKAL_H
#define KRSUKAL_H

class Tarjan
{
public:
    static int find(int *parent, int q);
    static void union_k(int *parent, int *rank, int x, int y);
};

int find(int *parent, int q);
void union_k(int *parent, int *rank, int x, int y);
int compara_peso(const void *a, const void *b);
BPT *kruskal(Grafo *gr);

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

#endif // KRSUKAL_H
