/*
 * individuo.h
 *
 *  Created on: 10 de jul de 2018
 *      Author: adamr
 */

#ifndef INDIVIDUO_H_
#define INDIVIDUO_H_

#include "output.h"


class Individuo: public Output {

public:

	Individuo(Input *in);

	int getFitness();

	void setFitness();

	void setRoute(unsigned int id, unsigned int vertex);

	void setStopIndex(unsigned int vertex);

	bool isStopIndex(unsigned int vertex);

	int returnVertex(unsigned int vertex);

	int verifyPrecedent(unsigned int index, unsigned int real);

	//void setNumberVehicles(int num);


};


#endif /* INDIVIDUO_H_ */
