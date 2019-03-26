/*
 * output.h
 *
 *  Created on: 10 de jul de 2018
 *      Author: adamr
 */

#ifndef OUTPUT_H_
#define OUTPUT_H_

#include "input.h"
#include "client.h"
#include "vehicle.h"


class Output {

public:
	//Represents a pointer to class Input.
	Input *in;

	//Used to output a sequence of nodes representing the vertex of graph that was visited.
	vector<Client> route;

	vector<Vehicle> fleet;

	int num_vehicles;

	//int number_vehicles;

	Output(Input *in);

	void printDistanceMatrix();

	void printRoute();

	void printFitness();

	void fitness_set(int f);

	void printVehicles();

	void printCapacities();

	int fitness_get();

	void printResult();
	
private:
	//Represents the value of route.
	int fitness;
};

#endif /* OUTPUT_H_ */
