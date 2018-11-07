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

	int seed;
    //Represents a pointer to class Input, that contains size of graph and distance matrix.
	Input *in;

	//Used in twoOpt() to indicate improvement of an individual.
	bool improvement,
		 global_improvement;

	bool repeat;

	//Used in run(), and means the number of times that individuals mutate (twoOpt).
	int alfa_max;

	//Used in run(). Means the times of a change in the best individual of population.
	int	beta_max;

	//Represents the limit of generations of populations (stop criterion).
	int	limit;

	unsigned int selection_type,
				 crossover_type,
				 mutation_type,
				 insertion_type;

	int	random_person;

	unsigned int random_node1;

	unsigned int random_node2;

	int random_index;

	int lucky_range;

	//Used to crossomutationScramble(Individuo &f)ents.
	//A size of cut mutationScramble(Individuo &f)split of chromosomes occurs
	//at the point imutationScramble(Individuo &f)t size.
	int	cut_size;

	//Used in partiamutationScramble(Individuo &f)
	//New individualmutationScramble(Individuo &f) cut to population->size.
	int	cut;

	//TODO: Comment
	double probability;

	double lucky_factor;

	double lucky_number;

	int mutation_range;

	int lowest_fitness;

	int new_fitness;

	int old_fitness;

	int current_edges_value;

	int new_edges_value;

	//twoOptBestImprovement variables
	int delta,
		best_i,
		best_k,
		best_delta;
	
	//heap variables
	unsigned int l,
				 r,
				 smallest;

	vector<bool> inserted_vertex_f1;

	vector<bool> inserted_vertex_f2;

	vector<bool> repeated_vertex_f1;

	vector<bool> repeated_vertex_f2;

	vector<int> atual_route;

	vector<Individuo> population;

	Genetic(Input *in, int alfa, int beta, int generations, double prob_mutation,
			int num_individuals, double lucky_factor, int lucky_range, 
			int mutation_range,int stype, int ctype, int mtype, int itype);

	//Initializes a new population according to the limit of individuals.
	//The function creates individuals from limit to population.size,
	//and replaces any solution that where in population before.
	void init();

	void init2();
	
	//Initializes init() with the limit parameter.
	void create(int limit);

	void create2(int limit);

	int generateRandom();

	//This function is the Genetic Algorithm.
	//It performs several operations on individuals present in the population,
	//such as Initiation, Crossover, Selection, Mutation and Acceptance.
	//The function is iterative, and the stop criterion is generation limit.
	//Variables such as alpha_max and beta_max are also present to finalize a generation of individuals.
	void run();

	//TODO: Comment
	void selection(Individuo &i1, Individuo &i2, Individuo &p, int previous_fitness);

	//Selects parents p1 and p2 for Crossover.
	//The function randomly chooses two pairs of individuals,
	//and each pair competes with each other for Crossover selection.
	void binaryTour(Individuo &i1, Individuo &i2, Individuo &p, int previous_fitness);

	void rankSelection(Individuo &i1, Individuo &i2, Individuo &p, int previous_fitness);

	void randomSelection(Individuo &p);

	//TODO: Comment
	void crossover(Individuo &p1, Individuo &p2, Individuo &f1, Individuo &f2);
	//With value of the cut_size variable,
	//the method switches part of the routes from p1 to p2,
	//and these generate 2 new children f1 and f2.
	void onePointCrossover(Individuo &p1, Individuo &p2, Individuo &f1, Individuo &f2);

	void uniformCrossover(Individuo &p1, Individuo &p2, Individuo &f1, Individuo &f2);

	void swapNodeCrossover(Individuo &p1, Individuo &p2, Individuo &f1, Individuo &f2);

	//TODO: Comment
	void mutation(Individuo &f);

	void mutationSwap(Individuo &f);

	void mutationScramble(Individuo &f);
	
	void mutationInversion(Individuo &f);

	int deltaEvaluation(Individuo &s, int i, int k);

	// Perform local search in solution efficiently
	// without make changes in the solution directly,
	// but first, assessing whether the exchange will really be improver.
	void twoOptFirstImprovement(Individuo &solution);

	void twoOptBestImprovement(Individuo &solution);

	//Helper method for twoOpt().
	//Only exchanges two route nodes.
	void swapNodes(Individuo &s, int i, int k);


	//TODO: Comment
	void insertion(Individuo &s, Individuo &best, int &beta);

	//Randomly chooses an individual
	//of the population and compares with the child generated.
	//If this has the fitness smaller than the chosen individual
	//the child enters in population and the other is deleted.
	void randomInsertion(Individuo &s);

	void elitistInsertion(Individuo &s);

	//This method is used to recreate half of the
	//the next generation (elitist method).
	void partialReplacement();

	bool searchFitness(Individuo &s);

	void removeRepeatedNodes(Individuo &f1, Individuo &f2);

	void insertNodes(Individuo &f1, Individuo &f2);

	void showResult();

	void printPopulation();

	void sortPopulation();

	unsigned int left(unsigned int i);

	unsigned int right(unsigned int i);

	unsigned int father(unsigned int i);

	void parent(unsigned int i);

	void buildMinHeap();

	void minHeapify(unsigned int i);

	void heapFix(unsigned int i);

};

#endif /* GA_H_ */
