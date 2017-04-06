#ifndef ORDENACAOINTERNA_H
#define ORDENACAOINTERNA_H

#include "biblioteca.h"

/*---------------------------------------------------------------------------------------------
Protótipo: int particao(TLivro **memoria, int esq, int dir);
Função: Ordena partição do quicksort externo.
Entrada: O vetor a ser ordenado e as posições de esquerda e direita.
Saída: Retorna um inteiro referente a nova partição
---------------------------------------------------------------------------------------------*/
int particao(TLivro **memoria, int esq, int dir);

/*---------------------------------------------------------------------------------------------
Protótipo: void quickSort(TLivro **memoria, int esq, int dir);
Função: Realiza o quicksort interno.
Entrada: O vetor a ser ordenado e as posições de esquerda e direita.
Saída: Não retorna nada.
---------------------------------------------------------------------------------------------*/
void quickSort(TLivro **memoria, int esq, int dir);

/*---------------------------------------------------------------------------------------------
Protótipo: void insertionSort(TLivro **memoria, int tamanho);
Função: Realiza o insertion sort.
Entrada: O vetor a ser ordenado e o tamanho dele.
Saída: Não retorna nada.
---------------------------------------------------------------------------------------------*/
void insertionSort(TLivro **memoria, int tamanho);

#endif

