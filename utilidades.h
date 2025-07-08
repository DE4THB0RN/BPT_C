#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

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

void adiciona_item(int chave, Dicionario *di)
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