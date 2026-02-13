#include "imagem.h"
#include <opencv2/opencv.hpp>

Image_Manager::Image_Manager(std::string nome)
{
    nome_arquivo = nome;
    width = 0;
    height = 0;
}

int Image_Manager::get_width()
{
    return width;
}

int Image_Manager::get_height()
{
    return height;
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

            uchar r = (cor * cor * cor * 30) % 256;
            uchar g = (cor * cor * 10) % 256;
            uchar b = (cor * cor * 70 + cor) % 256;

            nova_imagem.at<cv::Vec3b>(i, j) = cv::Vec3b(b, g, r);
        }
    }

    cv::imwrite("segmented_" + nome_arquivo, nova_imagem);
    cv::imshow("Imagem segmentada", nova_imagem);
    cv::waitKey(0);
    nova_imagem.release();
}

void Image_Manager::salvar_imagem2(Grafo *gr, const std::string &caminho_saida)
{

    cv::Mat nova_imagem(height, width, CV_8UC3, cv::Vec3b(0, 0, 255));
    int atual = 0, seed;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            seed = gr->segmentos[atual];
            srand(seed);
            nova_imagem.at<cv::Vec3b>(i, j) = cv::Vec3b(rand() % 255, rand() % 255, rand() % 255);
            atual++;
        }
    }

    cv::imwrite(caminho_saida, nova_imagem);

    cv::namedWindow("Imagem segmentada", cv::WINDOW_NORMAL);
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

    int vertices = width * height;

    Grafo *gr = new Grafo(vertices);
    int index = 0;

    gr->width = width;
    gr->height = height;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            auto pixel_atual = imagem.at<uchar>(i, j);

            // gr->grafo[i * width + j].peso = static_cast<int>(pixel_atual);

            // if (j > 0)
            // {
            //     gr->adicionar_aresta2(i * width + (j - 1), i * width + j);
            // }

            // if (i > 0)
            // {
            //     gr->adicionar_aresta2((i - 1) * width + j, i * width + j);
            // }

            if (j + 1 < width)
            {
                auto pixel_direita = imagem.at<uchar>(i, j + 1);
                gr->adicionar_aresta_alter(index, std::abs(pixel_atual - pixel_direita));
            }
            else
            {
                gr->adicionar_aresta_alter(index, -1);
            }
            index++;
            if (i + 1 < height)
            {
                auto pixel_baixo = imagem.at<uchar>(i + 1, j);
                gr->adicionar_aresta_alter(index, std::abs(pixel_atual - pixel_baixo));
            }
            else
            {
                gr->adicionar_aresta_alter(index, -1);
            }
            index++;
        }
    }

    imagem.release();

    gr->ordenar_arestas();

    std::cout << "Imagem lida com sucesso!" << std::endl;
    return gr;
}

int Image_Manager::processar_seed(int x, int y)
{
    if (y > height || x > width)
    {
        throw std::runtime_error("Valor inválido");
    }
    int resp = y * width + x;

    return resp;
}