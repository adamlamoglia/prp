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

	fitness_set(fitness_get() + in->distance_matrix[0][vehicle.first]);

	for(unsigned int i = 0; i < route.size() - 1; i++)
		fitness_set( fitness_get() + in->distance_matrix[route[i]][route[i+1]]);

	fitness_set(fitness_get() + in->distance_matrix[vehicle.second][0]);

}

int Individuo::getFitness(){
	return fitness_get();
}

void Individuo::setRoute(unsigned int id, unsigned int vertex){

	route[id] = vertex;
}

void Individuo::setIndexes(){

	for(unsigned int i = 1; i < route.size() - 1; i++){
		index[route[i]] = i;
	}
}


