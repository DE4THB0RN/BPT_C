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
    std::map<int, int> tamCores;
    Vertex *grafo;

    Grafo(int numV);
    int get_num_vertices();
    void adicionar_aresta(int origem, int destino, int peso);
    void adicionar_aresta2(int origem, int destino);
    void remover_aresta(int origem, int destino);
    Aresta &buscar_aresta(int origem, int destino);
    std::vector<MST_Edge> *arestas_MST();
    std::vector<MST_Edge> *lista_arestas();
    void marcar_mst(int origem, int destino);
    void colorir_grafo(int seed);
    void recolorir_grafo(MST_Edge *corte);
    ~Grafo();
};

#endif // GRAFO_H