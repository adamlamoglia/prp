/*
 * output.h
 *
 *  Created on: 10 de jul de 2018
 *      Author: adamr
 */

#ifndef OUTPUT_H_
#define OUTPUT_H_

#include "input.h"


class Output {

public:
	Input *in;
	vector<unsigned int> route;
	double fitness;

	Output(Input *in);
	void printDistanceMatrix();
	void printRoute();
	void printFitness();


};

#endif /* OUTPUT_H_ */
