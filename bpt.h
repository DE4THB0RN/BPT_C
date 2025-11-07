#include <stdlib.h>
#include "grafo.h"
#ifndef BPT_H
#define BPT_H

class NoBPT
{
protected:
    int marca;

private:
    NoBPT *dir;
    NoBPT *esq;
    NoBPT *pai;

public:
    void set_dir(NoBPT *d);
    void set_esq(NoBPT *e);
    void set_pai(NoBPT *p);

    NoBPT *get_dir();
    NoBPT *get_esq();
    NoBPT *get_pai();
    void aumenta_marca();
    void diminui_marca();
    int get_marca();

    virtual ~NoBPT();
};

class No_Aresta : public NoBPT
{

public:
    int de;
    int para;
    int peso;
    No_Aresta(int d, int p, int w);
};

class No_Vertice : public NoBPT
{
private:
    int vertice;

public:
    No_Vertice(int v);
};

class BPT
{
private:
    No_Aresta *raiz;
    std::vector<No_Vertice *> folhas;

    void delete_tree(NoBPT *atual);

public:
    BPT(int numV);
    ~BPT();

    void adicionar_seeds(int *seeds, int numseeds, Grafo *gr);
    void remover_seeds(int *seeds, int numseeds, Grafo *gr);
    void remover_seed(int seed, Grafo *gr);
    void kruskal(Grafo *gr);
};

#endif // BPT_H