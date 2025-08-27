#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include "grafo.h"

#ifndef IMAGEM_H
#define IMAGEM_H

void salvar_imagem(char *nome, Grafo *gr)
{

    int width = gr->width;
    int height = gr->height;
    unsigned char *img = (unsigned char *)malloc(width * height * 3);

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int index = (i * width + j) * 3;
            int cor = gr->grafo[i * width + j].cor;

            unsigned char r = (cor * cor * 5) % 256;
            unsigned char g = (cor * cor * 30) % 256;
            unsigned char b = (cor * cor * 40) % 256;

            img[index] = r;
            img[index + 1] = g;
            img[index + 2] = b;
        }
    }

    stbi_write_png(nome, width, height, 3, img, width * 3);
    free(img);
    img = NULL;
}

#endif // IMAGEM_H