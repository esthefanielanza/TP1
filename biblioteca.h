#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define TITULO_LIVRO_MAX 51
#define NOME_ARQUIVO_ESTANTE 20

//Struct para representar um livro
typedef struct TLivro{
	
	//Titulo do livro
	char titulo[TITULO_LIVRO_MAX];

	//Identifica se o livro está disponível na biblioteca ou emprestado
	char disponivel;

	//Adicional apenas para funções estéticas na hora de escrever um arquivo binário//
	char adicionalFormatacao[2];

} TLivro;

#include "quicksortExterno.h"
#include "ordenacaoInterna.h"

/*---------------------------------------------------------------------------------------------
Protótipo: void leLivro(FILE *arquivo, TLivro *livroAtual);
Função: Lê um livro de um arquivo.
Entrada: Recebe o arquivo e uma variável para armazenar o livro.
Saída: Não retorna nada.
---------------------------------------------------------------------------------------------*/
void leLivro(FILE *arquivo, TLivro *livroAtual);

/*---------------------------------------------------------------------------------------------
Protótipo: void escreveLivro(FILE **arquivo, TLivro livroAtual);
Função: Escreve um livro em um arquivo.
Entrada: Recebe o arquivo e o livro para ser escrito.
Saída: Não retorna nada.
---------------------------------------------------------------------------------------------*/
void escreveLivro(FILE **arquivo, TLivro livroAtual);

/*---------------------------------------------------------------------------------------------
Protótipo: FILE** criaEstantes(int nEstantes, int escrita);
Função: Cria um vetor de arquivos para armazenar as estantes.
Entrada: O número de estantes e se os arquivos serão abertos para escrita ou leitura.
Saída: Retorna um vetor de arquivos.
---------------------------------------------------------------------------------------------*/
FILE** criaEstantes(int nEstantes, int escrita);

/*---------------------------------------------------------------------------------------------
Protótipo: void fechaArquivosEstantes(int nEstantes, FILE** estantes);
Função: Desaloca espaço do vetor de estantes e fecha o arquivo
Entrada: O número de estantes e o vetor de estantes.
Saída: Não retorna.
---------------------------------------------------------------------------------------------*/
void fechaArquivosEstantes(int nEstantes, FILE** estantes);

/*---------------------------------------------------------------------------------------------
Protótipo: void inicializaLivros(int nLivros);
Função: Lê os livros do stdin e os escreve em um arquivo temporário
Entrada: O número de livros.
Saída: Não retorna nada.
---------------------------------------------------------------------------------------------*/
void inicializaLivros(int nLivros);

/*---------------------------------------------------------------------------------------------
Protótipo: void separaLivrosEstantes(int nLivros, int nEstantes, int nLivrosEstantes);
Função: Separa os livros já ordenados em estantes e cria um arquivo de indices
Entrada: O número de livros, o número de estantes e o número de livros por estante.
Saída: Não retorna nada.
---------------------------------------------------------------------------------------------*/
void separaLivrosEstantes(int nLivros, int nEstantes, int nLivrosEstantes);

/*---------------------------------------------------------------------------------------------
Protótipo: char pesquisaBinaria(char *nomeLivro, int esq, int dir, FILE *estante, int *posicao);
Função: Pesquisa se um livro está em uma estante.
Entrada: O título do livro procurado, as diretrizes direita e esquerda, a estante e um apontador
para a posição que será alterada internamente caso o arquivo seja encontrado.
Saída: Retorna a disponibilidade do livro encontrado. 0 Emprestado/1 Disponível/2 Livro não 
econtrado.
---------------------------------------------------------------------------------------------*/
char pesquisaBinaria(char *nomeLivro, int esq, int dir, FILE *estante, int *posicao);

/*---------------------------------------------------------------------------------------------
Protótipo: int encontraEstante(char *nomeLivro, char *maiorIndice, char *menorIndice, FILE *indice, char *disponivel, int nEstantes);
Função: Faz uma pesquisa sequencial para descobrir qual a provavél estante que o livro pertence
Entrada: O nome do livro, o maior indice da estante, o menor indice, o arquivo de indices, um 
ponteiro para sinalizar a disponibilidade de um livro e o número de estantes 
Saída: Retorna o número da estante.
---------------------------------------------------------------------------------------------*/
int encontraEstante(char *nomeLivro, char *maiorIndice, char *menorIndice, FILE *indice, char *disponivel, int nEstantes);

/*---------------------------------------------------------------------------------------------
Protótipo: void consultaLivro(int nConsultas, int nEstantes);
Função: Realiza uma consulta de um livro imprimindo sua disponibilidade no stdout
Entrada: O número de consultas a serem realizadas e o número de estante.
Saída: Não retorna nada.
---------------------------------------------------------------------------------------------*/
void consultaLivro(int nConsultas, int nEstantes);

/*---------------------------------------------------------------------------------------------
Protótipo: void criaLivrosOrdenados(int nLivros);
Função: Transfere os livros do arquivo binário para um txt.
Entrada: O número de livros.
Saída: Não retorna nada.
---------------------------------------------------------------------------------------------*/
void criaLivrosOrdenados(int nLivros);

#endif