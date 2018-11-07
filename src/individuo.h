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

	int getNewFitness();

	void setFitness();

	void setNewFitness();

	void setRoute(unsigned int id, unsigned int vertex);

	void setNewRoute(unsigned int id, unsigned int vertex);

	void setIndexes();


};


#endif /* INDIVIDUO_H_ */
