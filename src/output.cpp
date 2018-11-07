/*
 * output.cpp
 *
 *  Created on: 10 de jul de 2018
 *      Author: adamr
 */

#include "output.h"
#include <cassert>


Output::Output(Input *in) {

	this->in = in;

	//o tamanho da rota tem um valor a mais, pois sempre ha o retorno para o deposito
	route.resize(in->num_vertices + 1, 0);

	new_route.resize(in->num_vertices - 1, 0);
	
	index.resize(in->num_vertices, 0);
	
	fitness = 0;

	vehicle.first = 0;
	vehicle.second = 0;
}


void Output::printDistanceMatrix(){

	cout << "[";
	for(unsigned int i = 0; i < in->distance_matrix.size(); i++){
		for(unsigned int j = 0; j < in->distance_matrix.size(); j++){

				cout  << in->distance_matrix[i][j] << ",";

		}

	}

	cout << "]";
}

void Output::printRoute(){

	for(unsigned int i = 0; i < route.size(); i++)
		cout << route[i]+1 << " ";

	cout << endl;

}

void Output::fitness_set(int f){
		
	this->fitness =  f;
}

void Output::newFitnessSet(int f){

	this->new_fitness = f;
}

int Output::newFitnessGet(){
	return new_fitness;
}

int Output::fitness_get(){
	return this->fitness;
}

void Output::printIndexes(){

	for(unsigned int i = 0; i < in->num_vertices; i++)
		cout << index[i] << " ";

	cout << endl;

}

void Output::printFitness(){

	std::cout << "Best " << fitness << std::endl;

}

void Output::setStart(int index_start){

	vehicle.first = index_start;
}

void Output::setEnd(int index_end){

	vehicle.second = index_end;
}

