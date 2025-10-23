#include <stdlib.h>
#include "bpt.h"
#include "grafo.h"
#ifndef KRSUKAL_H
#define KRSUKAL_H

class Tarjan
{
public:
    static int find(int *parent, int q);
    static void union_k(int *parent, int *rank, int x, int y);
};

#endif // KRSUKAL_H
