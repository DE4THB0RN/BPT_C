#include "bpt.h"

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

    parent = new int[numV * 2 - 1];
    size = 0;
}

BPT::~BPT()
{
    delete_tree(raiz);
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

void BPT::make_set(int q)
{
    parent[q] = -1;
    size++;
}