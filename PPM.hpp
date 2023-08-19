#ifndef PPM_H_INCLUDED
#define PPM_H_INCLUDED
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "PGM.hpp"
using namespace std;

// Dados da PPM
struct PPM
{
    string tipo;
    int largura;
    int altura;
    int vmax;
    unsigned char *pixels;

    PPM()
    {
        pixels = nullptr;
        largura = 0;
        altura = 0;
        vmax = 255;
        tipo = "";
    }
};

// Definidor de cor RGB
struct RGB
{
    unsigned char r, g, b;

    RGB()
    {
        r = 0;
        g = 0;
        b = 0;
    }

    RGB(unsigned char _r, unsigned char _g, unsigned char _b)
    {
        r = _r;
        g = _g;
        b = _b;
    }
};

// Imprime o RGB formatado
ostream &operator<<(ostream &os, const RGB rgb)
{
    return os << (int)rgb.r << ", " << (int)rgb.g << ", " << (int)rgb.b;
}

// Desaloca o objeto da imagem PPM
void destruir(PPM *ppm)
{
    if (ppm->pixels)
        delete ppm->pixels;

    ppm->pixels = nullptr;
    ppm->largura = 0;
    ppm->altura = 0;
    ppm->tipo = "";
    ppm->vmax = 255;
}

// Imprime as informações sobre a imagem PPM
void imprimir(PPM *ppm)
{
    cout << "\n * PPM * \n";
    cout << "Tipo: " << ppm->tipo << endl;
    cout << "Dimensao: " << ppm->largura << "x" << ppm->altura << endl;
    cout << "vMax: " << ppm->vmax << endl;

    if (ppm->pixels)
        cout << "Vetor de pixels: " << &(ppm->pixels) << endl;
    else
        cout << "Vetor de pixels: NULL\n";
}

// Cria uma imagem PPM com o fundo preto RGB(0,0,0)
void criar(PPM *ppm, int largura, int altura)
{
    if (ppm->pixels)
        delete ppm->pixels;

    int tamanho = largura * altura * 3;

    ppm->tipo = "P3";
    ppm->largura = largura;
    ppm->altura = altura;
    ppm->vmax = 255;
    ppm->pixels = new unsigned char[tamanho];

    for (int i = 0; i < tamanho; i++)
        ppm->pixels[i] = 0;
}

// Grava uma imagem PPM em um arquivo da memória
bool gravar(PPM *ppm, string caminho)
{
    if (!ppm->pixels)
        return false;

    ofstream arq;

    arq.open(caminho);
    if (!arq.is_open())
    {
        cout << "PPM: endereco do arquivo invalido\n";
        return false;
    }

    arq << ppm->tipo << endl;
    arq << ppm->largura << " " << ppm->altura << endl;
    arq << 255 << endl;

    int tam = ppm->largura * ppm->altura * 3;
    for (int i = 0; i < tam; i++)
    {
        arq << (int)ppm->pixels[i] << endl;
        arq.flush();
    }

    arq.close();
    return true;
}

// Lê uma linha do arquivo PPM, ignorando comentários (#)
string lerLinhaArquivoPPM(std::ifstream &arq)
{
    string linha = "", dadoLido = "";
    while (!arq.eof())
    {
        linha = "";
        std::getline(arq, linha);
        if (linha.size() > 0 && linha[0] != '#')
            return linha;
    }
    return linha;
}

// Lê todo o arquivo PPM, usando como função auxiliar a lerLinhaArquivoPPM
bool ler(PPM *ppm, string caminho)
{
    ifstream arq;
    string dado;
    stringstream str;

    arq.open(caminho);
    if (!arq.is_open())
    {
        cout << "PPM: endereco do arquivo invalido\n";
        return false;
    }

    dado = lerLinhaArquivoPPM(arq);
    if (dado == "P3")
        ppm->tipo = dado;
    else
    {
        cout << "PPM: erro ao ler o tipo da imagem\n";
        return false;
    }

    dado = lerLinhaArquivoPPM(arq);
    str = stringstream(dado);
    if (!(str >> ppm->largura))
    {
        cout << "PPM: erro ao ler a largura\n";
        return false;
    }
    if (!(str >> ppm->altura))
    {
        cout << "PPM: erro ao ler a largura\n";
        return false;
    }

    dado = lerLinhaArquivoPPM(arq);
    str = stringstream(dado);
    if (!(str >> ppm->vmax))
    {
        cout << "PPM: erro ao ler vmax\n";
        return false;
    }

    if (ppm->pixels)
        delete ppm->pixels;

    int tam = ppm->largura * ppm->altura * 3;
    ppm->pixels = new unsigned char[tam];

    int i = 0, p;
    while (!arq.eof())
    {

        if (arq >> p)
        {
            if (i < tam)
                ppm->pixels[i] = (unsigned char)p;
            i++;
        }
        else
            break;
    }

    if (i != tam)
    {
        cout << "PPM: erro ao ler os pixels\n";
        return false;
    }
    arq.close();

    return true;
}

// Retorna a cor RGB de um determinado pixel de uma imagem
RGB getPixel(PPM *ppm, int x, int y)
{
    RGB rgb;
    if (!ppm->pixels)
        return rgb;

    rgb.r = ppm->pixels[y * ppm->largura * 3 + x * 3];
    rgb.g = ppm->pixels[y * ppm->largura * 3 + x * 3 + 1];
    rgb.b = ppm->pixels[y * ppm->largura * 3 + x * 3 + 2];

    return rgb;
}

// Atribui uma cor passada como parâmetro para um determinado pixel de uma imagem
void setPixel(PPM *ppm, int x, int y, RGB rgb)
{
    if (!ppm->pixels)
        return;

    ppm->pixels[y * ppm->largura * 3 + x * 3] = rgb.r;
    ppm->pixels[y * ppm->largura * 3 + x * 3 + 1] = rgb.g;
    ppm->pixels[y * ppm->largura * 3 + x * 3 + 2] = rgb.b;
}

/*
Exercício 3:
Crie uma função para criar uma imagem PPM. A função deve conter os seguintes
parâmetros:
*/
void criar(PPM *ppm, int largura, int altura, RGB corFundo)
{
    if (ppm->pixels)
        delete ppm->pixels;

    int tamanho = largura * altura * 3;

    ppm->tipo = "P3";
    ppm->largura = largura;
    ppm->altura = altura;
    ppm->vmax = 255;
    ppm->pixels = new unsigned char[tamanho];

    for (int i = 0; i < tamanho; i += 3)
    {
        ppm->pixels[i] = corFundo.r;
        ppm->pixels[i + 1] = corFundo.g;
        ppm->pixels[i + 2] = corFundo.b;
    }
}

/*
Exercício 4:
Crie uma função para preencher uma determinada linha de uma imagem PPM com uma
cor específica passada por parâmetro.
*/
void setLinha(PPM *ppm, int linha, RGB cor)
{
    if (!ppm->pixels)
        return;

    for (int x = 0; x < ppm->largura; x++)
        setPixel(ppm, x, linha, cor);
}

/*
Exercício 5:
Crie uma função para verificar se as coordenadas de um pixel passadas por parâmetro
são válidas.
*/
bool coordValida(PPM *ppm, int x, int y)
{
    if (!ppm->pixels)
        return false;

    if (x < ppm->largura && x >= 0 && y < ppm->altura && y >= 0)
        return true;
    else
        return false;
}

/*
Exercício 6:
Implemente uma aplicação para marcar uma área em uma imagem PPM:
- O programa deve receber como entrada o caminho da imagem PPM, as
coordenadas dos pontos P1(x1, y1) e P2(x2,y2) e a cor RGB da linha.
- O programa deve prevenir erros quando as coordenadas ultrapassarem as
dimensões da imagem, traçando a linha somente na- O programa deve receber como entrada o caminho da imagem PPM, as
coordenadas dos pontos P1(x1, y1) e P2(x2,y2) e a cor RGB da linha.
- O programa deve prevenir erros quando as coordenadas ultrapassarem as
dimensões da imagem, traçando a linha somente nas coordenadas válidas da
imagem (use a função criada no exercício 5).s coordenadas válidas da
imagem (use a função criada no exercício 5).
*/
void marcarArea(PPM *ppm, int x1, int y1, int x2, int y2, RGB cor)
{
    if (!ppm->pixels)
        return;

    for (int x = x1; x <= x2; x++)
    {
        if (coordValida(ppm, x, y1))
            setPixel(ppm, x, y1, cor);

        if (coordValida(ppm, x, y2))
            setPixel(ppm, x, y2, cor);
    }

    for (int y = y1; y <= y2; y++)
    {
        if (coordValida(ppm, x1, y))
            setPixel(ppm, x1, y, cor);

        if (coordValida(ppm, x2, y))
            setPixel(ppm, x2, y, cor);
    }
}

/*
Exercício 7:
Crie uma imagem PPM de 500x500 pixels com fundo preto (colocar o valor zero para
todos os pixels). Em seguida, atribuir uma cor RGB gerada aleatoriamente a cada 50
linhas imagem.
*/
void pintarListras(PPM *ppm)
{
    if (!ppm->pixels)
        return;
    
    for (int y = 50; y <= ppm->altura; y += 50)
        setLinha(ppm, y, RGB(rand() % 255, rand() % 255, rand() % 255));
}

/*
Exercício 8:
Considere uma imagem PPM de entrada e uma região definida pelas coordenadas P1(x1,
y1) e P2(x2,y2). Desenvolva um método para criar uma imagem de saída, a qual possui a
mesma dimensão da imagem de entrada e a cor de todos os pixels é preta. Em seguida,
copie a região definida na imagem de entrada para a imagem de saída.
*/
void copiaSelecaoRegiao(PPM *ppm_1, PPM *ppm_2, int x1, int y1, int x2, int y2)
{
    if (!ppm_1->pixels)
        return;

    criar(ppm_2, ppm_1->altura, ppm_1->largura);
	imprimir(ppm_2);

    for (int y = y1; y < y2; y++) {

        for (int x = x1; x < x2; x++) {

            if (coordValida(ppm_1, x1, y1) && coordValida(ppm_1, x2, y2))
            {
                RGB corPixel = getPixel(ppm_1, x, y);
                setPixel(ppm_2, x, y, corPixel);
            }

        }

    }
}

/*
Exercício 9:
Crie um programa pra converter imagens PPM para PGM:
- Ler a imagem PPM;
- Criar uma imagem PGM com a mesma dimensão da imagem PPM e definir a
cor preta para todos pixels;
- Construir um laço para percorrer os pixels da imagem PPM. Para cada pixel
PPM(x, y), converta a cor RGB para cinza:
- Cinza = 0.299*R + 0.587*G + 0.114*B
- Atribuir a cor cinza calculada para o pixel na imagem PGM(x,y), na
mesma posição .
- Salvar a imagem PGM criada.
*/
void converterPPM_PGM(PPM *ppm, PGM *pgm)
{
    if (!ppm->pixels)
        return;

    criar(pgm, ppm->altura, ppm->largura);
	imprimir(pgm);

    for (int y = 0; y < ppm->altura; y++) {

        for (int x = 0; x < ppm->largura; x++) {

            if (coordValida(ppm, x, y) && coordValida(pgm, x, y))
            {
                RGB corPixel = getPixel(ppm, x, y);
                unsigned char pixelConvertido = 0.299 * corPixel.r + 0.587 * corPixel.g + 0.114 * corPixel.b;
                setPixel(pgm, x, y, pixelConvertido);
            }

        }

    }
}

/*
Exercício 10:
Implemente um método para inverter uma imagem PPM horizontalmente.
*/
void flipHorizontal(PPM *ppm)
{
    if (!ppm->pixels)
        return;

    RGB aux, aux2;
    for (int x = 0; x < ppm->largura / 2; x++)
    {

        for (int y = 0; y < ppm->altura; y++)
        {

            aux = getPixel(ppm, x, y);
            setPixel(ppm, x, y, getPixel(ppm, ppm->largura - x - 1, y));
            setPixel(ppm, ppm->largura - x - 1, y, aux);

        }

    }
}

/*
Exercício 11:
Implemente o exercício 6 novamente, permitindo que o usuário possa definir a largura
da borda. Por exemplo:
- Imagem: numeros.ppm
- Pixels: P1(391, 327), P2(574, 575)
- Largura da borda: 10 pixels
*/
void marcarAreaBorda(PPM *ppm, int x1, int y1, int x2, int y2, RGB cor, int borda)
{
    if (!ppm->pixels)
        return;

    for (int x = x1; x <= x2; x++)
    {

        for (int y = y1 - borda - 1; y <= y1; y++)
        {
            if (coordValida(ppm, x, y))
                setPixel(ppm, x, y, cor);
        }

        for (int y = y2 - borda - 1; y <= y2; y++)
        {
            if (coordValida(ppm, x, y))
                setPixel(ppm, x, y, cor);
        }

    }

    for (int y = y1; y <= y2; y++)
    {

        for (int x = x1 - borda - 1; x <= x1; x++)
        {
            if (coordValida(ppm, x, y))
                setPixel(ppm, x, y, cor);
        }

        for (int x = x2 - borda - 1; x <= x2; x++)
        {
            if (coordValida(ppm, x, y))
                setPixel(ppm, x, y, cor);
        }
        
    }
}

#endif