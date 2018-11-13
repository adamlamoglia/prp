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

	for(unsigned int i = 0; i < route.size() - 1; i++){
		
		if(isStopIndex(route[i]))
			fitness_set( fitness_get() + in->distance_matrix[route[i]][route[0]] + in->distance_matrix[route[0]][route[i+1]]);
		else
			fitness_set( fitness_get() + in->distance_matrix[route[i]][route[i+1]]);
	}
		

}

int Individuo::getFitness(){
	return fitness_get();
}

void Individuo::setRoute(unsigned int id, unsigned int vertex){

	route[id] = vertex;
}

void Individuo::setStopIndex(unsigned int vertex){
	stop_index[vertex] = true;
}

bool Individuo::isStopIndex(unsigned int vertex){

	return stop_index[vertex];
}



