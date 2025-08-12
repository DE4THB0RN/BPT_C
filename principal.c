#include <stdio.h>
#include "pgmread.h"
#include "bpt.h"
#include "kruskal.h"
#include "grafo.h"
#include "lista.h"
#include "utilidades.h"

int main()
{
    Grafo *grafo1 = grafo_arq("teste2.pgm");
    // Grafo *grafo1 = novo_grafo(8);
    // adicionar_aresta(0, 1, 95, grafo1);
    // adicionar_aresta(0, 4, 0, grafo1);
    // adicionar_aresta(0, 5, 100, grafo1);
    // adicionar_aresta(1, 2, 120, grafo1);
    // adicionar_aresta(1, 5, 80, grafo1);
    // adicionar_aresta(1, 6, 180, grafo1);
    // adicionar_aresta(2, 3, 9, grafo1);
    // adicionar_aresta(2, 6, 125, grafo1);
    // adicionar_aresta(2, 7, 200, grafo1);
    // adicionar_aresta(3, 7, 116, grafo1);
    // adicionar_aresta(4, 5, 15, grafo1);
    // adicionar_aresta(4, 1, 50, grafo1);
    // adicionar_aresta(5, 6, 75, grafo1);
    // adicionar_aresta(5, 2, 46, grafo1);
    // adicionar_aresta(6, 7, 0, grafo1);
    // adicionar_aresta(6, 3, 96, grafo1);
    printf("Grafo criado com sucesso!\n");
    BPT *bpt = kruskal(grafo1);
    printf("Não crashei");
    return 0;
}