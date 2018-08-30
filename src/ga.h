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

	bool no_improvement;

	int alfa_max,
		beta_max,
		limit,
		random_person,
		lucky_number,
		cut_size,
		cut;

	double probability,
		   lucky_factor,
		   lowest_fitness,
		   new_fitness;

	vector<bool> visited_vertex,
				 inserted_vertex_f1,
				 inserted_vertex_f2,
				 repeated_vertex_f1,
				 repeated_vertex_f2;

	vector<Individuo> population;

	Genetic(Input *in, int alfa, int beta, int generations, double prob_mutation, int num_individuals, double lucky);
	~Genetic();

	void init();
	void create(int limit);
	void run();
	void sortPopulation();
	void binaryTour(Individuo &i1, Individuo &i2, Individuo &p1, Individuo &p2);
	void onePointCrossover(Individuo &p1, Individuo &p2, Individuo &f1, Individuo &f2);
	void twoOpt(Individuo &f, Individuo &s);
	void twoOptSwap(Individuo &s, int i, int k);
	void acception(Individuo &s);
	bool searchFitness(Individuo &s);
	void removeRepetitions(Individuo &f1, Individuo &f2);
	void insertVertices(Individuo &f1, Individuo &f2);
	void showResult();
	void printPopulation();
	void partialReplacement();

};


#endif /* GA_H_ */
