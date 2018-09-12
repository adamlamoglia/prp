/*
 * individuo.cpp
 *
 *  Created on: 10 de jul de 2018
 *      Author: adamr
 */

#include "individuo.h"


Individuo::Individuo(Input *in) : Output(in) {

}

void Individuo::setFitness(){
	fitness = 0;

	for(unsigned int i = 0; i < route.size() - 1; i++)
		fitness += in->distance_matrix[route[i]][route[i+1]];

}

int Individuo::getFitness(){
	return fitness;
}

void Individuo::setRoute(unsigned int id, unsigned int vertex){

	route[id] = vertex;
}


