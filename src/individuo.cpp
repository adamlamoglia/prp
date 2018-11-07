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

	fitness_set(0);

	for(unsigned int i = 0; i < route.size() - 1; i++)
		fitness_set( fitness_get() + in->distance_matrix[route[i]][route[i+1]]);

}

void Individuo::setNewFitness(){

	newFitnessSet(newFitnessGet() + in->distance_matrix[0][vehicle.first]);

	for(unsigned int i = 0; i < route.size() - 1; i++)
		newFitnessSet( newFitnessGet() + in->distance_matrix[route[i]][route[i+1]]);

	newFitnessSet(newFitnessGet() + in->distance_matrix[vehicle.second][0]);
	
}

int Individuo::getFitness(){
	return fitness_get();
}

int Individuo::getNewFitness(){
	return newFitnessGet();
}

void Individuo::setRoute(unsigned int id, unsigned int vertex){

	route[id] = vertex;
}

void Individuo::setNewRoute(unsigned int id, unsigned int vertex){
	new_route[id] = vertex;
}

void Individuo::setIndexes(){

	for(unsigned int i = 1; i < route.size() - 1; i++){
		index[route[i]] = i;
	}
}


