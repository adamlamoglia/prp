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

	Individuo();

	void calculateFitness();

	void setRoute(unsigned int vehicle, unsigned int id, unsigned int vertex);

	int verifyPrecedent(unsigned int index, unsigned int real);


};


#endif /* INDIVIDUO_H_ */
