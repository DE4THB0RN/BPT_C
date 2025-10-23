#include <stdio.h>
#include <time.h>
#include "bpt.h"
#include "tarjan.h"
#include "grafo.h"
#include "imagem.h"

int main()
{
    clock_t inicio, fim;
    double tempo;
    Image_Manager image_manager = Image_Manager("teste.jpg");

    inicio = clock();

    Grafo *grafo1 = image_manager.ler_imagem();

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
    std::cout << "Grafo criado com sucesso!" << std::endl;
    BPT bpt = BPT(grafo1->get_num_vertices());
    std::cout << "BPT criado com sucesso!" << std::endl;

    bpt.kruskal(grafo1);

    fim = clock();

    tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    std::cout << "Tempo de execucao: " << tempo << " segundos." << std::endl;

    // Coisas para o processamento de teste1.pgm
    int seed1 = image_manager.processar_seed(113, 226);
    int seed2 = image_manager.processar_seed(1381, 294);
    int seed3 = image_manager.processar_seed(359, 183);
    int seed4 = image_manager.processar_seed(296, 512);
    int seed5 = image_manager.processar_seed(1890, 296);
    int seed6 = image_manager.processar_seed(1472, 959);
    int seed7 = image_manager.processar_seed(897, 309);

    int seeds[] =
        {
            seed1,
            seed6,
            seed3,
            seed4,
            seed5,
            seed2,
            seed7};
    int numseeds = 7;

    std::cout << "Adicionando seeds..." << std::endl;
    bpt.adicionar_seeds(seeds, numseeds, grafo1);
    std::cout << "Teoricamente sem problemas" << std::endl;

    image_manager.salvar_imagem(grafo1);

    return 0;
}