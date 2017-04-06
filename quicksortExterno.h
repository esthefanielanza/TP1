#ifndef QUICKSORTEXTERNO_H
#define QUICKSORTEXTERNO_H

#include "biblioteca.h"
#include "ordenacaoInterna.h"

/*---------------------------------------------------------------------------------------------
Protótipo: leSuperior(FILE **leituraSuperior, int *ls, TLivro *Livro, int *alternaEsquerdaDireita);
Função: Lê um livro da parte superior do arquivo
Entrada: O arquivo com apontador para leitura superior, o apontador superior, um ponteiro para
armazenar o livro lido e a variavel responsável por alternar entre esquerda e direita. 
Saída: Não retorna nada.
---------------------------------------------------------------------------------------------*/
void leSuperior(FILE **leituraSuperior, int *ls, TLivro *Livro, int *alternaEsquerdaDireita);

/*---------------------------------------------------------------------------------------------
Protótipo: void leInferior(FILE **leituraInferior, int *li, TLivro *Livro, int *alternaEsquerdaDireita);
Função: Lê um livro da parte inferior do arquivo
Entrada: O arquivo com apontador para leitura inferior, o apontador inferior, um ponteiro para
armazenar o livro lido e a variavel responsável por alternar entre esquerda e direita. 
Saída: Não retorna nada.
---------------------------------------------------------------------------------------------*/
void leInferior(FILE **leituraInferior, int *li, TLivro *Livro, int *alternaEsquerdaDireita);

/*---------------------------------------------------------------------------------------------
Protótipo: void escreveMax(FILE **escritaSuperior, TLivro *Livro, int *es);
Função: Escreve um livro na parte superior do arquivo.
Entrada: O arquivo com apontador para escrita suprerior, o apontador superior, o livro a ser 
escrito.
Saída: Não retorna nada.
---------------------------------------------------------------------------------------------*/
void escreveMax(FILE **escritaSuperior, TLivro *Livro, int *es);

/*---------------------------------------------------------------------------------------------
Protótipo: void escreveMin(FILE **escritaInferior, TLivro *Livro, int *ei);
Função: Escreve um livro na parte inferior do arquivo.
Entrada: O arquivo com apontador para escrita inferior, o apontador inferior, o livro a ser 
escrito.
Saída: Não retorna nada.
---------------------------------------------------------------------------------------------*/
void escreveMin(FILE **escritaInferior, TLivro *Livro, int *ei);

/*---------------------------------------------------------------------------------------------
Protótipo: void particaoExterno(int esq, int dir, FILE **leituraInferior, FILE **leituraSuperior, FILE **escritaSuperior, FILE **escritaInferior, TLivro **memoria, int nLivrosMemoria, int *i, int *j);
Função: Ordena partição.
Entrada: Recebe o arquivos, um vetor que representa a memória disponível, os marcadores das 
novas partições i e j e as posições esquerda e direita.
Saída: Não retorna nada.
---------------------------------------------------------------------------------------------*/
void particaoExterno(int esq, int dir, FILE **leituraInferior, FILE **leituraSuperior, FILE **escritaSuperior, FILE **escritaInferior, TLivro **memoria, int nLivrosMemoria, int *i, int *j);

/*---------------------------------------------------------------------------------------------
Protótipo: void quicksortExterno(int dir, int esq, FILE **leituraInferior, FILE **leituraSuperior, FILE **escritaSuperior, FILE **escritaInferior, TLivro **memoria, int nLivrosMemoria);
Função: Realiza o quicksort chamando a função de partição.
Entrada: Recebe as posições direita e esquerda, os arquivos, a memória disponível e o número
de livros que cabem mna memória
Saída: Não retorna nada.
---------------------------------------------------------------------------------------------*/
void quicksortExterno(int dir, int esq, FILE **leituraInferior, FILE **leituraSuperior, FILE **escritaSuperior, FILE **escritaInferior, TLivro **memoria, int nLivrosMemoria);

/*---------------------------------------------------------------------------------------------
Protótipo: void ordena(int nLivros, int nLivrosMemoria);
Função: Responsável por abrir arquivos e chamar a função quicksort
Entrada: Recebe o número total de livros e o número de livros que cabem na memória.
Saída: Não retorna nada.
---------------------------------------------------------------------------------------------*/
void ordena(int nLivros, int nLivrosMemoria);

#endif