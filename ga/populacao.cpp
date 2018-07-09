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

	lista_de_individuos.resize(tamanho_inicial);

	for(int i = 0; i < lista_de_individuos.size(); i++){

		lista_de_individuos[i].veiculo_ = new Veiculo(grafo_->getQuantidadeVertices());
		lista_de_individuos[i].grafo_ = g;
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

void Populacao::calcularFitness(){
	double fitnessAtual = 0;

	for(int i = 0; i < lista_de_individuos.size(); i++){

		vector<int> rota = lista_de_individuos[i].veiculo_->rota_;
		fitnessAtual = 0;

		for(int x = 0; x < rota.size() - 1; x++)
			fitnessAtual += grafo_->matriz_de_adjacencia[rota[x]][rota[x+1]];


		lista_de_individuos[i].setFitness(fitnessAtual);
	}


}

void Populacao::imprimirRotaFitness(){
	vector<int> rota;

	for(int i = lista_de_individuos.size() - 1; i >= 0; i--){
		cout << "rota do Individuo " << i << endl;
		rota = lista_de_individuos[i].veiculo_->rota_;

		for(int x = 0; x < rota.size(); x++)
			cout << rota[x] << " ";
		cout << endl;

		cout << "fitness: " << lista_de_individuos[i].getFitness();
		cout << endl;
	}

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


	}

	calcularFitness();
	ordenarIndividuos();



}


