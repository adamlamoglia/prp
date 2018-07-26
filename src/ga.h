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
		limit,
		lucky_factor,
		random_person,
		lucky_number,
		cut_size;

	double probability;

	vector<bool> visited_vertex,
				 inserted_vertex_f1,
				 inserted_vertex_f2,
				 repeated_vertex_f1,
				 repeated_vertex_f2;

	vector<Individuo> population;

	Genetic(Input *in, int alfa, int beta, int generations, double prob_mutation, int num_individuals);

	void init();
	void run();
	void sortPopulation();
	void binaryTour(Individuo &i1, Individuo &i2, Individuo &p1, Individuo &p2);
	void onePointCrossover(Individuo &p1, Individuo &p2, Individuo &f1, Individuo &f2);
	void twoOpt(Individuo *solution);
	void acception(Individuo *f1, Individuo *f2);
	bool searchFitness(Individuo *solution);
	void removeRepetitions(Individuo &f1, Individuo &f2);
	void insertVertices(Individuo &f1, Individuo &f2);

};


#endif /* GA_H_ */
