/*
 * individuo.cpp
 *
 *  Created on: 12 de mai de 2018
 *      Author: adamr
 */

#include "individuo.h"


Individuo::Individuo(double fitness,Grafo *grafo) {
	fitness_ = fitness;
	grafo_ = grafo;
	veiculo_ = new Veiculo(grafo->getQuantidadeVertices()+1);


}

Individuo::Individuo(){

}

void Individuo::setFitness(double fitness){
	this->fitness_ = fitness;
}

void Individuo::calcularFitnessIndividual(){
	double fitness_atual = 0;
	vector<int> rota = veiculo_->rota_;

	for(int i = 0; i < rota.size() - 1; i++)
		fitness_atual += grafo_->matriz_de_adjacencia[rota[i]][rota[i+1]];


	this->setFitness(fitness_atual);
}

double Individuo::getFitness(){
	return fitness_;
}



