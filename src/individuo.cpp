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

	for(unsigned int i = 0; i < route.size() - 1; i++){
		
		if(route[i].id == 0 && route[i+1].id == 0)
			break;

		fitness_set( fitness_get() + in->distance_matrix[route[i].id][route[i+1].id]);

	}
		

}

int Individuo::getFitness(){
	return fitness_get();
}

void Individuo::setRoute(unsigned int index, unsigned int vertex){

	route[index].id = vertex;
}


void Individuo::setNumVehicles(int num){
	this->num_vehicles = num;
}

int Individuo::getNumVehicles(){
	return num_vehicles;
}



