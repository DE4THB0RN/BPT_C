#include <stdio.h>
#include <time.h>
#include "bpt.h"
#include "tarjan.h"
#include "grafo.h"
#include "imagem.h"
#include <vector>

int main()
{
  clock_t inicio, fim;
  double tempo;
  Image_Manager image_manager = Image_Manager("toy_image.png");

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

  bpt.kruskal(grafo1);
  std::cout << "BPT criado com sucesso!" << std::endl;

  fim = clock();

  tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
  std::cout << "Tempo de execucao: " << tempo << " segundos." << std::endl;

  // Coisas para o processamento de teste1.pgm
  // int seed_fundo = image_manager.processar_seed(774, 222);
  // int seed_f1 = image_manager.processar_seed(427, 209);
  // int seed_f2 = image_manager.processar_seed(1100, 192);
  // int seed1 = image_manager.processar_seed(545, 136);
  // int seed2 = image_manager.processar_seed(547, 236);
  // int seed3 = image_manager.processar_seed(449, 232);
  // int seed4 = image_manager.processar_seed(1159, 92);
  // int seed5 = image_manager.processar_seed(1024, 204);
  // int seed6 = image_manager.processar_seed(1050, 341);
  // int seed7 = image_manager.processar_seed(967, 161);

  // int seed_fundo = image_manager.processar_seed(15, 15);
  // int seed_f1 = image_manager.processar_seed(250, 250);

  // int seeds[] =
  //     {

  //         seed_fundo,
  //         seed_f1,
  // seed2,
  // seed3,
  // seed6,
  // seed1,
  // seed5,
  // seed4,
  // seed7,
  // seed_fundo,
  // seed_f1,
  // seed_f2,
  //};
 // int numseeds = 2;

  std::vector<int> marcadores = {278, 50, 250 * 500 + 250};

  std::cout << "Adicionando seeds..." << std::endl;
  bpt.adicionar_seeds2(marcadores.data(), marcadores.size(), grafo1);
  std::cout << "Teoricamente sem problemas" << std::endl;

  image_manager.salvar_imagem2(grafo1, "output_segmented.png");

  // delete grafo1;

  return 0;
}