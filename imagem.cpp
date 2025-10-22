#include "imagem.h"
#include <opencv2/opencv.hpp>

Image_Manager::Image_Manager(std::string nome)
{
    nome_arquivo = nome;
    width = 0;
    height = 0;
}

void Image_Manager::salvar_imagem(Grafo *gr)
{

    cv::Mat nova_imagem(height, width, CV_8UC3, cv::Scalar(0, 0, 0));

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int index = (i * width + j);
            int cor = gr->grafo[i * width + j].cor;

            uchar r = (cor * cor * 20) % 256;
            uchar g = (cor * cor * 50) % 256;
            uchar b = (cor * cor * 100) % 256;

            nova_imagem.at<cv::Vec3b>(i, j) = cv::Vec3b(b, g, r);
        }
    }

    cv::imwrite("segmented_" + nome_arquivo, nova_imagem);
    cv::imshow("Imagem segmentada", nova_imagem);
    cv::waitKey(0);
    nova_imagem.release();
}

Grafo *Image_Manager::ler_imagem()
{
    cv::Mat imagem = cv::imread(nome_arquivo, cv::IMREAD_GRAYSCALE);

    if (imagem.empty())
    {
        throw std::runtime_error("Erro ao ler a imagem.");
    }

    width = imagem.cols;
    height = imagem.rows;

    Grafo *gr = new Grafo(width * height);

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            auto pixel_atual = imagem.at<uchar>(i, j);

            gr->grafo[i * width + j].peso = static_cast<int>(pixel_atual);

            if (j > 0)
            {
                gr->adicionar_aresta2(i * width + (j - 1), i * width + j);
            }

            if (i > 0)
            {
                gr->adicionar_aresta2((i - 1) * width + j, i * width + j);
            }
        }
    }

    imagem.release();
    return gr;
}