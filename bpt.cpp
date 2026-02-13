#include "bpt.h"
#include <iostream>

//=============================================================
// Código dos nós
//=============================================================

NoBPT::~NoBPT()
{
    esq = nullptr;
    dir = nullptr;
    pai = nullptr;
}

void NoBPT::aumenta_marca()
{
    marca++;
}

void NoBPT::diminui_marca()
{
    marca--;
}

void NoBPT::set_dir(NoBPT *d)
{
    dir = d;
}

void NoBPT::set_esq(NoBPT *e)
{
    esq = e;
}

void NoBPT::set_pai(NoBPT *p)
{
    pai = p;
}

NoBPT *NoBPT::get_dir()
{
    return dir;
}

NoBPT *NoBPT::get_esq()
{
    return esq;
}

NoBPT *NoBPT::get_pai()
{
    return pai;
}

int NoBPT::get_marca()
{
    return marca;
}

No_Aresta::No_Aresta(int d, int p, int w)
{

    de = d;
    para = p;
    peso = w;

    set_dir(nullptr);
    set_esq(nullptr);
    set_pai(nullptr);
    marca = 0;
}

No_Vertice::No_Vertice(int v)
{
    vertice = v;

    set_dir(nullptr);
    set_esq(nullptr);
    set_pai(nullptr);
    marca = 0;
}

//=============================================================
// Código da BPT
//=============================================================
BPT::BPT(int numV)
{
    raiz = nullptr;
    folhas.resize(numV);

    parent_1 = new int[numV * 2 - 1]();
    parent_2 = new int[numV * 2 - 1]();
    rank = new int[numV * 2 - 1]();
    root = new int[numV * 2 - 1]();
    marcas = new int[numV * 2 - 1]();
    size_1 = 0;
    size_2 = 0;
    size = 0;
}

BPT::~BPT()
{
    delete_tree(raiz);
    delete[] parent_1;
    delete[] parent_2;
    delete[] root;
    delete[] rank;
    delete[] marcas;
    marcas = nullptr;
    parent_1 = nullptr;
    parent_2 = nullptr;
    root = nullptr;
    rank = nullptr;
    raiz = nullptr;
}

void BPT::delete_tree(NoBPT *atual)
{
    if (atual == nullptr)
    {
        return;
    }

    delete_tree(atual->get_esq());
    delete_tree(atual->get_dir());

    delete atual;
}

void BPT::adicionar_seeds(int *seeds, int numseeds, Grafo *gr)
{
    NoBPT *tmp;

    for (int i = 0; i < numseeds; i++)
    {
        tmp = folhas[seeds[i]];
        while (tmp != raiz)
        {
            tmp = tmp->get_pai();
            tmp->aumenta_marca();

            if (tmp->get_marca() == 2)
            {
                No_Aresta *aresta_no = dynamic_cast<No_Aresta *>(tmp);

                gr->remover_aresta(aresta_no->de, aresta_no->para);

                aresta_no = nullptr;
            }
        }

        gr->colorir_grafo(seeds[i]);
    }
}

void BPT::remover_seeds(int *seeds, int numseeds, Grafo *gr)
{
    NoBPT *tmp;

    for (int i = 0; i < numseeds; i++)
    {
        tmp = folhas[seeds[i]];
        while (tmp != raiz && tmp->get_marca() != 1)
        {
            tmp = tmp->get_pai();
            tmp->diminui_marca();

            if (tmp->get_marca() == 1)
            {
                No_Aresta *aresta_no = static_cast<No_Aresta *>(tmp);
                Aresta &aresta = gr->buscar_aresta(aresta_no->de, aresta_no->para);

                aresta.removida = false;

                // Talvez recolorir direto aqui, progressivamente
            }
        }
    }
    // Mas também estou considerando recolorir aqui
}

void BPT::remover_seed(int seed, Grafo *gr)
{
    NoBPT *tmp = folhas[seed];
    MST_Edge corte;
    while (tmp != raiz && tmp->get_marca() != 1)
    {
        tmp = tmp->get_pai();
        tmp->diminui_marca();

        if (tmp->get_marca() == 1)
        {
            No_Aresta *aresta_no = static_cast<No_Aresta *>(tmp);
            Aresta &aresta = gr->buscar_aresta(aresta_no->de, aresta_no->para);

            aresta.removida = false;

            corte = MST_Edge{aresta_no->de, aresta_no->para, aresta_no->peso};

            gr->recolorir_grafo(&corte);
        }
    }
}

void BPT::adicionar_seeds2(int *seeds, int numseeds, Grafo *gr)
{

    int marca_atual, cima = 0;
    std::vector<int> fila_corte;
    bool *visitados = new bool[gr->get_num_vertices()]();

    for (int i = 0; i < numseeds; i++)
    {

        marca_atual = marcas[seeds[i]];
        cima = parent_2[marca_atual];
        // std::cout << cima << std::endl;
        while (cima != -1)
        {
            marcas[cima]++;
            if (marcas[cima] == 2)
            {
                std::cout << "Index da aresta" << gr->index_aresta(cima) << std::endl;
                gr->editar_mst[gr->index_aresta(cima)] = false;
                fila_corte.push_back(gr->index_aresta(cima));
                //          std::cout << "Corte adicionado: " << gr->index_aresta(cima) << std::endl;
                break;
            }
            cima = parent_2[cima];
        }
    }

    std::cout << "Recolorindo grafo..." << std::endl;
    gr->colorir_grafo2(fila_corte, visitados);

    delete[] visitados;
}

void BPT::make_set_1(int q)
{
    parent_1[q] = -1;
    rank[q] = 0;
    size_1++;
}

void BPT::make_set_2(int q)
{
    parent_2[q] = -1;
    size_2++;
}

void BPT::make_set(int q)
{
    root[q] = q;
    make_set_1(q);
    make_set_2(q);
}

void BPT::set_parent_2(int q, int p)
{
    parent_2[q] = p;
}
