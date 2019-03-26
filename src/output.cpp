/*
 * output.cpp
 *
 *  Created on: 10 de jul de 2018
 *      Author: adamr
 */

#include "output.h"
#include <cassert>

Output::Output(Input *in)
{

	this->in = in;

	route.resize(in->num_vertices * 2 + 1, Client(0,0,0));
	fleet.resize(in->num_vertices, Vehicle(in->capacity));

	fitness = 0;
}

void Output::printVehicles()
{
	for (unsigned int i = 0; i < route.size(); i++)
			cout << route[i].vehicle << " ";

	cout << endl;
}

void Output::printCapacities(){

		for (unsigned int i = 0; i < fleet.size(); i++)
			cout << fleet[i].capacity << " ";

		cout << endl;
}

void Output::printDistanceMatrix()
{
	cout << "   ";
	for(int i = 0; i < in->distance_matrix.size(); i++){
		cout << i << " ";
	}
	cout << endl;
	for (unsigned int i = 0; i < in->distance_matrix.size(); i++)
	{
		cout << i << "| ";

		for (unsigned int j = 0; j < in->distance_matrix.size(); j++)
		{

			cout << in->distance_matrix[i][j] << " ";
		}
		cout << endl;
	}

}

void Output::printRoute()
{

	for (unsigned int i = 0; i < route.size(); i++)
		cout << route[i].id << " ";

	cout << endl;
}

void Output::fitness_set(int f)
{
	if (f < 0)
	{
		//cout << "erro" << endl;
		//exit(0);
	}

	this->fitness = f;
}

int Output::fitness_get()
{
	return this->fitness;
}

void Output::printFitness()
{

	std::cout << "Best " << fitness << std::endl;
}

void Output::printResult()
{
	for(int i = 0; i < num_vehicles; i++){

		cout << "Route #" << i + 1 << ":" << " ";

		for(int j = 0; j < route.size(); j++)
			if(route[j].vehicle == i + 1)
				cout << route[j].id << " ";

		cout << endl;
	}
}

