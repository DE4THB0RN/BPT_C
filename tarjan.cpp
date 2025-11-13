#include "tarjan.h"
#include <algorithm>
#include <iostream>

int Tarjan::find(int *parent, int q)
{

    while (parent[q] >= 0)
        q = parent[q];
    // while (parent[q] >= 0)
    // {
    //     tmp = q;
    //     q = parent[q];
    //     parent[tmp] = r;
    // }

    return q;
}

void Tarjan::union_k(int *parent, int &size, int x, int y)
{
    parent[y] = size;
    parent[x] = size;
    size++;
}

void BPT::kruskal(Grafo *gr)
{
    int num_vertices = gr->get_num_vertices();

    std::vector<MST_Edge> *arestas = gr->lista_arestas();
    std::cout << "Até aqui vai" << std::endl;

    std::sort(arestas->begin(), arestas->end(), [](const MST_Edge &a, const MST_Edge &b)
              { return a.peso < b.peso; });

    // std::cout << "Maior peso: " << arestas->at(0).peso << " Menor peso: " << arestas->at(arestas->size() - 1).peso << std::endl;
    int *parent = new int[num_vertices * 2 - 1];
    int size = 0;

    NoBPT **raizes = new NoBPT *[num_vertices]();

    for (int i = 0; i < num_vertices; i++)
    {
        parent[i] = -1;
    }
    size = num_vertices - 1;

    int edge_count = 0;
    int index = 0;
    int x, y;
    NoBPT *pai1, *pai2;
    std::cout << "Começando Kruskal..." << std::endl;
    while (edge_count < num_vertices - 1)
    {
        MST_Edge proxima = arestas->at(index++);
        x = Tarjan::find(parent, proxima.de);
        y = Tarjan::find(parent, proxima.para);
        if (x != y)
        {

            if (folhas[proxima.de] == NULL)
            {
                folhas[proxima.de] = new No_Vertice(proxima.de);
                raizes[proxima.de] = folhas[proxima.de];
            }

            if (folhas[proxima.para] == NULL)
            {
                folhas[proxima.para] = new No_Vertice(proxima.para);
                raizes[proxima.para] = folhas[proxima.para];
            }

            No_Aresta *novo_no = new No_Aresta(proxima.de, proxima.para, proxima.peso);

            pai1 = raizes[x];
            pai2 = raizes[y];

            raizes[x] = novo_no;
            raizes[y] = novo_no;

            novo_no->set_esq(pai1);
            novo_no->set_dir(pai2);
            pai1->set_pai(novo_no);
            pai2->set_pai(novo_no);

            gr->marcar_mst(proxima.de, proxima.para);

            Tarjan::union_k(parent, size, x, y);

            edge_count++;

            novo_no = nullptr;
        }
    }

    int root = Tarjan::find(parent, 0);
    raiz = static_cast<No_Aresta *>(raizes[root]);

    std::cout << "Kruskal finalizado!" << std::endl;
    delete[] parent;
    delete[] raizes;
    delete arestas;
}
