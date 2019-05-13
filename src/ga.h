/*
 * ga.h
 *
 *  Created on: 10 de jul de 2018
 *      Author: adamr
 */

#ifndef GA_H_
#define GA_H_

#define DEBUG_SWAP

#include "individuo.h"
#include "statistic.h"
#include <algorithm>
#include <utility>
#include <unistd.h>

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
	int	gen_limit,
		era_limit;

	int init_type,
		selection_type,
		crossover_type,
		mutation_type,
		insertion_type;

	int	random_person;
	
	unsigned int random_vehicle1,
				 random_vehicle2,
				 random_node1,
				 random_node2,
				 begin,
				 end;

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
	double probability,
		   lucky_factor,
		   lucky_number;

	int mutation_range,
		lowest_fitness,
		new_fitness,
		old_fitness,
		current_edges_value,
		new_edges_value,
		number_vehicles,
		delta,
		best_i,
		best_k,
		best_delta,
		begin_index,
		end_index,
		fit_factor;
	
	//heap variables
	unsigned int l,
				 r,
				 smallest;
	
	Statistic stat;

	vector<bool> inserted,
				 visited;

	vector<int> mask,
				list,
				sort_index;


	vector<Individuo> population;

	struct Insertion{
		int vehicle;
		int index;
		int cost;
	};

	vector<Insertion> permutations;

	Genetic(int alfa, int beta, int generations, double prob_mutation,
			int num_individuals, double lucky_factor, int lucky_range, 
			int mutation_range, int initype, int stype, int ctype, int mtype, 
			int itype, int number_vehicles, int fit);

	//Initializes a new population according to the limit of individuals.
	//The function creates individuals from limit to population.size,
	//and replaces any solution that where in population before.
	void init();

	//Initializes init() with the limit parameter.
	void create(int limit);

	bool clientsServed();

	bool clientsChecked();

	void initialization(Individuo &s, int client);

	void computePossibilities(Individuo &s, int client);

	void cheapestInit(Individuo &s, int client);

	void randomCheapestInit(Individuo &s, int client);

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

	void routeCrossover(Individuo &p1, Individuo &p2, Individuo &f1, Individuo &f2);

	//TODO: Comment
	void mutation(Individuo &f);

	void mutationSwap(Individuo &f);

	void mutationScramble(Individuo &f);
	
	void mutationInversion(Individuo &f);

	int deltaEvaluation(Individuo &s, int vehicle, int i, int k);

	// Perform local search in solution efficiently
	// without make changes in the solution directly,
	// but first, assessing whether the exchange will really be improver.
	void twoOptFirstImprovement(Individuo &solution);

	void twoOptBestImprovement(Individuo &solution);

	//Helper method for twoOpt().
	//Only exchanges two route nodes.
	void swapNodes(Individuo &s, int vehicle, int i, int k);

	void swapDiffRouteNodes(Individuo &s, int vehicle1, int vehicle2, int i, int k);

	int calculatePartialRoute(Individuo &s, int vehicle, int i, int k);

	int calculatePartialDiffRoute(Individuo &s, int vehicle1, int vehicle2, int i, int k);

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


	bool capacityIsSatisfied(Individuo &s, int vehicle1, int vehicle2, int node1, int node2);

	void chooseNodes(Individuo &s);

	void removeVertexFromVehicle(Individuo &s);

	void addVertexForVehicle(Individuo &s);

	void swapVehicles(Individuo &s, int vehicle1, int vehicle2);

	bool capacityRemovingIsSatisfied(Individuo &s, int node1, int node2);

	void lineUpRouteAdded(Individuo &s, int vehicle, int node);

	void lineUpRouteRemoved(Individuo &s, int vehicle, int node);

	void lineUp(Individuo &s, int vehicle1, int vehicle2, int node1, int node2);

	void findIndexes(Individuo &s, int node, int vehicle);

	void pickRoute(Individuo &s, int index);

	void sortRoute(Individuo &s);

	void updateRoute(Individuo &s);

};

#endif /* GA_H_ */
