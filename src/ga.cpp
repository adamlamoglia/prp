/*
 * ga.cpp
 *
 *  Created on: 10 de jul de 2018
 *      Author: adamr
 */

#include "ga.h"

int aux;

Genetic::Genetic(int alfa, int beta, int generations, double prob_mutation,
				 int size, double lucky_factor, int lucky_range, int mutation_range,
				 int stype, int ctype, int mtype, int itype, int number_vehicles)
{

	this->in = Input::getInstance();

	alfa_max = alfa;
	beta_max = beta;
	limit = generations;
	probability = prob_mutation;

	this->crossover_type = ctype;

	this->lucky_factor = lucky_factor;
	this->lucky_range = lucky_range;
	this->mutation_range = mutation_range;
	this->number_vehicles = number_vehicles - 1;

	inserted.resize(in->num_vertices, false);

	cut_size = in->num_vertices / 2;

	cut = size / 2;

	population.resize(size, Individuo());
}

bool lowerFitness(Individuo a, Individuo b)
{
	return a.getFitness() < b.getFitness();
}

unsigned int Genetic::left(unsigned int i)
{

	return 2 * i + 1;
}

unsigned int Genetic::right(unsigned int i)
{

	return 2 * i + 2;
}

void Genetic::sortPopulation()
{

	sort(population.begin(), population.end(), lowerFitness);
}

unsigned int Genetic::father(unsigned int i)
{
	if (i % 2 == 0)
		return i / 2 - 1;
	return i / 2;
}

void Genetic::heapFix(unsigned int i)
{
	int k = i;
	while (k > 0 && population[father(k)].getFitness() > population[k].getFitness())
	{
		swap(population[k], population[father(k)]);
		k = father(k);
	}
}

void Genetic::minHeapify(unsigned int i)
{

	l = left(i);
	r = right(i);

	if (l < population.size() && population[l].getFitness() < population[i].getFitness())
		smallest = l;

	else
		smallest = i;

	if (r < population.size() && population[r].getFitness() < population[smallest].getFitness())
		smallest = r;

	if (smallest != i)
	{

		swap(population[i], population[smallest]);
		minHeapify(smallest);
	}
}

void Genetic::buildMinHeap()
{

	for (int i = floor(population.size() / 2); i >= 0; i--)
		minHeapify(i);
}

void Genetic::create(int limit)
{

	for (unsigned int i = limit; i < population.size(); i++)
	{

		int random_client;
		int num_inserted = 0;

		for (unsigned int j = 0; j < inserted.size(); j++)
			inserted[j] = false;

		for (int vehicle = 0; vehicle < in->num_vertices; vehicle++)
		{
			int cumulate_capacity = 0;
			int atual_index = 0;

			while (cumulate_capacity < in->capacity && num_inserted < in->num_vertices - 1)
			{

				random_client = rand() % in->num_vertices;

				while (inserted[random_client] || random_client == 0)
					random_client = rand() % in->num_vertices;

				if (in->demand[random_client] + cumulate_capacity <= in->capacity)
				{

					population[i].setRoute(vehicle, random_client);
					cumulate_capacity += in->demand[random_client];
					inserted[random_client] = true;
					atual_index++;
					num_inserted++;
				}
				else
					break;
			}

			population[i].fleet[vehicle].setCapacity(in->capacity - cumulate_capacity);
		}

		population[i].calculateFitness();
	}

	buildMinHeap();
}

void Genetic::init()
{

	create(0);
}

void Genetic::partialReplacement()
{

	create(cut);
}

void Genetic::selection(Individuo &i1, Individuo &i2, Individuo &p, int previous_fitness)
{

	switch (selection_type)
	{

	case 1:
		binaryTour(i1, i2, p, previous_fitness);

	case 2:
		randomSelection(p);

	case 3:
		rankSelection(i1, i2, p, previous_fitness);

	default:
		binaryTour(i1, i2, p, previous_fitness);
	}
}

void Genetic::binaryTour(Individuo &i1, Individuo &i2, Individuo &p, int previous_fitness)
{

	lucky_number = rand() % lucky_range;

	do
	{

		random_person = rand() % population.size();
		i1 = population[random_person];
	} while (i1.getFitness() == previous_fitness);

	do
	{

		random_person = rand() % population.size();
		i2 = population[random_person];

	} while (i1.getFitness() == i2.getFitness() || i2.getFitness() == previous_fitness);

	if (i1.getFitness() < i2.getFitness() && lucky_factor > lucky_number)
		p = i1;

	else
		p = i2;
}

void Genetic::rankSelection(Individuo &i1, Individuo &i2, Individuo &p, int previous_fitness)
{
}

void Genetic::randomSelection(Individuo &p)
{

	p = population[rand() % population.size()];
}

void Genetic::crossover(Individuo &p1, Individuo &p2, Individuo &f1, Individuo &f2)
{

	switch (crossover_type)
	{

	case 1:
		swapNodeCrossover(p1, p2, f1, f2);

	case 2:
		uniformCrossover(p1, p2, f1, f2);

	case 3:
		onePointCrossover(p1, p2, f1, f2);

	case 4:
		routeCrossover(p1, p2, f1, f2);

	default:
		swapNodeCrossover(p1, p2, f1, f2);
	}
}

void Genetic::swapNodeCrossover(Individuo &p1, Individuo &p2, Individuo &f1, Individuo &f2)
{

	f1 = p1;
	f2 = p2;

	chooseNodes(f1);

	if (random_node1 < random_node2)
		swapNodes(f1, random_vehicle, random_node1, random_node2);

	else
		swapNodes(f1, random_vehicle, random_node2, random_node1);

	chooseNodes(f2);

	if (random_node1 < random_node2)
		swapNodes(f2, random_vehicle, random_node1, random_node2);

	else
		swapNodes(f2, random_vehicle, random_node2, random_node1);
}

void Genetic::chooseNodes(Individuo &s)
{

	do
	{
		random_vehicle = rand() % in->num_vertices;
	} while (s.route[random_vehicle].size() <= 1);

	//cout << "1" << endl;
	
	do
	{
		random_node1 = rand() % s.route[random_vehicle].size();

	} while (s.route[random_vehicle][random_node1] == 0);

	//cout << "2" << endl;

	do
	{
		random_node2 = rand() % s.route[random_vehicle].size();

	} while (random_node1 == random_node2);

	//cout << "3" << endl;

}

void Genetic::uniformCrossover(Individuo &p1, Individuo &p2, Individuo &f1, Individuo &f2)
{
}

void Genetic::onePointCrossover(Individuo &p1, Individuo &p2, Individuo &f1, Individuo &f2)
{
}

void Genetic::routeCrossover(Individuo &p1, Individuo &p2, Individuo &f1, Individuo &f2)
{
}

void Genetic::mutation(Individuo &f)
{

	switch (mutation_type)
	{

	case 1:
		mutationSwap(f);

	case 2:
		mutationScramble(f);

	case 3:
		mutationInversion(f);

	default:
		mutationSwap(f);
	}
}

void Genetic::mutationSwap(Individuo &f)
{

	chooseNodes(f);

	if (random_node1 < random_node2)
		swapNodes(f, random_vehicle, random_node1, random_node2);

	else
		swapNodes(f, random_vehicle, random_node2, random_node1);
}

void Genetic::mutationScramble(Individuo &f)
{
}

void Genetic::mutationInversion(Individuo &f)
{
}

void Genetic::insertion(Individuo &s, Individuo &best, int &beta)
{

	if (!searchFitness(s))
	{

		switch (insertion_type)
		{

		case 1:
			elitistInsertion(s);

		case 2:
			randomInsertion(s);

		default:
			elitistInsertion(s);
		}

		if (s.getFitness() < best.getFitness())
		{

			best = s;

			beta++;
		}
	}
}

void Genetic::randomInsertion(Individuo &s)
{

	random_person = rand() % population.size() / 2 + population.size() / 2;

	if (population[random_person].getFitness() > s.getFitness())
	{

		population[random_person] = s;

		heapFix(random_person);
	}
}

void Genetic::elitistInsertion(Individuo &s)
{

	if (population[population.size() - 1].getFitness() > s.getFitness())
	{

		population[population.size() - 1] = s;

		heapFix(population.size() - 1);
	}
}

bool Genetic::searchFitness(Individuo &s)
{

	for (unsigned int i = 0; i < population.size(); i++)
		if (s.getFitness() == population[i].getFitness())
			return true;

	return false;
}

void Genetic::twoOptBestImprovement(Individuo &solution)
{

		global_improvement = true;

		best_i = best_k = -1;
		delta = 1;

	for (unsigned int vehicle = 0; vehicle < solution.route.size(); vehicle++)
	{

		//cout << solution.route[vehicle].size() << endl;

		if(solution.route[vehicle].size() <= 1)
			continue;

		//cout << "passou porra" << endl;

		while (global_improvement)
		{
			global_improvement = false;

			//cout << solution.getFitness() << endl;

			lowest_fitness = solution.getFitness();

			for (unsigned int i = 0; i < solution.route[vehicle].size() - 1; i++)
			{

				best_delta = 0;

				improvement = false;

				for (unsigned int k = i + 1; k < solution.route[vehicle].size(); k++)
				{

						//cout << "achei" << endl;
					
						delta = deltaEvaluation(solution, vehicle, i, k);

						if (delta < 0 && delta < best_delta)
						{

							best_delta = delta;
							best_i = i;
							best_k = k;
							improvement = true;
						}

						//cout << "q1" << endl;
				
				}

				if (improvement)
				{

					swapNodes(solution, vehicle, best_i, best_k);

					if (solution.getFitness() < lowest_fitness)
					{
						global_improvement = true;
						//lowest_fitness = solution.getFitness();
					}
				}

				//cout << "q2" << endl;
			}

			//cout << "q3" << endl;
		}

		//cout << vehicle << endl;
	}
}

int Genetic::deltaEvaluation(Individuo &s, int vehicle, int i, int k)
{

	//cout << s.route[vehicle].size() << endl;
	
	//cout << i << " " << k << endl;

	current_edges_value = calculatePartialRoute(s, vehicle, i, k);


	swap(s.route[vehicle][i], s.route[vehicle][k]);

	new_edges_value = calculatePartialRoute(s, vehicle, i, k);

	//cout << "oxx" << endl;

	swap(s.route[vehicle][i], s.route[vehicle][k]);

	return new_edges_value - current_edges_value;
}

int Genetic::calculatePartialRoute(Individuo &s, int vehicle, int i, int k)
{

	if (i == k - 1)
	{

		if (i == 0)
		{

			if(k == s.route[vehicle].size() - 1)
						return in->distance_matrix[0][s.route[vehicle][i]] + 
						in->distance_matrix[s.route[vehicle][i]][s.route[vehicle][k]] + 
						in->distance_matrix[s.route[vehicle][k]][0];


			
			return in->distance_matrix[0][s.route[vehicle][i]] + 
			in->distance_matrix[s.route[vehicle][i]][s.route[vehicle][k]] + 
			in->distance_matrix[s.route[vehicle][k]][s.route[vehicle][k + 1]];
		}

		if(k == s.route[vehicle].size() - 1)
			return in->distance_matrix[0][s.route[vehicle][i]] + 
			in->distance_matrix[s.route[vehicle][i]][s.route[vehicle][k]] + 
			in->distance_matrix[s.route[vehicle][k]][0];


		return in->distance_matrix[s.route[vehicle][i - 1]][s.route[vehicle][i]] + 
		in->distance_matrix[s.route[vehicle][i]][s.route[vehicle][k]] + 
		in->distance_matrix[s.route[vehicle][k]][s.route[vehicle][k + 1]];
	}

	if (i == 0)
	{	
		//cout << "entrou" << endl;
		
		//cout << s.route[vehicle].size() << endl;
		//cout << in->distance_matrix[0][s.route[vehicle][i]] << endl;
		//cout << in->distance_matrix[s.route[vehicle][i]][s.route[vehicle][i + 1]] << endl;
		//cout << in->distance_matrix[s.route[vehicle][k - 1]][s.route[vehicle][k]] << endl;
		//cout << in->distance_matrix[s.route[vehicle][k]][s.route[vehicle][k + 1]] << endl;

		if(k == s.route[vehicle].size() - 1)
			return in->distance_matrix[0][s.route[vehicle][i]] + 
			in->distance_matrix[s.route[vehicle][i]][s.route[vehicle][i + 1]] + 
			in->distance_matrix[s.route[vehicle][k - 1]][s.route[vehicle][k]] + 
			in->distance_matrix[s.route[vehicle][k]][0];

		return in->distance_matrix[0][s.route[vehicle][i]] + 
		in->distance_matrix[s.route[vehicle][i]][s.route[vehicle][i + 1]] + 
		in->distance_matrix[s.route[vehicle][k - 1]][s.route[vehicle][k]] + 
		in->distance_matrix[s.route[vehicle][k]][s.route[vehicle][k + 1]];
	}

	if(k == s.route[vehicle].size() - 1)
		return in->distance_matrix[s.route[vehicle][i - 1]][s.route[vehicle][i]] + 
	in->distance_matrix[s.route[vehicle][i]][s.route[vehicle][i + 1]] + 
	in->distance_matrix[s.route[vehicle][k - 1]][s.route[vehicle][k]] + 
	in->distance_matrix[s.route[vehicle][k]][0];

	return in->distance_matrix[s.route[vehicle][i - 1]][s.route[vehicle][i]] + 
	in->distance_matrix[s.route[vehicle][i]][s.route[vehicle][i + 1]] + 
	in->distance_matrix[s.route[vehicle][k - 1]][s.route[vehicle][k]] + 
	in->distance_matrix[s.route[vehicle][k]][s.route[vehicle][k + 1]];
}

void Genetic::swapNodes(Individuo &s, int vehicle, int i, int k)
{

	/*if(vehicle1 != vehicle2){


		if (vehicle1 != vehicle2)
		{

			s.fleet[vehicle1].setCapacity(s.fleet[vehicle1].getCapacity() + in->demand[ s.route[vehicle1][i] ] - in->demand[ s.route[vehicle2][k] ] );
			s.fleet[vehicle2].setCapacity(s.fleet[vehicle2].getCapacity() + in->demand[ s.route[vehicle2][k] ] - in->demand[ s.route[vehicle1][i] ] );
		}
	}*/

	current_edges_value = calculatePartialRoute(s, vehicle, i, k);

	swap(s.route[vehicle][i], s.route[vehicle][k]);

	new_edges_value = calculatePartialRoute(s, vehicle, i, k);

	s.setFitness(s.getFitness() - current_edges_value + new_edges_value);

	#ifdef DEBUG_SWAP
		// Valor do fitness apos a execucao de swapnodes
		int old_fitness = s.getFitness();
		// Calcula o fitness do zero
		s.calculateFitness();
		// Pega o novo valor do fitness
		int new_fitness = s.getFitness();
		// Verifica se existe divergencia
		if(old_fitness != new_fitness){
			//cout << "fitness apos swap: " << old_fitness << endl;
			//cout << "fitness calculado: " << new_fitness << endl;
		}
			
		// Continua com o valor computado por esta função
		s.setFitness(new_fitness);
		#endif
}

void Genetic::showResult()
{

	population[0].printRoute();
	population[0].printFitness();
}

void Genetic::printPopulation()
{

	for (unsigned int i = 0; i < population.size(); i++)
	{
		population[i].printRoute();
		population[i].printFitness();
	}
}

void Genetic::run()
{

	int generations = 0,
		alfa = 0,
		beta = 0;

	double mutation_number;

	Individuo i1,
		i2;

	// Parents
	Individuo p1,
		p2;

	// Sons of parents p1 and p2
	Individuo f1,
		f2;

	// Best solution
	Individuo best;

	init();

	while (generations <= limit)
	{

		alfa = beta = 0;

		while (alfa < alfa_max and beta < beta_max)
		{

			best = population[0];

			selection(i1, i2, p1, 0);
			selection(i1, i2, p2, p1.getFitness());

			crossover(p1, p2, f1, f2);

			//cout << "pass1" << endl;

			mutation_number = rand() % mutation_range;

			if (mutation_number < probability)
			{

				mutation(f1);
				mutation(f2);

				alfa++;
			}
			//cout << "pass2" << endl;

			twoOptBestImprovement(f1);
			twoOptBestImprovement(f2);

			//cout << "pass3" << endl;

			insertion(f1, best, beta);
			insertion(f2, best, beta);
		}

		generations++;

		cout << "gen: " << generations << " - best fitness: " << best.getFitness() << endl;

		partialReplacement();
	}

	population[0] = best;
}
