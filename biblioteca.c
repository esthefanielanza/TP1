#include "biblioteca.h"

void leLivro(FILE *arquivo, TLivro *livroAtual){

	fread(livroAtual->titulo, sizeof(livroAtual->titulo), 1, arquivo);
	fread(livroAtual->adicionalFormatacao, sizeof(char), 1, arquivo);
	fread(&livroAtual->disponivel, sizeof(livroAtual->disponivel), 1, arquivo);
	fread(livroAtual->adicionalFormatacao, sizeof(char), 1, arquivo);
}

void escreveLivro(FILE **arquivo, TLivro livroAtual){

	fwrite(livroAtual.titulo, sizeof(livroAtual.titulo), 1, *arquivo);
	fwrite(" ", sizeof(char), 1, *arquivo);
	fwrite(&livroAtual.disponivel, sizeof(livroAtual.disponivel), 1, *arquivo);
	fwrite("\n", sizeof(char), 1, *arquivo);
}

FILE** criaEstantes(int nEstantes, int escrita){

	int i;
	
	FILE **estantes;
	
	//Aloca espaço para as estantes//
	estantes = malloc(nEstantes * sizeof(FILE*));
	if(!estantes) { perror(NULL); exit(EXIT_FAILURE); }
	
	char estanteAtual[NOME_ARQUIVO_ESTANTE];

	//Cria estantes para leitura ou escrita//
	for(i = 0; i < nEstantes; i++){
		
		//Escreve o nome do arquivo da estante atual//
		snprintf(estanteAtual, sizeof(estanteAtual), "estante%d", i);
		
		//Cria estantes para escrita//
		if(escrita)
			estantes[i] = fopen(estanteAtual, "w+b");
		
		//Para consulta//
		else
			estantes[i] = fopen(estanteAtual, "rb");

		if(!estantes[i]) { perror(NULL); exit(EXIT_FAILURE); }
	}

	return estantes;
}

void fechaArquivosEstantes(int nEstantes, FILE** estantes){

	int i;

	//Fecha estantes//
	for(i = 0; i < nEstantes; i++)
		fclose(estantes[i]);
	
	free(estantes);
}

void inicializaLivros(int nLivros){
	
	int i, j;

	//Variável auxiliar para armazenar dados do livro lido//
	TLivro livro;

	//Cria o arquivo binário//
	FILE *temp;

	//Abre o arquivo binário//
	temp = fopen("temp", "wb");
	if(!temp){ printf("Arquivo não existe\n"); exit(1);}

	//Para cada livro
	for(i = 0; i < nLivros; i++){

		//Preenche a string com '\0'"
		for(j = 0; j < TITULO_LIVRO_MAX; j++){
			livro.titulo[j] = '\0';
		}

		//Lê o input com o título e disponibilidade//
		scanf("%s %c", livro.titulo, &livro.disponivel);
		//Escreve no arquivo binário//
		escreveLivro(&temp, livro);
	}

	//Fecha arquivo binário//
	fclose(temp);
}

void separaLivrosEstantes(int nLivros, int nEstantes, int nLivrosEstantes){

	int i;
	FILE *livrosOrdenados;
	livrosOrdenados = fopen("temp", "rb"); if(!livrosOrdenados){ printf("Arquivo não existe\n"); exit(1);}

	FILE **estantes;
	estantes = criaEstantes(nEstantes, 1);

	TLivro livroAtual;

	int estanteAtual = 0, trocaEstante = 0;

	//Escrevemos os índices em outro arquivo//
	FILE *indice;
	indice = fopen("indice", "w"); if(!indice){printf("Arquivo não existe\n"); exit(1);}

	//Separa livros em estantes//
	for(i = 0; i < nLivros; i++){
		
		leLivro(livrosOrdenados, &livroAtual);
		escreveLivro(&estantes[estanteAtual], livroAtual);

		trocaEstante++;

		//Trocamos de estante assim que atingimos o número máximo de livros por estante//
		if(trocaEstante == nLivrosEstantes){
			if(i < nLivros - 1){
				estanteAtual++;
				trocaEstante = 0;
			}
		}

		//Calcula se é o primeiro ou o ultimo livro da estante para escreve-lo no arquivo de indices//
		if(i == estanteAtual * nLivrosEstantes)
			fprintf(indice, "%s ", livroAtual.titulo);

		if(trocaEstante == 0){
			fprintf(indice, "%s\n", livroAtual.titulo);
		}
	}

	//Imprimimos o ultimo livro no indice//
	fprintf(indice, "%s\n", livroAtual.titulo);

	//Preenchemos o arquivo de indice com # para as estantes vazias//
	for(i = estanteAtual; i < nEstantes - 1; i++)
		fprintf(indice, "#\n");

	fclose(indice);
	fclose(livrosOrdenados);
	fechaArquivosEstantes(nEstantes, estantes);

}

char pesquisaBinaria(char *nomeLivro, int esq, int dir, FILE *estante, int *posicao){

	TLivro livroAtual;
	
	int pivo;

	//Enquanto o ponteiro da esquerda não ultrapassar o da direita//
	while(dir >= esq){

		//Definimos o elemento central como pivô//
		pivo = (dir + esq)/2;

		//Acessamos sua posição no arquivo em O(1)//
		fseek(estante, pivo*sizeof(TLivro), SEEK_SET);
		leLivro(estante, &livroAtual);

		//Verificamos se seu titulo é igual ao do livro procurado//
		if(strcmp(nomeLivro, livroAtual.titulo) == 0){
			*posicao = pivo;
			return livroAtual.disponivel;
		}

		//Se ele for maior, caminhamos para a partição da direita//
		if(strcmp(nomeLivro, livroAtual.titulo) < 0)
			dir = pivo - 1;

		//Se não, para a partição da esquerda//
		else
			esq = pivo + 1;
		
	}

	return '2';
}

int encontraEstante(char *nomeLivro, char *maiorIndice, char *menorIndice, FILE *indice, char *disponivel, int nEstantes){
	
	int estanteAtual = 0;

	//Enquanto o nome do livro for maior que o maior indice, vamos para a pŕoxima estante//
	while(strcmp(nomeLivro, maiorIndice) > 0){
				
		if(strcmp(nomeLivro, menorIndice) < 0){
			*disponivel = '2';
				break;
		}
				
		//Vamos para a próxima estante//
		estanteAtual++;

		//Lemos os próximo indice//
		fscanf(indice, "%s", menorIndice);
			
		if(menorIndice[0] != '#')
			fscanf(indice, "%s", maiorIndice);

		else 
			break;

		//Se acabaram as estantes retornamos que o livro não foi encontrado//
		if(estanteAtual > nEstantes){
			*disponivel = '2';
			break;
		}
	}
	
	return estanteAtual;	
}

void consultaLivro(int nConsultas, int nEstantes){
	
	int i;
	int estanteAtual = 0, livrosEstantes, posicao;

	char nomeLivro[TITULO_LIVRO_MAX];
	char menorIndice[TITULO_LIVRO_MAX], maiorIndice[TITULO_LIVRO_MAX];

	FILE *indice;
	FILE **estantes;

	char disponivel;

	//Abre arquivos//
	indice = fopen("indice", "r");
	estantes = criaEstantes(nEstantes, 0);

	for(i = 0; i < nConsultas; i++){

		disponivel = 0;

		//A cada consulta volta ao ínicio do arquivo de indices//
		fseek(indice, 0, SEEK_SET);

		scanf("%s", nomeLivro);

		//Verifica o menor indice//
		fscanf(indice, "%s", menorIndice);
		
		//Se ele for diferente do símbolo para estante vazia, verificamos qual é o maior//
		if(menorIndice[0] != '#'){
			
			fscanf(indice, "%s", maiorIndice);

			if(strcmp(nomeLivro, menorIndice) < 0)
				disponivel = '2';

			//Encontra estante que o livro pertence//
			estanteAtual = encontraEstante(nomeLivro, maiorIndice, menorIndice, indice, &disponivel, nEstantes);

			if(disponivel != '2'){
				//Calculamos o número de livros no arquivo//
				fseek(estantes[estanteAtual], 0, SEEK_END);
				livrosEstantes = ftell(estantes[estanteAtual])/sizeof(TLivro);
				
				//Voltamos ao inicio do arquivo//
				fseek(estantes[estanteAtual], 0, SEEK_SET);

				//Realizamos a busca binária//
				disponivel = pesquisaBinaria(nomeLivro, 0, livrosEstantes, estantes[estanteAtual], &posicao);
			}

			//Se o livro não foi encontrado imprimimos//
			if(disponivel == '2')
				printf("livro nao encontrado\n");

			//Se o livro está emprestado imprimimos//
			else if(disponivel == '0')
				printf("emprestado\n");

			//Se o livro está na biblioteca imprimimos sua estante e posição//
			else
				printf("disponivel na posicao %d na estante %d\n", posicao, estanteAtual);
			
			//Voltamos para estante 0 para realizar a próxima consulta//
			estanteAtual = 0;
		}
	}

	//Fecha os arquivos//
	fechaArquivosEstantes(nEstantes, estantes);
	fclose(indice);
}

void criaLivrosOrdenados(int nLivros){

	int i;

	FILE *temp, *livrosOrdenados;
	temp = fopen("temp", "r+b");
	livrosOrdenados = fopen("livros_ordenados", "w");

	TLivro livroAtual;

	//Transferência dos livros ordenados de um arquivo binário para um .txt//
	for(i = 0; i < nLivros; i++){
		leLivro(temp, &livroAtual);
		fprintf(livrosOrdenados, "%s", livroAtual.titulo);
		fprintf(livrosOrdenados, " %c\n", livroAtual.disponivel);
	}

	fclose(temp);
	fclose(livrosOrdenados);
}
