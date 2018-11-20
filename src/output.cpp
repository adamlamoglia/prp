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
	stop_index.resize(in->num_vertices + 1, false);

	fitness = 0;

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
		cout << route[i] << " ";

	cout << endl;

}

void Output::fitness_set(int f){
	if(f < 0){
		cout<<"erro"<<endl;
		exit(0);
	}
	
	this->fitness =  f;
}

int Output::fitness_get(){
	return this->fitness;
}

void Output::printStopIndexes(){

	for(unsigned int i = 0; i < stop_index.size(); i++)
		if(stop_index[i])
			cout << i << " ";
		else
			cout << stop_index[i] << " ";

	cout << endl;

}

void Output::printFitness(){

	std::cout << "Best " << fitness << std::endl;

}

void Output::printArray2d(){
	cout << "[" << endl;
	for(unsigned int i = 1; i <= in->num_vertices; i++){
		for(unsigned int j = 1; j <= in->num_vertices; j++){
			if(i != j){
					cout << i << "," << j << ",";
			}

		}
	}
	cout << "]);" << endl;
}

