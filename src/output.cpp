/*
 * output.cpp
 *
 *  Created on: 10 de jul de 2018
 *      Author: adamr
 */

#include "output.h"



Output::Output(Input *in) {

	this->in = in;

	//o tamanho da rota tem um valor a mais, pois sempre ha o retorno para o deposito
	route.resize(in->num_vertices + 1, 0);

	fitness = 0;

}


void Output::printDistanceMatrix(){
	cout << "[";
	for(unsigned int i = 0; i < in->distance_matrix.size(); i++){
		for(unsigned int j = 0; j < in->distance_matrix.size(); j++){

			if(i != j)
				cout << in->distance_matrix[i][j] << "," << endl;

		}

	}

	cout << "]";
}

void Output::printRoute(){

	for(unsigned int i = 0; i < route.size(); i++)
		cout << route[i] << " ";

	cout << endl;

}

void Output::printFitness(){

	cout << fitness << endl;

}

