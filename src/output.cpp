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
	rota.resize(in->quantidade_vertices + 1, 0);

	fitness = 0;

}


void Output::imprimirMatrizDeDistancias(){

	for(unsigned int i = 0; i < in->matriz_distancias.size(); i++){
		for(unsigned int j = 0; j < in->matriz_distancias.size(); j++){

			cout << in->matriz_distancias[i][j] << " - ";
		}
		cout << endl;
	}
}

void Output::imprimirRota(){

	for(unsigned int i = 0; i < rota.size(); i++)
		cout << rota[i] << " ";

	cout << endl;

}

void Output::imprimirFitness(){

	cout << fitness << endl;

}

