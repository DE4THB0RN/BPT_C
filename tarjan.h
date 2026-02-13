#include <stdlib.h>
#include "bpt.h"
#include "grafo.h"
#ifndef KRSUKAL_H
#define KRSUKAL_H

class Tarjan
{
private:
    static int find_1(BPT *bpt, int q);
    static int find_2(BPT *bpt, int q);

public:
    static int find(BPT *bpt, int q);
    static int union_k1(BPT *bpt, int x, int y);
    static int union_k2(BPT *bpt, int x, int y);
    static int union_k(BPT *bpt, int x, int y);
};

#endif // KRSUKAL_H
