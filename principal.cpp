#include <stdio.h>
#include <time.h>
#include "pgmread.h"
#include "bpt.h"
#include "tarjan.h"
#include "grafo.h"


#include "imagem.h"

int main()
{
    clock_t inicio, fim;
    double tempo;

    inicio = clock();
    Grafo *grafo1 = grafo_arq("teste1.pgm");

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
    fim = clock();

    tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("Tempo total de criação: %.2f s\n", tempo);

    // Coisas para o processamento de teste1.pgm
    int seed1 = processar_seed(grafo1, 113, 226);
    int seed2 = processar_seed(grafo1, 1381, 294);
    int seed3 = processar_seed(grafo1, 359, 183);
    int seed4 = processar_seed(grafo1, 296, 512);
    int seed5 = processar_seed(grafo1, 1890, 296);
    int seed6 = processar_seed(grafo1, 1472, 959);
    int seed7 = processar_seed(grafo1, 897, 309);

    int seeds[] = 
    {
        seed1,
        seed6,
        seed3, 
        seed4, 
        seed5, 
        seed2, 
        seed7
        };
    int numseeds = 7;

    printf("Processando seeds...\n");
    adicionar_seeds(seeds, numseeds, bpt, grafo1);
    printf("Teoricamente sem problemas\n");

    salvar_imagem("resultado1_7s.png", grafo1);

    return 0;
}