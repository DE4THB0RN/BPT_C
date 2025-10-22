#include "grafo.h"
#include <iostream>

Vertex::Vertex()
{
    cor = -1;
    peso = 0;
}

Grafo::Grafo(int numV)
{
    numCores = numV;
    numCores = 0;
    grafo = new Vertex[numV];
}

Grafo::~Grafo()
{
    delete[] grafo;
    grafo = nullptr;
}

int Grafo::get_num_vertices()
{
    return numVertices;
}

void Grafo::adicionar_aresta(int origem, int destino, int peso)
{
    Aresta novaAresta;
    novaAresta.vertice = destino;
    novaAresta.peso = peso;
    novaAresta.mst = false;
    novaAresta.removida = false;
    novaAresta.inserida = false;
    grafo[origem].arestas.push_back(novaAresta);
}

void Grafo::adicionar_aresta2(int origem, int destino)
{
    Aresta novaAresta;
    novaAresta.vertice = destino;
    novaAresta.peso = std::abs(grafo[origem].peso - grafo[destino].peso);
    novaAresta.mst = false;
    novaAresta.removida = false;
    novaAresta.inserida = false;
    grafo[origem].arestas.push_back(novaAresta);
}

void Grafo::remover_aresta(int origem, int destino)
{
    for (auto &aresta : grafo[origem].arestas)
    {
        if (aresta.vertice == destino)
        {
            aresta.removida = true;
            return;
        }
    }
}

Aresta &Grafo::buscar_aresta(int origem, int destino)
{

    for (auto &aresta : grafo[origem].arestas)
    {
        if (aresta.vertice == destino)
        {
            return aresta;
        }
    }

    std::cout << "Aresta nao encontrada!" << std::endl;
}

void Grafo::marcar_mst(int origem, int destino)
{
    for (auto &aresta : grafo[origem].arestas)
    {
        if (aresta.vertice == destino)
        {
            aresta.mst = true;
            return;
        }
    }
}

void Grafo::colorir_recursivo(int vertice, int cor, bool *visitados, int *vertice_count)
{
    visitados[vertice] = true;
    grafo[vertice].cor = cor;
    tamCores.at(cor) = tamCores.at(cor) + 1;
    vertice_count[0] = vertice_count[0] + 1;

    for (auto &aresta : grafo[vertice].arestas)
    {
        if (!visitados[aresta.vertice] && !aresta.removida)
        {
            colorir_recursivo(aresta.vertice, cor, visitados, vertice_count);
        }
    }
}

void Grafo::colorir_grafo(int seed)
{
    int vertice_count = 0;
    bool *visitados = new bool[numVertices]();
    tamCores.insert({numCores, 0});

    colorir_recursivo(seed, numCores, visitados, &vertice_count);

    printf("Seção %d com número de vértices: %d\n", numCores, vertice_count);
    numCores++;
    printf("Número de seções: %d\n", numCores);
}

void Grafo::recolorir_grafo(MST_Edge *corte)
{
    int vertice_count = 0;
    bool *visitados = new bool[numVertices]();
    int cor1 = grafo[corte->de].cor;
    int cor2 = grafo[corte->para].cor;

    if (tamCores.at(cor1) > tamCores.at(cor2))
    {
        tamCores.erase(cor2);
        colorir_recursivo(corte->para, cor1, visitados, &vertice_count);
    }
    else
    {
        tamCores.erase(cor1);
        colorir_recursivo(corte->de, cor2, visitados, &vertice_count);
    }
}

std::vector<MST_Edge> *Grafo::arestas_MST()
{
    std::vector<MST_Edge> *lista = new std::vector<MST_Edge>();
    for (int i = 0; i < numVertices; i++)
    {
        for (auto &aresta : grafo[i].arestas)
        {
            if (aresta.mst)
            {
                MST_Edge mst_nova_aresta;
                mst_nova_aresta.de = i;
                mst_nova_aresta.para = aresta.vertice;
                mst_nova_aresta.peso = aresta.peso;
                lista->push_back(mst_nova_aresta);
            }
        }
    }
    return lista;
}