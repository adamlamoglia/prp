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
		fitnessAtual += grafo_->lista_de_adjacencia[rota[i]][rota[i+1]];

	// EF = 147
	return fitnessAtual*147;
}


void Populacao::gerarPrimeiraGeracao(){
	vector<bool> vertices_visitados;
	int vertice_aleatorio;

	for(int i = 0; i < getTamanho(); i++){

		//criacao de vetor auxiliar para controlar aleatoriedade
		vertices_visitados.resize(grafo_->getQuantidadeVertices(),false);
		vertices_visitados[0] = vertices_visitados[vertices_visitados.size() - 1] = true;

		for(int j = 1; j < lista_de_individuos[i].veiculo_->rota_.size() - 1; j++){

			//os vertices sao escolhidos no intervalo de 1 a vertices-2
			vertice_aleatorio = rand() % (grafo_->getQuantidadeVertices() - 2) + 1;

			while(vertices_visitados[vertice_aleatorio])
				vertice_aleatorio = rand() % (grafo_->getQuantidadeVertices() - 2) + 1;

			lista_de_individuos[i].veiculo_->rota_[j] = vertice_aleatorio;
		}

		lista_de_individuos[i].setFitness(calcularFitness(lista_de_individuos[i].veiculo_->rota_));
	}

	ordenarIndividuos();
}


