// Teste_Filtro_Mediano.cpp : Defines the entry point for the console application.
//Allyson Martins
#include "stdafx.h"
#include <stdio.h>
//Declaração de variavéis globais
int largura,altura,limiteCor;
int entrada[500][500],saida[500][500],aux[9];

//Inicializacao das funcoes
void FiltroMediano();void scanTamanho(FILE &Imagem);
void LerImagem(FILE &imagemEntrada,FILE &NovaImagem);
int Limites(int posicao, int delta, int tamanho);

/*Aqui a funcao main abre os arquivos de leitura e de escrita respectivamente e aplica as funcoes necessarias
para a aplicacao do filtro.*/
int main()
{
	FILE * ImagemEntrada;
	FILE * NovaImagem;
	fopen_s(&ImagemEntrada,"teste.pgm", "r");
	fopen_s(&NovaImagem,"ImagemNova.pgm", "w");
	scanTamanho(*ImagemEntrada);
	LerImagem(*ImagemEntrada,*NovaImagem);
	printf("Median Filter aplicado com sucesso.\n\n");
	return 0;
}

//Funcao calcula limites da matriz
int Limites(int posicao, int delta, int tamanho){
	if(posicao + delta > tamanho || posicao + delta <0)
		return posicao - delta;
	else
		return posicao + delta;
}
//Algoritmo de ordenacao: Ordena o vetor de modo crescente (Algoritmo de ordenacao por selecao)
void selection_sort(){
	int i,j,axiliar;
	for(i=0;i<9;i++)
		for(j=i+1; j<9; j++){
			if(aux[i] > aux[j]){
				axiliar = aux[i];
				aux[i] = aux[j];
				aux[j] = axiliar;
			}
		}
}
//Funcao de aplicação do filtro
//Essa funcao faz varredura da imagem e seleciona uma submatriz de tamanho 3x3 para que seja aplicado o filtro. 
void FiltroMediano(){
	int i,x,y;
	for(y=0;y<altura;y++){
			for(x=0;x<largura;x++){
				for(i=0;i<9;i++){
					aux[i] = entrada[Limites(y,i/3-1,altura-1)][Limites(x,i%3-1,largura-1)];	
				}
				selection_sort();
				saida[y][x] = aux[4];
			}
		}
}
//Scanea os valores da imagem, largura,altura e limite da cor.
void scanTamanho(FILE &Imagem){
	fgetc(&Imagem);
	fgetc(&Imagem);
	fscanf_s(&Imagem,"%d%d%d", &largura,&altura,&limiteCor);	
}
//Funcao de leitura da imagem de entrada
//Essa funcao faz a leitura dos valores do pixel da imagem e repassa para a matriz de entrada
void LerImagem(FILE &imagemEntrada,FILE &NovaImagem){
	int i,j,x,y;
	for(y=0; y<altura; y++)
		for(x=0;x<largura;x++)
			fscanf_s(&imagemEntrada,"%d",&entrada[y][x]);

		FiltroMediano();
		fprintf_s(&NovaImagem,"P2\n%d %d\n%d\n",largura,altura,limiteCor);

		for(i=0; i<altura; i++)
			for(j=0; j<largura; j++)
				fprintf_s(&NovaImagem,"%d ", saida[i][j]);

		fclose(&imagemEntrada);
		fclose(&NovaImagem);
}

