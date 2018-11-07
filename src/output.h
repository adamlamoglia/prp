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

	vector<int> new_route;

	//Indicates the beginning and end of a route from a vehicle 
	pair<int,int> vehicle;

	//Sequence of indexes related to vehicle route
	vector<int> index;

	Output(Input *in);

	void printDistanceMatrix();

	void printRoute();

	void printIndexes();

	void printFitness();

	void printArray2d();

	void fitness_set(int f);

	void newFitnessSet(int f);

	int newFitnessGet();

	int fitness_get();

	void setStart(int index_start);

	void setEnd(int index_end);

private:
	//Represents the value of route.
	int fitness;
	int new_fitness;
};

#endif /* OUTPUT_H_ */
