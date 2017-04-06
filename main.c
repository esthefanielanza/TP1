#include "biblioteca.h"

int main (void){

	//Deriáveis para a entrada//
	int nLivros, nLivrosMemoria, nEstantes, nLivrosEstante, nConsultas;

	//Lê entradas//
	scanf("%d %d %d %d %d", &nLivros, &nLivrosMemoria, &nEstantes, &nLivrosEstante, &nConsultas);

	//Inicializa todos os livros da biblioteca//
	inicializaLivros(nLivros);

	//Ordena os livros existentes na blbioteca//
	ordena(nLivros, nLivrosMemoria);
	
	//Cria arquivo para livros ordenados//
	criaLivrosOrdenados(nLivros);

	//Separa os livros em nEstantes//
	separaLivrosEstantes(nLivros, nEstantes, nLivrosEstante);

	//Verifica a situação do livro a partir de uma busca binária//
	consultaLivro(nConsultas, nEstantes);

	//Remove o arquivo temporário utilizado para ordenação//
	remove("temp");
	
	return 0;
}