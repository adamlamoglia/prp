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
	index.resize(in->num_vertices, 0);

	fitness = 0;

}


void Output::printDistanceMatrix(){
	cout << "[";
	for(unsigned int i = 0; i < in->distance_matrix.size(); i++){
		for(unsigned int j = 0; j < in->distance_matrix.size(); j++){

			if(i != j)
				cout << fixed << setprecision(0) << in->distance_matrix[i][j] << ",";

		}

	}

	cout << "]";
}

void Output::printRoute(){

	for(unsigned int i = 0; i < route.size(); i++)
		cout << route[i]+1 << " ";

	cout << endl;

}

void Output::printIndexes(){

	for(unsigned int i = 0; i < in->num_vertices; i++)
		cout << index[i] << " ";

	cout << endl;

}

void Output::printFitness(){

	cout << fitness << endl;

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

