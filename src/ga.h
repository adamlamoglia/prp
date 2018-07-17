/*
 * ga.h
 *
 *  Created on: 10 de jul de 2018
 *      Author: adamr
 */

#ifndef GA_H_
#define GA_H_

#include "individuo.h"
#include <algorithm>
#include <utility>

class Genetic{

public:
	Input *in;

	int alfa_max,
		beta_max,
		limit;

	double probability;

	vector<bool> visited_vertex;

	vector<Individuo> population;

	Genetic(Input *in, int alfa, int beta, int generations, double prob_mutation, int num_individuals);

	void init();
	void run();
	void sortPopulation();
	void binaryTour();
	void onePointCrossover();
	void twoOpt(Individuo solution);
	void acception();
	bool searchFitness(Individuo solution);

};


#endif /* GA_H_ */
