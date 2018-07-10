/*
 * ga.cpp
 *
 *  Created on: 10 de jul de 2018
 *      Author: adamr
 */

#include "ga.h"


Ga::Ga(Input *in, int alfa, int beta, int num_geracoes, double prob_mutacao, int quantidade_individuos) {

	this->in = in;

	alfa_maximo = alfa;
	beta_maximo = beta;
	numero_geracoes = num_geracoes;
	probabilidade_mutacao = prob_mutacao;

	populacao.resize(quantidade_individuos, Individuo(in));

	vertices_visitados.resize(in->quantidade_vertices,false);

}

bool ordemCrescenteDeFitness(Individuo a, Individuo b){
	return a.getFitness() < b.getFitness();
}

void Ga::ordenarPopulacao(){
	sort(populacao.begin(), populacao.end(), ordemCrescenteDeFitness);
}

void Ga::inicializarPopulacao(){
	int vertice_aleatorio;

	for(unsigned int i = 0; i < populacao.size(); i++){

		for(unsigned int j = 0; j < vertices_visitados.size(); j++)
					vertices_visitados[j] = false;

		vertices_visitados[0]  =  true;


		for(unsigned int indice_vertice = 1; indice_vertice < in->quantidade_vertices; indice_vertice++){

			//os vertices sao escolhidos no intervalo de 1 a vertices-1
			vertice_aleatorio = rand() % (in->quantidade_vertices - 1) + 1;

			while(vertices_visitados[vertice_aleatorio]){
				vertice_aleatorio = rand() % (in->quantidade_vertices - 1) + 1;
			}

			populacao[i].setRota(indice_vertice,vertice_aleatorio);

			vertices_visitados[vertice_aleatorio] = true;

		}

		populacao[i].setFitness();
	}

	ordenarPopulacao();
}

void Ga::realizarOperacaoGenetica(){

	Individuo pai1(in),
			  pai2(in),
			  filho1(in),
			  filho2(in);

	inicializarPopulacao();

	for(unsigned int i = 0; i < populacao.size(); i++){
		populacao[i].imprimirRota();
		populacao[i].imprimirFitness();
	}

}

