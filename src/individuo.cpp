/*
 * individuo.cpp
 *
 *  Created on: 10 de jul de 2018
 *      Author: adamr
 */

#include "individuo.h"

Individuo::Individuo() : Output()
{
}

void Individuo::setRoute(unsigned int vehicle, unsigned int vertex)
{

	route[vehicle].push_back(vertex);
}

void Individuo::calculateFitness()
{

	setFitness(0);

	for (unsigned int vehicle = 0; vehicle < route.size(); vehicle++)
	{

		if (route[vehicle].size() > 0)
		{
			for (unsigned int i = 1; i < route[vehicle].size(); i++)
				setFitness(getFitness() + in->distance_matrix[route[vehicle][i - 1]][route[vehicle][i]]);
			
		}
	}
}
