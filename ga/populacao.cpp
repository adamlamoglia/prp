/*
 * populacao.cpp
 *
 *  Created on: 12 de mai de 2018
 *      Author: adamr
 */

#include "populacao.h"

using namespace std;

Populacao::Populacao(Grafo *g, int tamanho_inicial) {
	grafo_ = g;
	tamanho = tamanho_inicial;

	//individuoInicial = new Individuo(-1, g);

	lista_de_individuos.resize(tamanho_inicial);

	for(int i = 0; i < lista_de_individuos.size(); i++){

		lista_de_individuos[i].veiculo_ = new Veiculo(grafo_->getQuantidadeVertices());

	}

}

int Populacao::getTamanho(){
	return tamanho;
}

Grafo* Populacao::getGrafo(){
	return grafo_;
}

bool Populacao::procurarIndividuoPorFitness(double fitness){

	for(int i = 0; i < lista_de_individuos.size(); i++)
		if(fitness == lista_de_individuos[i].getFitness())
			return true;

	return false;
}

bool ordemCrescente(Individuo a, Individuo b){
	return a.getFitness() < b.getFitness();
}

void Populacao::ordenarIndividuos(){
	sort(lista_de_individuos.begin(), lista_de_individuos.end(), ordemCrescente);
}

double Populacao::calcularFitness(vector<int> &rota){
	double fitnessAtual = 0;


	for(int i = 0; i < rota.size() - 1; i++)
		fitnessAtual += grafo_->matriz_de_adjacencia[rota[i]][rota[i+1]];



	// EF = 147
	//TODO: ADAPTAR RETORNO PARA PRP
	return fitnessAtual;
}


void Populacao::gerarPrimeiraGeracao(){
	vector<bool> vertices_visitados;
	int vertice_aleatorio;
	vertices_visitados.resize(grafo_->getQuantidadeVertices(),false);


	for(int i = 0; i < getTamanho(); i++){

		//criacao de vetor auxiliar para controlar aleatoriedade
		for(int j = 0; j < vertices_visitados.size(); j++)
			vertices_visitados[j] = false;

		vertices_visitados[0]  =  true;


		for(int j = 1; j < grafo_->getQuantidadeVertices(); j++){

			//os vertices sao escolhidos no intervalo de 1 a vertices-1
			vertice_aleatorio = rand() % (grafo_->getQuantidadeVertices() - 1) + 1;

			while(vertices_visitados[vertice_aleatorio]){
				vertice_aleatorio = rand() % (grafo_->getQuantidadeVertices() - 1) + 1;
			}

			lista_de_individuos[i].veiculo_->rota_[j] = vertice_aleatorio;

			vertices_visitados[vertice_aleatorio] = true;

		}

		lista_de_individuos[i].setFitness(calcularFitness(lista_de_individuos[i].veiculo_->rota_));


	}

	ordenarIndividuos();


}


