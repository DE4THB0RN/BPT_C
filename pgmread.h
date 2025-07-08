#include <string.h>
#include <stdio.h>
#include "grafo.h"

Grafo *grafo_arq(char *filename)
{
    int height;
    int width;
    FILE *arq;
    arq = fopen(filename, "r");

    if (!arq)
    {
        printf("Erro ao abrir arquivo\n");
    }

    printf("Abrindo arquivo\n");

    char *linha = (char *)malloc(100 * sizeof(char));

    fgets(linha, 100, arq);
    printf("Li a linha\n");
    if (!strcmp(linha, "P2"))
    {
        printf("Arquivo inválido");
        return NULL;
    }
    fgets(linha, 100, arq);
    fgets(linha, 100, arq);

    char *parte = strtok(linha, " ");
    width = atoi(parte);
    parte = strtok(NULL, " ");
    height = atoi(parte);

    fgets(linha, 100, arq);

    int lin = 0, col = 0;

    Grafo *novo = novo_grafo(height * width);

    while (fgets(linha, 100, arq))
    {

        novo->grafo[col * width + lin].peso = atoi(linha);

        if (lin > 0)
        {
            adicionar_aresta(col * height + lin, col * height + lin - 1, abs(novo->grafo[col * width + lin].peso - novo->grafo[col * width + lin - 1].peso), novo);
        }

        if (col > 0)
        {
            adicionar_aresta(col * height + lin, (col - 1) * height + lin, abs(novo->grafo[col * width + lin].peso - novo->grafo[(col - 1) * width + lin].peso), novo);
        }

        if (col > 0 && lin > 0)
        {
            adicionar_aresta(col * height + lin, (col - 1) * height + lin - 1, abs(novo->grafo[col * width + lin].peso - novo->grafo[(col - 1) * width + lin - 1].peso), novo);
        }

        if (col > 0 && lin < width - 1)
        {
            adicionar_aresta(col * height + lin, (col - 1) * height + lin + 1, abs(novo->grafo[col * width + lin].peso - novo->grafo[(col - 1) * width + lin + 1].peso), novo);
        }

        lin++;
        if (lin == width)
        {
            col++;
            lin = 0;
        }
    }

    fclose(arq);
    arq = NULL;

    return novo;
}