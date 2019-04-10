/*
 * output.cpp
 *
 *  Created on: 10 de jul de 2018
 *      Author: adamr
 */

#include "output.h"
#include <cassert>

Output::Output()
{

	this->in = Input::getInstance();


	route.resize(in->num_vertices, vector<int>(in->num_vertices, 0));
	fleet.resize(in->num_vertices, Vehicle(in->capacity) );

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
		bool routeExists = false;
		
		for(unsigned int j = 0; j < route[i].size(); j++){
			if(j == 0 && route[i][j] != 0){
				cout << "route #" << i + 1 << ": ";
				routeExists = true;
			}
			if(route[i][j] != 0)
				cout << route[i][j] << " ";
		}
		
		if(routeExists)
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
