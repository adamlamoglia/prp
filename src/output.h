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
	//Represents a pointer to class Input.
	Input *in;

	//Used to output a sequence of nodes representing the vertex of graph that was visited.
	vector<int> route;

	//Represents the value of route.
	double fitness;

	Output(Input *in);
	void printDistanceMatrix();
	void printRoute();
	void printFitness();
	void printArray2d();//for minizinc


};

#endif /* OUTPUT_H_ */
