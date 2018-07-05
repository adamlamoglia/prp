/*
 * individuo.cpp
 *
 *  Created on: 12 de mai de 2018
 *      Author: adamr
 */

#include "individuo.h"


Individuo::Individuo(double fitness,Grafo *grafo) {
	fitness_ = fitness;
	veiculo_ = new Veiculo(grafo->getQuantidadeVertices()+1);

}

Individuo::Individuo(){

}

void Individuo::setFitness(double fitness){
	fitness_ = fitness;
}

double Individuo::getFitness(){
	return fitness_;
}



