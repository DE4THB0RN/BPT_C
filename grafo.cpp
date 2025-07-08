#include "lista.h"
#include <list>
#include <unordered_map>
#include <vector>
using namespace std;

typedef struct Vertex
{
    int id;
    int cor;
    int peso;
    list<NoLista> arestas;
} Vertex;

typedef struct Grafo
{
    int numCores;
    unordered_map<int, int> tamCores;
    vector<Vertex> grafo;
    int numVertices;
} Grafo;

Grafo *novo_grafo(int numV);
void adicionar_aresta(int origem, int destino, int peso, Grafo *gr);
void adicionar_aresta2(int origem, int destino, Grafo *gr);
void remover_aresta(int origem, int destino, Grafo *gr);

Grafo *novo_grafo(int numV)
{
    Grafo *novo = (Grafo *)malloc(sizeof(Grafo));
    novo->numVertices = numV;
    novo->numCores = 0;
    novo->grafo.resize(numV);

    for (int i = 0; i < numV; i++)
    {
        novo->grafo[i].id = i;
        novo->grafo[i].arestas = nova_lista();
    }

    printf("Criado grafo de tamanho %d\n", numV);

    return novo;
}

void adicionar_aresta(int origem, int destino, int peso, Grafo *gr)
{
    inserir_no(destino, peso, gr->grafo[origem].arestas);
    inserir_no(origem, peso, gr->grafo[destino].arestas);
}

void adicionar_aresta2(int origem, int destino, Grafo *gr)
{
    inserir_no2(destino, gr->grafo[origem].arestas);
    inserir_no2(origem, gr->grafo[destino].arestas);
}

void remover_aresta(int origem, int destino, Grafo *gr)
{
    remover_no(origem, gr->grafo[destino].arestas);
    remover_no(destino, gr->grafo[origem].arestas);
}
