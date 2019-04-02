/*
 * output.h
 *
 *  Created on: 10 de jul de 2018
 *      Author: adamr
 */

#ifndef OUTPUT_H_
#define OUTPUT_H_

#include "input.h"

class Output
{

  private:

	//Represents the value of route.
	int fitness;

  public:

	//Represents a pointer to class Input.
	Input *in;

	//Used to output a sequence of nodes representing the vertex of graph that was visited.
	vector<vector<int> > route;

	Output(Input *in);

	void printDistanceMatrix();

	void printRoute();

	void printFitness();

	void setFitness(int f);

	int getFitness();

};

#endif /* OUTPUT_H_ */
