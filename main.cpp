#include <iostream>
#include "PPM.hpp"

using namespace std;

int main(void)
{
	srand(time(NULL));

	// Exercício 3
	PPM ex3;
	criar(&ex3, 5, 7, RGB(0, 128, 128));
	gravar(&ex3, "imagens/exercicio3.ppm");
	destruir(&ex3);

	// Exercício 4
	PPM ex4;
	ler(&ex4, "imagens/exercicio3.ppm");
	setLinha(&ex4, 2, RGB(255, 0, 0));
	gravar(&ex4, "imagens/exercicio4.ppm");
	destruir(&ex4);

	// Exercício 5
	PPM ex5;
	ler(&ex5, "imagens/exercicio3.ppm");
	if (coordValida(&ex5, 4, 6))
		cout<< "Coordenada válida";
	else
		cout<< "Coordenada inválida";
	destruir(&ex5);

	// Exercício 6
	PPM ex6;
	ler(&ex6, "imagens/numeros.ppm");
	marcarArea(&ex6, 200, 4, 390, 250, RGB(255,0,0));
	gravar(&ex6, "imagens/exercicio6.ppm");
	destruir(&ex6);

	// Exercício 7
	PPM ex7;
	criar(&ex7, 500, 500);
	pintarListras(&ex7);
	gravar(&ex7, "imagens/exercicio7.ppm");
	destruir(&ex7);

	// Exercício 8
	PPM ex8_1, ex8_2;
	ler(&ex8_1, "imagens/numeros.ppm");
	copiaSelecaoRegiao(&ex8_1, &ex8_2, 200, 4, 390, 250);
	gravar(&ex8_2, "imagens/exercicio8.ppm");
	destruir(&ex8_1);
	destruir(&ex8_2);

	// Exercício 9
	PPM ex9_1;
	PGM ex9_2;
	ler(&ex9_1, "imagens/numeros.ppm");
	converterPPM_PGM(&ex9_1, &ex9_2);
	gravar(&ex9_2, "imagens/exercicio9.pgm");
	destruir(&ex9_1);
	destruir(&ex9_2);

	// Exercício 10
	PPM ex10;
	ler(&ex10, "imagens/numeros.ppm");
	flipHorizontal(&ex10);
	gravar(&ex10, "imagens/exercicio10.ppm");
	destruir(&ex10);

	// Exercício 11
	PPM ex11;
	ler(&ex11, "imagens/numeros.ppm");
	marcarAreaBorda(&ex11, 200, 4, 390, 250, RGB(255,0,0), 5);
	gravar(&ex11, "imagens/exercicio11.ppm");
	destruir(&ex11);
	
	cout << "Pressione uma tecla para encerrar o programa.\n";
	getchar();
	return EXIT_SUCCESS; 
}
