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

	this->in = in->getInstance();


	route.resize(in->num_vertices, vector<int>(in->num_vertices, 0));

	fitness = 0;
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

	for (unsigned int i = 0; i < route.size(); i++){
		cout << "route #" << i + 1 << ": ";

		for(unsigned int j = 0; j < route[i].size(); j++)
			cout << route[i][j] << " ";
		
		cout << endl;
	}
}

void Output::setFitness(int f)
{
	if (f < 0)
	{
		//cout << "erro" << endl;
		//exit(0);
	}

	this->fitness = f;
}

int Output::getFitness()
{
	return this->fitness;
}

void Output::printFitness()
{

	std::cout << "Best " << fitness << std::endl;
}
