#include <vector>
#include <map>
#include "utilidades.h"
#ifndef GRAFO_H
#define GRAFO_H

typedef struct Aresta
{
    int vertice;
    int peso;
    bool mst;
    bool removida;
    bool inserida;
} Aresta;

typedef struct Vertex
{
public:
    int cor;
    int peso;
    std::vector<Aresta> arestas;
    Vertex();
} Vertex;

class Grafo
{

private:
    int numVertices;
    void colorir_recursivo(int vertice, int cor, bool *visitados, int *vertice_count);

public:
    int numCores;
    int *tamSegs;
    std::vector<int> cores;
    Vertex *grafo;
    int *map_grafo_mst;
    int *arestas;
    int **arestas_ordenadas;
    std::vector<int> mst;
    bool *editar_mst;
    int *segmentos;
    int *count;
    int width;
    int height;

    Grafo(int numV);
    int get_num_vertices();
    void adicionar_aresta(int origem, int destino);
    void adicionar_aresta_alter(int index, int peso);
    void remover_aresta(int origem, int destino);

    Aresta &buscar_aresta(int origem, int destino);
    std::vector<MST_Edge> *arestas_MST();
    std::vector<MST_Edge> *lista_arestas();
    std::vector<MST_Edge> *lista_arestas_ordenado();
    void ordenar_arestas();
    void marcar_mst(int origem, int destino);
    void colorir_grafo2(std::vector<int> &fila, bool *visitados);
    void colorir_grafo(int seed);
    void recolorir_grafo(MST_Edge *corte);
    int busca_profundidade(int cor, int p);
    int index_aresta(int i);

    ~Grafo();
};

#endif // GRAFO_H