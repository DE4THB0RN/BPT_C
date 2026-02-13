#include "grafo.h"
#include <iostream>
#include <algorithm>
#include <cstring>

Vertex::Vertex()
{
    cor = -1;
    peso = 0;
}

Grafo::Grafo(int numV)
{
    numVertices = numV;
    numCores = 0;
    grafo = new Vertex[numV];
    map_grafo_mst = new int[numV * 2]();
    arestas = new int[numV * 2]();
    count = new int[256]();
    arestas_ordenadas = new int *[256];
    segmentos = new int[numV]();
    tamSegs = new int[numV]();

    tamSegs[0] = numV;

    for (int i = 0; i < numV * 2; i++)
    {
        map_grafo_mst[i] = -1;
    }
}

Grafo::~Grafo()
{
    delete[] grafo;
    delete[] map_grafo_mst;
    map_grafo_mst = nullptr;
    grafo = nullptr;
}

int Grafo::get_num_vertices()
{
    return numVertices;
}

void Grafo::adicionar_aresta(int origem, int destino)
{
    Aresta novaAresta;
    novaAresta.vertice = destino;
    novaAresta.peso = std::abs(grafo[origem].peso - grafo[destino].peso);
    novaAresta.mst = false;
    novaAresta.removida = false;
    novaAresta.inserida = false;
    grafo[origem].arestas.push_back(novaAresta);

    Aresta novaAresta2;
    novaAresta2.vertice = origem;
    novaAresta2.peso = novaAresta.peso;
    novaAresta2.mst = false;
    novaAresta2.removida = false;
    novaAresta2.inserida = false;
    grafo[destino].arestas.push_back(novaAresta2);
}

void Grafo::adicionar_aresta_alter(int index, int peso)
{
    if (index < 0 || index >= numVertices * 2)
    {
        throw std::out_of_range("Index fora do intervalo válido");
    }
    else
    {
        arestas[index] = peso;
        count[peso]++;
    }
}

void Grafo::remover_aresta(int origem, int destino)
{
    for (auto &aresta : grafo[origem].arestas)
    {
        if (aresta.vertice == destino)
        {
            aresta.removida = true;
        }
    }

    for (auto &aresta : grafo[destino].arestas)
    {
        if (aresta.vertice == origem)
        {
            aresta.removida = true;
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

    throw std::runtime_error("Aresta não encontrada");
}

void Grafo::marcar_mst(int origem, int destino)
{
    for (auto &aresta : grafo[origem].arestas)
    {
        if (aresta.vertice == destino)
        {
            aresta.mst = true;
        }
    }
    for (auto &aresta : grafo[destino].arestas)
    {
        if (aresta.vertice == origem)
        {
            aresta.mst = true;
        }
    }
}

void Grafo::colorir_recursivo(int vertice, int cor, bool *visitados, int *vertice_count)
{
    visitados[vertice] = true;
    grafo[vertice].cor = cor;
    //  tamCores.at(cor) = tamCores.at(cor) + 1;
    vertice_count[0] = vertice_count[0] + 1;

    for (auto &aresta : grafo[vertice].arestas)
    {
        if (!visitados[aresta.vertice] && !aresta.removida && aresta.mst)
        {
            colorir_recursivo(aresta.vertice, cor, visitados, vertice_count);
        }
    }
}

void Grafo::colorir_grafo(int seed)
{
    int vertice_count = 0;
    bool *visitados = new bool[numVertices]();
    //   tamCores.insert({numCores, 0});

    colorir_recursivo(seed, numCores, visitados, &vertice_count);

    printf("Seção %d com número de vértices: %d\n", numCores, vertice_count);
    numCores++;
    printf("Número de seções: %d\n", numCores);
}

void Grafo::colorir_grafo2(std::vector<int> &fila, bool *visitados)
{
    int vertice_count = 0;
    int vertice1, vertice2, cor1, cor2, novaCor;

    for (int aresta : fila)
    {
        if (((aresta) & (1 << (0))) == 1)
        {
            vertice1 = aresta / 2;
            vertice2 = (aresta / 2) + width;
        }
        else
        {
            vertice1 = (aresta + 1) / 2;
            vertice2 = ((aresta + 1) / 2) + 1;
        }

        cor1 = segmentos[vertice1];
        cor2 = segmentos[vertice2];

        if (!visitados[cor2])
        {
            if (cores.empty())
            {
                novaCor = numCores;
                numCores++;
            }
            else
            {
                novaCor = cores.back();
                cores.pop_back();
            }
            tamSegs[novaCor] = busca_profundidade(novaCor, vertice2);
            tamSegs[cor2] -= tamSegs[novaCor];
            if (tamSegs[cor2] <= 0)
            {
                cores.push_back(cor2);
            }
            visitados[cor2] = true;
        }
        if (!visitados[cor1])
        {
            if (cores.empty())
            {
                novaCor = numCores;
                numCores++;
            }
            else
            {
                novaCor = cores.back();
                cores.pop_back();
            }
            tamSegs[novaCor] = busca_profundidade(novaCor, vertice1);
            tamSegs[cor1] -= tamSegs[novaCor];
            if (tamSegs[cor1] <= 0)
            {
                cores.push_back(cor1);
            }
            visitados[cor1] = true;
        }
    }
}

void Grafo::recolorir_grafo(MST_Edge *corte)
{
    int vertice_count = 0;
    bool *visitados = new bool[numVertices]();
    int cor1 = grafo[corte->de].cor;
    int cor2 = grafo[corte->para].cor;

    // if (tamSegs.at(cor1) > tamSegs.at(cor2))
    // {
    //     tamSegs.erase(cor2);
    //     colorir_recursivo(corte->para, cor1, visitados, &vertice_count);
    // }
    // else
    // {
    //     tamSegs.erase(cor1);
    //     colorir_recursivo(corte->de, cor2, visitados, &vertice_count);
    // }
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

std::vector<MST_Edge> *Grafo::lista_arestas()
{
    std::vector<MST_Edge> *lista = new std::vector<MST_Edge>();
    for (int i = 0; i < numVertices; i++)
    {
        for (auto &aresta : grafo[i].arestas)
        {

            MST_Edge mst_nova_aresta;
            mst_nova_aresta.de = i;
            mst_nova_aresta.para = aresta.vertice;
            mst_nova_aresta.peso = aresta.peso;
            lista->push_back(mst_nova_aresta);
        }
    }
    return lista;
}

std::vector<MST_Edge> *Grafo::lista_arestas_ordenado()
{
    std::vector<MST_Edge> *lista = lista_arestas();
    std::sort(lista->begin(), lista->end(), [](const MST_Edge &a, const MST_Edge &b)
              { return a.peso < b.peso; });
    return lista;
}

void Grafo::ordenar_arestas()
{
    for (int i = 0; i < 256; i++)
    {
        arestas_ordenadas[i] = new int[count[i]];
    }

    int *index_atual = new int[256]();
    memset(index_atual, 0, 256 * sizeof(int));

    for (int i = 0; i < 2 * numVertices; i++)
    {
        if (arestas[i] >= 0)
        {
            int peso = arestas[i];
            int index_local = index_atual[peso];
            arestas_ordenadas[peso][index_local] = i;
            index_atual[peso]++;
        }
    }

    delete[] index_atual;
}

int Grafo::busca_profundidade(int cor, int p)
{
    std::vector<int> fila;
    fila.push_back(p);
    int count = 1;
    int tamtotal = width * height;

    int vertice, dir, esq, cima, baixo;
    while (!fila.empty())
    {
        vertice = fila.back();
        fila.pop_back();
        segmentos[vertice] = cor;

        dir = vertice + 1;
        esq = vertice - 1;
        cima = vertice - width;
        baixo = vertice + width;

        if (dir < tamtotal && (vertice + 1) % width != 0)
        {
            auto aresta_mst = map_grafo_mst[vertice * 2];
            if (aresta_mst != -1)
            {
                if (editar_mst[aresta_mst] && segmentos[dir] != cor)
                {
                    fila.push_back(dir);
                    segmentos[dir] = cor;
                    count++;
                }
            }
        }

        if (esq >= 0 && vertice % width != 0)
        {
            auto aresta_mst = map_grafo_mst[(vertice * 2) - 2];
            if (aresta_mst != 1)
            {
                if (editar_mst[aresta_mst] && segmentos[esq] != cor)
                {
                    fila.push_back(esq);
                    segmentos[esq] = cor;
                    count++;
                }
            }
        }

        if (baixo < tamtotal)
        {
            auto aresta_mst = map_grafo_mst[(vertice * 2) + 1];
            if (aresta_mst != -1)
            {
                if (editar_mst[aresta_mst] && segmentos[baixo] != cor)
                {
                    fila.push_back(baixo);
                    segmentos[baixo] = cor;
                    count++;
                }
            }
        }

        if (cima >= 0)
        {
            auto aresta_mst = map_grafo_mst[((vertice * 2) - (width * 2)) + 1];
            if (aresta_mst != -1)
            {
                if (editar_mst[aresta_mst] && segmentos[cima] != cor)
                {
                    fila.push_back(cima);
                    segmentos[cima] = cor;
                    count++;
                }
            }
        }
    }

    return count;
}

int Grafo::index_aresta(int i)
{
   // std::cout << "Index de aresta: " << i << std::endl;
    if (i < numVertices)
    {
        std::cout << "Index de aresta inválido: " << i << std::endl;
        std::exit(EXIT_FAILURE);
    }
    return i - numVertices;
}