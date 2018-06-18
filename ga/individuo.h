/*
 * individuo.h
 *
 *  Created on: 12 de mai de 2018
 *      Author: adamr
 */

#ifndef INDIVIDUO_H_
#define INDIVIDUO_H_

#include <vector>

#include "../estrutura/veiculo.h"
#include "../estrutura/grafo.h"

using namespace std;

class Individuo {
private:

	//valor de EF associado
	double fitness_;

public:
	Individuo(double fitness,Grafo *grafo);
	Individuo();
	//atributo associado ao PTSP
	Veiculo* veiculo_;


	void setFitness(double fitness);
	double getFitness();
};

#endif /* INDIVIDUO_H_ */
