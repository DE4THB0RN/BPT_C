#include <stdio.h>
#include "pgmread.h"

int main()
{
    Grafo *grafo1 = grafo_arq("teste1.pgm");
    printf("Não crashei");
    return 0;
}