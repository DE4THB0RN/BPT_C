#include "utilidades.h"
#include <stdbool.h>
#include "lista.h"

typedef struct Vertex
{
    int id;
    int cor;
    int peso;
    Lista *arestas;
} Vertex;

typedef struct Grafo
{
    int numCores;
    Dicionario *tamCores;
    Vertex *grafo;
    int numVertices;
} Grafo;

Grafo *novo_grafo(int numV);
void adicionar_aresta(int origem, int destino, int peso, Grafo *gr);
void adicionar_aresta2(int origem, int destino, Grafo *gr);
void remover_aresta(int origem, int destino, Grafo *gr);

Grafo *novo_grafo(int numV)
{
    Grafo *novo = (Grafo *)malloc(sizeof(Grafo));
    novo->tamCores = criar_dicionario();
    novo->numVertices = numV;
    novo->numCores = 0;
    novo->grafo = (Vertex *)malloc(numV * sizeof(Vertex));

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

Lista *todas_as_arestas(Grafo *gr)
{
    bool *visitados = (bool *)malloc(gr->numVertices * sizeof(bool));
    Lista *resp = nova_lista();
}
