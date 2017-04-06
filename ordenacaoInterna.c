#include "ordenacaoInterna.h"

int particao(TLivro **memoria, int esq, int dir){

	int i = esq, j = dir;
	
	TLivro *temp;

	int x;

	//Obtém pivô//
	x = (i + j)/2; 

	//Enquanto o ponteiro da esquerda não ultrapassar o da direita//
	do{
		
		//Se o livro i for menor que o pivô//
		while(strcmp(memoria[i]->titulo, memoria[x]->titulo) < 0)
			i++;
		
		//Se o livro j for maior que o pivô//
		while(strcmp(memoria[j]->titulo, memoria[x]->titulo) > 0)
			j--;

		if(i <= j){
			temp = memoria[i];
			memoria[i] = memoria[j];
			memoria[j] = temp;
			i++;
			j--;
		}

	} while(i <= j);

	return i;
}


void quickSort(TLivro **memoria, int esq, int dir){
	
	int p = 0;
	p = particao(memoria, esq, dir);

	//Chamamos a função recursivamente para a esquerda e direita//
	if(esq < p - 1)
		quickSort(memoria, esq, p - 1);
	if(dir > p)
		quickSort(memoria, p, dir);
}

void insertionSort(TLivro **memoria, int tamanho){

	TLivro *livroAtual;
	int i, j;

	//Enquanto não passarmos por todos os livros//
	for(i = 1; i < tamanho; i++){
		
		livroAtual = memoria[i];
		j = i - 1;		
		
		//Enquanto o livro atual for menor que o anterior//
		while(j >= 0 && strcmp(livroAtual->titulo, memoria[j]->titulo) < 0){
			//Trocamos os dois//
			memoria[j+1] = memoria[j];
			j--;
		}

		memoria[j + 1] = livroAtual;
	}
}
