#include "grafo.h"
#include <string>
#include <opencv2/opencv.hpp>

#ifndef IMAGEM_H
#define IMAGEM_H

class Image_Manager
{
private:
    std::string nome_arquivo;
    int width;
    int height;

public:
    Image_Manager(std::string nome);
    Grafo *ler_imagem();
    void salvar_imagem(Grafo *gr);
    int processar_seed(int x, int y);
};

#endif // IMAGEM_H