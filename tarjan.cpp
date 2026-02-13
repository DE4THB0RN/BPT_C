#include "tarjan.h"
#include <algorithm>
#include <iostream>

int Tarjan::find_1(BPT *bpt, int q)
{
    int r = q;
    int tmp = 0;
    while (bpt->parent_1[r] >= 0)
    {
        r = bpt->parent_1[r];
    }
    while (bpt->parent_1[q] >= 0)
    {
        tmp = q;
        q = bpt->parent_1[q];
        bpt->parent_1[tmp] = r;
    }

    return r;
}

int Tarjan::find_2(BPT *bpt, int q)
{
    while (bpt->parent_2[q] >= 0)
    {
        q = bpt->parent_2[q];
    }

    return q;
}

int Tarjan::find(BPT *bpt, int q)
{
    return find_1(bpt, q);
}

int Tarjan::union_k1(BPT *bpt, int x, int y)
{
    if (bpt->rank[x] > bpt->rank[y])
    {
        int tmp = x;
        x = y;
        y = tmp;
    }
    if (bpt->rank[x] == bpt->rank[y])
    {
        bpt->rank[y]++;
    }
    bpt->parent_1[x] = y;

    // std::cout << "Unindo " << x << " e " << y << std::endl;

    return y;
}

int Tarjan::union_k2(BPT *bpt, int x, int y)
{
    bpt->parent_2[x] = bpt->size_2;
    bpt->parent_2[y] = bpt->size_2;
    bpt->size_2++;
    return (bpt->size_2) - 1;
}

int Tarjan::union_k(BPT *bpt, int x, int y)
{
    int tx = bpt->root[x];
    int ty = bpt->root[y];

    bpt->set_parent_2(tx, bpt->size_2);
    bpt->set_parent_2(ty, bpt->size_2);

    int c = union_k1(bpt, x, y);
    bpt->root[c] = bpt->size_2;
    bpt->make_set_2(bpt->size_2);

    return bpt->size_2 - 1;
}

void BPT::kruskal(Grafo *gr)
{
    int num_vertices = gr->get_num_vertices();

    for (int i = 0; i < num_vertices; i++)
    {
        make_set(i);
    }

    int x, y;

    int count = 0;

    std::cout << "Começando Kruskal..." << std::endl;
    for (int i = 0; i < 256; i++)
    {
        for (int j = 0; j < gr->count[i]; j++)
        {
            x = 0;
            y = 0;

            int aresta = gr->arestas_ordenadas[i][j];

            if ((aresta) & 1 == 1)
            {
                x = aresta / 2;
                y = (aresta / 2) + gr->width;
            }
            else
            {
                x = (aresta + 1) / 2;
                y = ((aresta + 1) / 2) + 1;
            }

            x = Tarjan::find(this, x);
            y = Tarjan::find(this, y);

            if (x != y)
            {
                Tarjan::union_k(this, x, y);
                gr->mst.push_back(aresta);
                gr->map_grafo_mst[aresta] = count;
                count++;
            }
        }
    }

    gr->editar_mst = new bool[gr->mst.size()];

    for (size_t i = 0; i < gr->mst.size(); i++)
    {
        gr->editar_mst[i] = true;
    }

    std::cout << "Kruskal finalizado!" << std::endl;
}
