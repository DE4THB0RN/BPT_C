#include "utilidades.h"
#include <stdbool.h>
#include "lista.h"
#ifndef GRAFO_H
#define GRAFO_H

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
    inserir_no_lista(destino, peso, gr->grafo[origem].arestas);
    inserir_no_lista(origem, peso, gr->grafo[destino].arestas);
}

void adicionar_aresta2(int origem, int destino, Grafo *gr)
{
    inserir_no2_lista(destino, gr->grafo[origem].arestas);
    inserir_no2_lista(origem, gr->grafo[destino].arestas);
}

void remover_aresta(int origem, int destino, Grafo *gr)
{
    remover_no_lista(origem, gr->grafo[destino].arestas);
    remover_no_lista(destino, gr->grafo[origem].arestas);
}

NoLista *buscar_aresta(int origem, int destino, Grafo *gr)
{
    NoLista *tmp = gr->grafo[origem].arestas->begin;
    while (tmp != NULL)
    {
        if (tmp->vertice == destino)
            return tmp;
        tmp = tmp->prox;
    }
    return NULL;
}

// Lista *todas_as_arestas(Grafo *gr)
// {
//     bool *visitados = (bool *)malloc(gr->numVertices * sizeof(bool));
//     Lista *resp = nova_lista();
// }

MST_Edge_List *arestas_MST(Grafo *gr)
{
    MST_Edge_List *lista = (MST_Edge_List *)malloc(sizeof(MST_Edge_List));
    MST_Edge *arestas = (MST_Edge *)malloc(gr->numVertices * 8 * sizeof(MST_Edge));
    int index = 0;

    for (int i = 0; i < gr->numVertices; i++)
    {
        NoLista *tmp = gr->grafo[i].arestas->begin;
        while (tmp)
        {
            if(!tmp->inserida){
                arestas[index].de = i;
                arestas[index].para = tmp->vertice;
                arestas[index].peso = tmp->peso;

                tmp->inserida = true;
                NoLista *outro_lado = buscar_aresta(tmp->vertice, i, gr);
                outro_lado->inserida = true;

                index++;
            }
        
            tmp = tmp->prox;
        }
    }

    printf("Arestas criadas: %d\n", index);
    printf("Arestas minimas: %d\n", gr->numVertices - 1);

    lista->arestas = arestas;
    lista->numArestas = index;

    return lista;
}

void marcar_mst(int origem, int destino, Grafo *gr){
    NoLista *aresta = buscar_aresta(origem, destino, gr);
    if (aresta != NULL) {
        aresta->mst = true;
    }
    
    NoLista *aresta2 = buscar_aresta(destino, origem, gr);
    if (aresta2 != NULL) {
        aresta2->mst = true;
    }
}
#endif // GRAFO_H