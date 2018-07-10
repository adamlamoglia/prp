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

	for(unsigned int i = 0; i < rota.size() - 1; i++)
		fitness += in->matriz_distancias[rota[i]][rota[i+1]];

}

double Individuo::getFitness(){
	return fitness;
}

void Individuo::setRota(unsigned int id, unsigned int vertice){

	rota[id] = vertice;
}


