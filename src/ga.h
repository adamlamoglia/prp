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

    //Represents a pointer to class Input, that contains size of graph and distance matrix.
	Input *in;

	//Used in twoOpt() to indicate improvement of an individual.
	bool no_improvement;

	//Used in run(), and means the number of times that individuals mutate (twoOpt).
	int alfa_max;

	//Used in run(). Means the times of a change in the best individual of population.
	int	beta_max;

	//Represents the limit of generations of populations (stop criterion).
	int	limit;

	//Used to pick up an random individual in population.
	int	random_person;

	//Used to select a node randomly to swap with another in crossover.
	int random_node1;

	//Same as above.
	int random_node2;

	//Represents a number to choose the parents to Crossover.
	//Used in binaryTour().
	int	lucky_number;

	//Used to crossover the chosen parents.
	//A size of cut is chosen and the split of chromosomes occurs
	//at the point indicated by the cut size.
	int	cut_size;

	//Used in partial replacement.
	//New individuals are created from cut to population->size.
	int	cut;

	//Used in run() to limit mutation.
	double probability;

	//Represents a lucky factor to choose the parents to Crossover.
	//Used in binaryTour().
	double lucky_factor;

	//Used in twoOpt() to return the best solution after mutation.
	double lowest_fitness;

	//Helper variable used in twoOpt().
	double new_fitness;

	//Represents nodes visited in a route. Used in init().
	vector<bool> visited_vertex;

	//Represents inserted nodes of route of individual f1.
	vector<bool> inserted_vertex_f1;

	//Represents inserted nodes of route of individual f2.
	vector<bool> inserted_vertex_f2;

	//Represents repeated nodes  of route of individual f1.
	vector<bool> repeated_vertex_f1;

	//Represents repeated nodes of route of individual f2.
	vector<bool> repeated_vertex_f2;

	//Is the space of solutions.
	//The individuals of population will undergo genetic operations to improve solutions.
	vector<Individuo> population;

	Genetic(Input *in, int alfa, int beta, int generations, double prob_mutation, int num_individuals, double lucky);
	~Genetic();

	void init();
	void create(int limit);
	void run();
	void sortPopulation();
	void binaryTour(Individuo &i1, Individuo &i2, Individuo &p1, Individuo &p2);
	void onePointCrossover(Individuo &p1, Individuo &p2, Individuo &f1, Individuo &f2);
	void swapNodeCrossover(Individuo &p1, Individuo &p2, Individuo &f1, Individuo &f2);
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
