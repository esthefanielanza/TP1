#include "quicksortExterno.h"


void leSuperior(FILE **leituraSuperior, int *ls, TLivro *Livro, int *alternaEsquerdaDireita){

	//Ajeitamos o apontador de leitura superior//
	fseek(*leituraSuperior, *ls * sizeof(TLivro), SEEK_SET);
	//Lemos o livro//
	leLivro(*leituraSuperior, Livro);
	//Colocamos a nova posição para o apontador de leitura superior//
	*ls = *ls - 1;
	//Sinalizamos que dá próxima vez será realizada uma leitura inferior//
	*alternaEsquerdaDireita = 0;
}

void leInferior(FILE **leituraInferior, int *li, TLivro *Livro, int *alternaEsquerdaDireita){

	//Lemos o livro//
	leLivro(*leituraInferior, Livro);
 	//Colocamos a nova posição para o apontador de leitura inferior//
	*li = *li + 1;
	//Sinalizamos que dá próxima vez será realizada uma leitura superior//
	*alternaEsquerdaDireita = 1;
}

void escreveMax(FILE **escritaSuperior, TLivro *Livro, int *es){
	
	//Ajeitamos o apontador de escrita superior//
	fseek(*escritaSuperior, *es * sizeof(TLivro) , SEEK_SET);
	escreveLivro(escritaSuperior, *Livro);
	//Colocamos a nova posição para o apontador de escrita superior//
	*es = *es - 1;
}

void escreveMin(FILE **escritaInferior, TLivro *Livro, int *ei){
	
	escreveLivro(escritaInferior, *Livro);
	//Colocamos a nova posição para o apontador de escrita superior//
	*ei = *ei + 1;
}

void preencheMemoria(FILE **leituraInferior, FILE **leituraSuperior, TLivro **memoria, int *memoriaUtilizada, int nLivrosMemoria, int *alternaEsquerdaDireita, int *li, int *ls){
	
	//Enquanto existir espaço na memória e livros a serem lidos//
	while(*memoriaUtilizada < nLivrosMemoria && *ls >= *li){
		//Alternamos entre ler um número de cima ou de baixo
		if(!*alternaEsquerdaDireita)
			leInferior(leituraInferior, li, memoria[*memoriaUtilizada], alternaEsquerdaDireita);
		else
			leSuperior(leituraSuperior, ls, memoria[*memoriaUtilizada], alternaEsquerdaDireita);
		//Indicamos que ocupamos mais um espaço na memória
		*memoriaUtilizada = *memoriaUtilizada + 1;
	}

}

void trocaLivroMemoria(FILE **escrita, int posicao, TLivro livroAtual, TLivro **memoria, int *e){

	int i;

	//Se vamos escrever o mínimo
	if(posicao == 0)
		escreveMin(escrita, memoria[posicao], e);
	
	//Se vamos escrever o máximo
	else
		escreveMax(escrita, memoria[posicao], e);

	//Zeramos a string de vetores
	for(i = 0; i < TITULO_LIVRO_MAX; i++)
		memoria[posicao]->titulo[i] = '\0';

	//Substituímos o livro de menor valor da memória pelo livro que está sendo lido atualmente//
	strcpy(memoria[posicao]->titulo, livroAtual.titulo);
	memoria[posicao]->disponivel = livroAtual.disponivel;
}

void particaoExterno(int esq, int dir, FILE **leituraInferior, FILE **leituraSuperior, FILE **escritaSuperior, FILE **escritaInferior, TLivro **memoria, int nLivrosMemoria, int *i, int *j){
 	
 	int k;

	//Ajustando variáveis para caminhar nos arquivos de acordo com leitura e escrita//
	int li = esq, ls = dir;
	int ei = esq, es = dir;

	//Variável para descobrir quantos elementos já temos na memória//
	int memoriaUtilizada = 0;

	//Coloca os ponteiros inferiores do arquivo na posição correta//
	fseek(*escritaInferior, ei * sizeof(TLivro), SEEK_SET);
	fseek(*leituraInferior, li * sizeof(TLivro), SEEK_SET);

	int alternaEsquerdaDireita = 0;

	TLivro livroAtual;

	//Ajuste de ponteiros para caso não seja criada nenhuma nova partição durante a execução//
	*i = esq - 1;
	*j = dir + 1;

	//Preenchemos a memória com o número de livros que cabe nela//
	preencheMemoria(leituraInferior, leituraSuperior, memoria, &memoriaUtilizada, nLivrosMemoria, &alternaEsquerdaDireita, &li, &ls);	
	quickSort(memoria, 0, memoriaUtilizada-1);

	//Enquanto ainda existir um livro há ser lido//
	while(ls >= li){

		//Lemos o próximo livro tomando cuidao para não sobreescrever ninguém//
		if(ls == es)
			leSuperior(leituraSuperior, &ls, &livroAtual, &alternaEsquerdaDireita);
		else if(li == ei)
			leInferior(leituraInferior, &li, &livroAtual, &alternaEsquerdaDireita);
		else if(!alternaEsquerdaDireita)
			leInferior(leituraInferior, &li, &livroAtual, &alternaEsquerdaDireita);
		else
			leSuperior(leituraSuperior, &ls, &livroAtual, &alternaEsquerdaDireita);

		//Comparamos se o livro vem antes do mininimo//
		if(strcmp(livroAtual.titulo, memoria[0]->titulo) < 0){
			//Sinalizamos que existe uma partição//
			*i = ei;
			//Escrevemos o mínimo no arquivo//
			escreveMin(escritaInferior, &livroAtual, &ei);
		}

		//Comparamos se o livro vem depois do maximo//
		else if(strcmp(livroAtual.titulo, memoria[memoriaUtilizada- 1 ]->titulo) > 0){
			*j = es;
			escreveMax(escritaSuperior, &livroAtual, &es);
		}

		//Se ele estiver entre o máximo e mínimo//
		else{
			
			//Verificamos qual apontador andou mais até então//
			//Se foi o escrita superior//
			if(ei - esq < dir - es)
				trocaLivroMemoria(escritaInferior, 0, livroAtual, memoria, &ei);

			//Se foi o escrita inferior//
			else
				trocaLivroMemoria(escritaSuperior, nLivrosMemoria - 1, livroAtual, memoria, &es);

			//Ordena memória por que trocamos livros da memória//
			insertionSort(memoria, memoriaUtilizada);
		}
	}

	//Descarrega memória no arquivo//
	for(k = 0; k < memoriaUtilizada; k++)
		escreveMin(escritaInferior, memoria[k], &ei);

	//Atualiza os arquivos//
	fflush(*leituraInferior);
	fflush(*leituraSuperior);
	fflush(*escritaInferior);
	fflush(*escritaSuperior);
}

void quicksortExterno(int dir, int esq, FILE **leituraInferior, FILE **leituraSuperior, FILE **escritaSuperior, FILE **escritaInferior, TLivro **memoria, int nLivrosMemoria){
	
	int i, j;
	
	//Se for uma partição inválida retornamos//
	if(dir - esq < 1)
		return;

	//Realizamos a ordenação para essa partição//
	particaoExterno(esq, dir, leituraInferior, leituraSuperior, escritaSuperior, escritaInferior, memoria, nLivrosMemoria, &i, &j);
	
	//Chama recursivamente para partições direita e esquerda//
	quicksortExterno(i, esq, leituraInferior, leituraSuperior, escritaSuperior, escritaInferior, memoria, nLivrosMemoria);	
	quicksortExterno(dir, j, leituraInferior, leituraSuperior, escritaSuperior, escritaInferior, memoria, nLivrosMemoria);
}

void ordena(int nLivros, int nLivrosMemoria){

	int i;

	FILE *leituraInferior, *leituraSuperior;
	FILE *escritaInferior, *escritaSuperior;

	//Abre os arquivos para arrumar os apontadores//
	leituraInferior = fopen("temp", "r+b"); if(!leituraInferior){ printf("Arquivo não existe\n"); exit(1);}
	leituraSuperior = fopen("temp", "r+b"); if(!leituraSuperior){ printf("Arquivo não existe\n"); exit(1);}
	escritaInferior = fopen("temp", "r+b"); if(!escritaInferior){ printf("Arquivo não existe\n"); exit(1);}
	escritaSuperior = fopen("temp", "r+b"); if(!escritaSuperior){ printf("Arquivo não existe\n"); exit(1);}

	//Criamos espaço para a memória interna//
	TLivro **memoria;
	memoria = malloc((nLivrosMemoria - 1) * sizeof(TLivro*));
	for(i = 0; i < nLivrosMemoria - 1; i++)
		memoria[i] = malloc(sizeof(TLivro));

	//Chamamos o quicksort externo//
	quicksortExterno(nLivros - 1, 0, &leituraInferior, &leituraSuperior, &escritaSuperior, &escritaInferior, memoria, nLivrosMemoria - 1);

	//Fechamos os arquivos//
	fclose(leituraInferior);
	fclose(leituraSuperior);
	fclose(escritaInferior);
	fclose(escritaSuperior);

	//Liberamos o espaço alocado para a memória//
	for(i = 0; i < nLivrosMemoria - 1; i++)
		free(memoria[i]);
	free(memoria);

}