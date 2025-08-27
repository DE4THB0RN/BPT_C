#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#ifndef UTILIDADES_H
#define UTILIDADES_H

typedef struct MST_Edge
{
    int de;
    int para;
    int peso;
} MST_Edge;

typedef struct MST_Edge_List
{
    MST_Edge *arestas;
    int numArestas;
} MST_Edge_List;

typedef struct Item
{
    int chave;
    int valor;
    struct Item *prox;
} Item;

typedef struct Dicionario
{
    int quantItens;
    Item *inicio;
    Item *final;
} Dicionario;

Dicionario *criar_dicionario()
{
    Dicionario *novo = (Dicionario *)malloc(sizeof(Dicionario));
    novo->quantItens = 0;
    novo->inicio = NULL;
    novo->final = NULL;
    return novo;
}

void novo_item(int chave, Dicionario *di)
{
    Item *novo = (Item *)malloc(sizeof(Item));
    novo->chave = chave;
    novo->valor = 0;
    novo->prox = NULL;
    if (di->inicio == NULL)
    {
        di->inicio = novo;
    }
    if (di->final != NULL)
    {
        di->final->prox = novo;
    }
    di->final = novo;
}

void add_no_item(int chave, Dicionario *di)
{
    Item *temp = di->inicio;
    bool parada = false;
    while (temp != NULL && !parada)
    {
        if (temp->chave == chave)
        {
            temp->valor++;
            parada = true;
        }
        temp = temp->prox;
    }
}

int valor_do_item(int chave, Dicionario *di)
{
    Item *temp = di->inicio;
    int resp = -1;
    bool parada = false;
    while (temp != NULL && !parada)
    {
        if (temp->chave == chave)
        {
            resp = temp->valor;
            parada = true;
        }
        temp = temp->prox;
    }
    return resp;
}

int quant_item(int chave, Dicionario *di)
{
    int resp = -1;
    Item *temp = di->inicio;
    bool parada = false;
    while (temp != NULL && !parada)
    {
        if (temp->chave == chave)
        {
            resp = temp->valor;
            parada = true;
        }
        temp = temp->prox;
    }

    return resp;
}

void remover_item(int chave, Dicionario *di)
{
    Item *temp = di->inicio;
    bool parada = false;
    while (temp != NULL && !parada)
    {
        if (temp->prox->chave == chave)
        {
            Item *a_remover = temp->prox;
            temp->prox = a_remover->prox;
            free(a_remover);
            a_remover = NULL;
            di->quantItens--;
            parada = true;
        }
        temp = temp->prox;
    }
}

#endif // UTILIDADES_H