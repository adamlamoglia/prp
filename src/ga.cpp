/*
 * ga.cpp
 *
 *  Created on: 10 de jul de 2018
 *      Author: adamr
 */

#include "ga.h"

int aux;

Genetic::Genetic(Input *in, int alfa, int beta, int generations, double prob_mutation,
				 int size, double lucky_factor, int lucky_range, int mutation_range,
				 int stype, int ctype, int mtype, int itype, int number_vehicles)
{

	this->in = in;

	alfa_max = alfa;
	beta_max = beta;
	limit = generations;
	probability = prob_mutation;

	this->crossover_type = ctype;

	this->lucky_factor = lucky_factor;
	this->lucky_range = lucky_range;
	this->mutation_range = mutation_range;
	this->number_vehicles = number_vehicles - 1;
	inserted.resize(in->num_vertices + 1, false);
	inserted[0] = inserted[inserted.size() - 1] = true;

	cut_size = in->num_vertices / 2;

	cut = size / 2;

	population.resize(size, Individuo(in));

	repeated_vertex_f1.resize(in->num_vertices, false);
	repeated_vertex_f2.resize(in->num_vertices, false);
	inserted_vertex_f1.resize(in->num_vertices, false);
	inserted_vertex_f2.resize(in->num_vertices, false);
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

		int atual_index = 1;
		int atual_vehicle = 1;
		int atual_vehicle_index = 1;

		int cumulate_capacity = 0;

		int random_client;

		for (unsigned int j = 1; j < inserted.size() - 1; j++)
			inserted[j] = false;

		while (atual_index < in->num_vertices)
		{

			random_client = rand() % in->num_vertices;

			while (inserted[random_client])
				random_client = rand() % in->num_vertices;

			if (in->demand[random_client] + cumulate_capacity <= in->capacity)
			{

				population[i].setRoute(atual_index, random_client);
				population[i].vehicle_associated[atual_vehicle_index] = atual_vehicle;

				cumulate_capacity += in->demand[random_client];
				inserted[random_client] = true;

				atual_index++;
				atual_vehicle_index++;
			}
			if (in->demand[random_client] + cumulate_capacity > in->capacity || atual_index == in->num_vertices)
			{
				population[i].setStopIndex(atual_index - 1);
				population[i].atual_capacity[atual_vehicle] = in->capacity - cumulate_capacity;

				cumulate_capacity = 0;
				atual_vehicle++;
			}
		}

		population[i].setFitness();
		population[i].setNumVehicles(atual_vehicle - 1);
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

	case 4:
		removeVertexFromVehicle(f);

	default:
		mutationSwap(f);
	}
					
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

void Genetic::onePointCrossover(Individuo &p1, Individuo &p2, Individuo &f1, Individuo &f2)
{

	f1 = p1;
	f2 = p2;

	for (unsigned int i = cut_size; i < in->num_vertices; i++)
	{
		inserted_vertex_f1[f1.route[i]] = true;
		inserted_vertex_f2[f2.route[i]] = true;
	}

	for (int i = 1; i < cut_size; i++)
	{

		if (inserted_vertex_f1[p2.route[i]])
			repeated_vertex_f1[p2.route[i]] = true;
		else
			inserted_vertex_f1[p2.route[i]] = true;

		f1.route[i] = p2.route[i];
	}

	for (int i = 1; i < cut_size; i++)
	{

		if (inserted_vertex_f2[p1.route[i]])
			repeated_vertex_f2[p1.route[i]] = true;
		else
			inserted_vertex_f2[p1.route[i]] = true;

		f2.route[i] = p1.route[i];
	}

	removeRepeatedNodes(f1, f2);
	insertNodes(f1, f2);

	f1.setFitness();
	f2.setFitness();

	for (unsigned int i = 1; i < in->num_vertices; i++)
	{
		inserted_vertex_f1[i] = false;
		inserted_vertex_f2[i] = false;
		repeated_vertex_f1[i] = false;
		repeated_vertex_f2[i] = false;
	}
}

void Genetic::removeRepeatedNodes(Individuo &f1, Individuo &f2)
{

	for (unsigned int i = 1; i < in->num_vertices; i++)
	{

		int a = f1.route[i];

		if (repeated_vertex_f1[a])
		{

			f1.route[i] = -1;
			repeated_vertex_f1[a] = false;
		}
	}

	for (unsigned int i = 1; i < in->num_vertices; i++)
	{

		int a = f2.route[i];

		if (repeated_vertex_f2[a])
		{

			f2.route[i] = -1;
			repeated_vertex_f2[a] = false;
		}
	}
}

void Genetic::insertNodes(Individuo &f1, Individuo &f2)
{

	for (unsigned int i = 1; i < in->num_vertices; i++)
	{

		if (f1.route[i] == -1)
		{

			for (unsigned int j = 1; j < in->num_vertices; j++)
			{

				if (!inserted_vertex_f1[j])
				{

					f1.route[i] = j;
					inserted_vertex_f1[j] = true;
					break;
				}
			}
		}
	}

	for (unsigned int i = 1; i < in->num_vertices; i++)
	{

		if (f2.route[i] == -1)
		{

			for (unsigned int j = 1; j < in->num_vertices; j++)
			{

				if (!inserted_vertex_f2[j])
				{

					f2.route[i] = j;

					inserted_vertex_f2[j] = true;

					break;
				}
			}
		}
	}
}

void Genetic::uniformCrossover(Individuo &p1, Individuo &p2, Individuo &f1, Individuo &f2)
{

	f1 = p1;
	f2 = p2;

	for (unsigned int i = 1; i < in->num_vertices - 1; i++)
	{

		aux = f1.route[i];

		swapNodes(f1, f1.route[i], f2.route[i]);
		swapNodes(f2, aux, f2.route[i]);
	}
}

void Genetic::chooseNodes(Individuo &s)
{
	
	do
	{
		random_node1 = rand() % in->num_vertices;
		do
		{
			random_node1 = rand() % in->num_vertices;

		} while (random_node1 == 0 || random_node1 == in->num_vertices - 1);

		random_node2 = rand() % in->num_vertices;
		do
		{
			random_node2 = rand() % in->num_vertices;

		} while (random_node2 == 0 || random_node2 == in->num_vertices - 1 || random_node1 == random_node2);
	} while (!capacityIsSatisfied(s, random_node1, random_node2));

	
}

bool Genetic::capacityIsSatisfied(Individuo &s, int node1, int node2)
{

	int vehicle1, vehicle2, capacity1, capacity2;

	vehicle1 = s.vehicle_associated[node1];
	vehicle2 = s.vehicle_associated[node2];

	if (vehicle1 == vehicle2)
		return true;

	capacity1 = s.atual_capacity[vehicle1];
	capacity2 = s.atual_capacity[vehicle2];

	if (capacity1 + in->demand[s.route[node1]] - in->demand[s.route[node2]] >= 0 &&
		capacity2 + in->demand[s.route[node2]] - in->demand[s.route[node1]] >= 0)
	{

		return true;
	}

	return false;
}

bool Genetic::capacityRemovingIsSatisfied(Individuo &s, int node1, int node2){

	int vehicle1, vehicle2, capacity1, capacity2;

	vehicle1 = s.vehicle_associated[node1];
	vehicle2 = s.vehicle_associated[node2];

	capacity1 = s.atual_capacity[vehicle1];
	capacity2 = s.atual_capacity[vehicle2];

	if (capacity2 - in->demand[s.route[node1]] >= 0)
	{

		return true;
	}

	return false;


}

void Genetic::swapNodeCrossover(Individuo &p1, Individuo &p2, Individuo &f1, Individuo &f2)
{

	f1 = p1;
	f2 = p2;

	chooseNodes(f1);

	if (random_node1 < random_node2)
		swapNodes(f1, random_node1, random_node2);

	else
		swapNodes(f1, random_node2, random_node1);

	chooseNodes(f2);

	if (random_node1 < random_node2)
		swapNodes(f2, random_node1, random_node2);

	else
		swapNodes(f2, random_node2, random_node1);
}

void Genetic::mutationSwap(Individuo &f)
{

	chooseNodes(f);

	if (random_node1 < random_node2)
		swapNodes(f, random_node1, random_node2);

	else
		swapNodes(f, random_node2, random_node1);
}

void Genetic::routeCrossover(Individuo &p1, Individuo &p2, Individuo &f1, Individuo &f2)
{

	mask.resize(p1.getNumVehicles(), 0);

	for(int i = 0; i < mask.size(); i++)
		mask[i] = rand() % 2;

	p1.printRoute();
	p1.printVehicles();
	
	for(int i = 0; i < mask.size(); i++)
		cout << mask[i] << " ";
	
	cout << endl;
	
	for(int i = 0; i < mask.size(); i++){

		//pick route to change
		if(mask[i] == 0){

			pickRoute(p1, i + 1);

			for(int j = 0; j < list.size(); j++)
				cout << list[j] << " ";

			cout << endl;

			sortRoute(p2);

			p2.printRoute();

			for(int j = 0; j < list.size(); j++)
				cout << list[j] << " ";

			cout << endl;

			exit(1);
		}
	}

}

void Genetic::pickRoute(Individuo &s, int index){

	int sizeRoute = 0, list_index = 0;

	for(int i = 0; i < s.route.size(); i++){

		if(s.vehicle_associated[i] == index)
			sizeRoute++;
	}

	
	list.resize(sizeRoute);
	sort_index.resize(sizeRoute);

	for(int i = 0; i < s.route.size(); i++){

		if(s.vehicle_associated[i] == index)
				list[list_index++] = s.route[i];
	}	
	
}

void Genetic::sortRoute(Individuo &s){
	
	for(int i = 0; i < list.size(); i++){

		for(int j = 0; j < s.route.size(); j++){

			if(list[i] == s.route[j]){

				sort_index[i] = j;
				break;
			}
		}
			
	}

	sort(sort_index.begin(), sort_index.end());

	for(int i = 0; i < list.size(); i++){

		list[i] = s.route[sort_index[i]];
	}
}

void Genetic::mutationScramble(Individuo &f)
{

	Individuo antigo(in);

	antigo = f;

	do
	{
		random_node1 = rand() % in->num_vertices;

	} while (random_node1 > in->num_vertices - 4);

	//TODO: Determine number of nodes to be scrambled
	random_shuffle(f.route.begin() + random_node1, f.route.begin() + random_node1 + 4);

	//TODO: Do the rest of method
}

void Genetic::mutationInversion(Individuo &f)
{

	do
	{

		random_node1 = rand() % in->num_vertices;

	} while (random_node1 > in->num_vertices - 4);

	//TODO: Determine number of nodes to be inversed
	reverse(f.route.begin() + random_node1, f.route.begin() + random_node1 + 4);

	int end = random_node1 + 3;

	for (unsigned int i = random_node1; i < random_node1 + 4; i++)
	{

		f.fitness_set(f.fitness_get() + deltaEvaluation(f, i, end));

		end--;
	}
}

void Genetic::swapVehicles(Individuo &s, int vehicle1, int vehicle2)
{
}

void Genetic::removeVertexFromVehicle(Individuo &s)
{

	int vehicle1, vehicle2, capacity1, capacity2;

	do
	{
		do{
			random_node1 = rand() % in->num_vertices;

		}while(random_node1 == 0);

		do
		{
			random_node2 = rand() % in->num_vertices;
		} while (s.vehicle_associated[random_node1] == s.vehicle_associated[random_node2] || random_node2 == 0);

		
		
	}while(!capacityRemovingIsSatisfied(s, random_node1, random_node2));

	vehicle1 = s.vehicle_associated[random_node1];
	vehicle2 = s.vehicle_associated[random_node2];
	//lineUpRouteRemoved(s, vehicle1, random_node1);
	//lineUpRouteAdded(s, vehicle2, random_node1);
	
	//lineUp(s, vehicle1, vehicle2, random_node1, random_node2);



	capacity1 = s.atual_capacity[vehicle1];
	capacity2 = s.atual_capacity[vehicle2];

	s.vehicle_associated[random_node1] = s.vehicle_associated[random_node2];

	s.atual_capacity[vehicle2] = s.atual_capacity[vehicle2] - in->demand[s.route[random_node1]];
	s.atual_capacity[vehicle1] = s.atual_capacity[vehicle1] + in->demand[s.route[random_node1]];

	
	

}

void Genetic::lineUp(Individuo &s, int vehicle1, int vehicle2, int node1, int node2){

	int previous_index_node1, next_index_node1, previous_index_node2, next_index_node2;

	int route_node1, route_node2;
	
	for(int i = node1 - 1; i >= 0; i--){

		if(s.vehicle_associated[i] == vehicle1 || i == 0){
			previous_index_node1 = i;
			break;
		}
	}

	for(int i = node1 + 1; i < s.route.size(); i++){

		if(s.vehicle_associated[i] == vehicle1){
			next_index_node1 = i;
			break;
		}

		else if(i == s.route.size() - 1)
			next_index_node1 = 0;
	}

	for(int i = node1 - 1; i >= 0; i--){

		if(s.vehicle_associated[i] == vehicle2 || i == 0){
			previous_index_node2 = i;
			break;
		}
	}

	for(int i = node1 + 1; i < s.route.size(); i++){

		if(s.vehicle_associated[i] == vehicle2){
			next_index_node2 = i;
			break;
		}

		else if(i == s.route.size() - 1)
			next_index_node2 = 0;
	}
	
	//route with single client
	if(previous_index_node1 == 0 && next_index_node1 == 0){

		//cout << "entrou1" << endl;

		s.fitness_set(s.fitness_get() - in->distance_matrix[0][s.route[node1]] 
									  - in->distance_matrix[s.route[node1]][0]);

		s.stop_index[node1] = 0;
	}

	else{

		//cout << "entrou2" << endl;


		s.fitness_set(s.fitness_get() - in->distance_matrix[s.route[previous_index_node1]][s.route[node1]]
									  - in->distance_matrix[s.route[node1]][s.route[next_index_node1]]
									  + in->distance_matrix[s.route[previous_index_node1]][s.route[next_index_node1]]);

		if(next_index_node1 == 0){
			s.stop_index[node1] = 0;
			s.setStopIndex(previous_index_node1);
		}
	}


	if(previous_index_node2 == 0 && next_index_node2 == 0){

		//cout << "entrou3" << endl;

				s.fitness_set(s.fitness_get() + in->distance_matrix[0][s.route[node1]] 
									  		  + in->distance_matrix[s.route[node1]][0]);
				
				//s.setStopIndex(node1);
	}

	else{

		//cout << "entrou4" << endl;
		s.fitness_set(s.fitness_get() + in->distance_matrix[s.route[previous_index_node2]][s.route[node1]]
									  + in->distance_matrix[s.route[node1]][s.route[next_index_node2]]
									  - in->distance_matrix[s.route[previous_index_node2]][s.route[next_index_node2]]);

		if(next_index_node2 == 0){
			s.stop_index[previous_index_node2] = 0;
			s.setStopIndex(node1);
		}
	}

}

void Genetic::lineUpRouteRemoved(Individuo &s, int vehicle, int node){
	int previous_index, next_index;

	//line up route of vehicle with removed vertex

	for(int i = node - 1; i >= 0; i--){

		if(s.vehicle_associated[i] == vehicle || i == 0){
			previous_index = i;
			break;
		}
	}

	for(int i = node + 1; i < s.route.size(); i++){

		if(s.vehicle_associated[i] == vehicle || i == s.route.size() - 1){
			next_index = i;
			break;
		}
	}

	//there's no more route
	if(previous_index == 0 && s.route[next_index] == 0){

		s.fitness_set(s.fitness_get() - in->distance_matrix[0][s.route[node]] 
									  - in->distance_matrix[s.route[node]][0]);

		s.stop_index[node] = 0;
	}

	else if(s.route[previous_index] == 0){

		s.fitness_set(s.fitness_get() - in->distance_matrix[0][s.route[node]]
									  - in->distance_matrix[s.route[node]][s.route[next_index]] 
									  + in->distance_matrix[0][s.route[next_index]]);
		
	}

	else if(s.route[next_index] == 0){

		s.fitness_set(s.fitness_get() - in->distance_matrix[s.route[previous_index]][s.route[node]]
									  - in->distance_matrix[s.route[node]][0] 
									  + in->distance_matrix[s.route[previous_index]][0]);

		
		s.stop_index[node] = 0;
		s.setStopIndex(previous_index);
	}

	else{
		s.fitness_set(s.fitness_get() - in->distance_matrix[s.route[previous_index]][s.route[node]] 
									  - in->distance_matrix[s.route[node]][s.route[next_index]]
									  + in->distance_matrix[s.route[previous_index]][s.route[next_index]]);
	}


}

void Genetic::lineUpRouteAdded(Individuo &s, int vehicle, int node){
	int previous_index, next_index;

	//find 0 or part of the same route 

	for(int i = node - 1; i >= 0; i--){

		if(s.vehicle_associated[i] == vehicle || s.vehicle_associated[i] == 0){
			previous_index = i;
			break;
		}
	}

	for(int i = node + 1; i < s.route.size(); i++){

		if(s.vehicle_associated[i] == vehicle || s.vehicle_associated[i] == 0){
			next_index = i;
			break;
		}
	}

	//line up route of vehicle with add vertex

	if(s.route[previous_index] == 0){

		s.fitness_set(s.fitness_get() - in->distance_matrix[0][s.route[next_index]] 
					+ in->distance_matrix[0][s.route[node]]
					+ in->distance_matrix[s.route[node]][s.route[next_index]]);

	}

	else if(s.route[next_index] == 0){

		s.fitness_set(s.fitness_get() - in->distance_matrix[s.route[previous_index]][0] 
					+ in->distance_matrix[s.route[previous_index]][s.route[node]]
					+ in->distance_matrix[s.route[node]][0]);
		
		s.setStopIndex(node);
		s.stop_index[previous_index] = 0;
	}

	else{

		s.fitness_set(s.fitness_get() - in->distance_matrix[s.route[previous_index]][s.route[next_index]] 
					+ in->distance_matrix[s.route[previous_index]][s.route[node]]
					+ in->distance_matrix[s.route[node]][s.route[next_index]]);

	}



}



void Genetic::addVertexForVehicle(Individuo &s)
{
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

void Genetic::twoOptFirstImprovement(Individuo &solution)
{

	improvement = true;

	while (improvement)
	{

		improvement = false;

		lowest_fitness = solution.getFitness();

		for (unsigned int i = 1; i < in->num_vertices - 2; i++)
		{

			for (unsigned int k = i + 1; k < in->num_vertices - 1; k++)
			{

				delta = deltaEvaluation(solution, i, k);

				if (delta < 0)
				{

					swapNodes(solution, i, k);

					if (solution.getFitness() < lowest_fitness)
						improvement = true;
				}
			}
		}
	}
}

void Genetic::twoOptBestImprovement(Individuo &solution)
{

	global_improvement = true;

	best_i = best_k = -1;
	delta = 1;

	while (global_improvement)
	{

		global_improvement = false;

		lowest_fitness = solution.getFitness();

		for (unsigned int i = 1; i < in->num_vertices - 2; i++)
		{

			best_delta = 0;

			improvement = false;

			for (unsigned int k = i + 1; k < in->num_vertices - 1; k++)
			{

				delta = deltaEvaluation(solution, i, k);

				if (delta < 0 && delta < best_delta)
				{

					best_delta = delta;
					best_i = i;
					best_k = k;
					improvement = true;
				}
			}

			if (improvement)
			{
				if (capacityIsSatisfied(solution, best_i, best_k))
				{
					swapNodes(solution, best_i, best_k);

					if (solution.getFitness() < lowest_fitness)
						global_improvement = true;
				}
			}
		}
	}
}

int Genetic::calculatePartialRoute(Individuo &s, int i, int k)
{

	if (i == k + 1 || i == k - 1)
	{

		// i is a stop index, k is not a stop index
		if (s.verifyPrecedent(i, i) == 0 && s.verifyPrecedent(k, k) != 0)
		{

			return in->distance_matrix[s.verifyPrecedent(i - 1, i - 1)][s.route[i]] 
			+ in->distance_matrix[s.route[i]][s.verifyPrecedent(i, i + 1)] 
			+ in->distance_matrix[s.verifyPrecedent(k - 1, k - 1)][s.route[k]] 
			+ in->distance_matrix[s.route[k]][s.verifyPrecedent(k, k + 1)];
		}

		// i is not a stop index, k is a stop index
		if (s.verifyPrecedent(i, i) != 0 && s.verifyPrecedent(k, k) == 0)
		{

			return in->distance_matrix[s.verifyPrecedent(i - 1, i - 1)][s.route[i]] 
			+ in->distance_matrix[s.verifyPrecedent(k - 1, k - 1)][s.route[k]] 
			+ in->distance_matrix[s.route[k]][s.verifyPrecedent(k, k + 1)];
		}

		// i is a stop index, k is a stop index
		if (s.verifyPrecedent(i, i) == 0 && s.verifyPrecedent(k, k) == 0)
		{

			return in->distance_matrix[s.verifyPrecedent(i - 1, i - 1)][s.route[i]] 
			+ in->distance_matrix[s.route[i]][s.verifyPrecedent(i, i + 1)] 
			+ in->distance_matrix[s.verifyPrecedent(k - 1, k - 1)][s.route[k]] 
			+ in->distance_matrix[s.route[k]][s.verifyPrecedent(k, k + 1)];
		}

		return in->distance_matrix[s.verifyPrecedent(i - 1, i - 1)][s.route[i]] 
		+ in->distance_matrix[s.verifyPrecedent(k - 1, k - 1)][s.route[k]] 
		+ in->distance_matrix[s.route[k]][s.verifyPrecedent(k, k + 1)];
	}

	return in->distance_matrix[s.verifyPrecedent(i - 1, i - 1)][s.route[i]] 
	+ in->distance_matrix[s.route[i]][s.verifyPrecedent(i, i + 1)] 
	+ in->distance_matrix[s.verifyPrecedent(k - 1, k - 1)][s.route[k]] 
	+ in->distance_matrix[s.route[k]][s.verifyPrecedent(k, k + 1)];
}

void Genetic::swapNodes(Individuo &s, int i, int k)
{

	int vehicle1, vehicle2, capacity1, capacity2;

	vehicle1 = s.vehicle_associated[i];
	vehicle2 = s.vehicle_associated[k];

	if (vehicle1 != vehicle2)
	{

		s.atual_capacity[vehicle1] = s.atual_capacity[vehicle1] + in->demand[s.route[i]] - in->demand[s.route[k]];
		s.atual_capacity[vehicle2] = s.atual_capacity[vehicle2] + in->demand[s.route[k]] - in->demand[s.route[i]];
	}

	current_edges_value = calculatePartialRoute(s, i, k);

	swap(s.route[i], s.route[k]);

	new_edges_value = calculatePartialRoute(s, i, k);

	s.fitness_set(s.fitness_get() - current_edges_value + new_edges_value);

		/*#ifdef DEBUG_SWAP

		// Valor do fitness apos a execucao de swapnodes
		int old_fitness = s.fitness_get();

		// Calcula o fitness do zero
		s.setFitness();

		// Pega o novo valor do fitness
		int new_fitness = s.getFitness();

		// Verifica se existe divergencia
		if(old_fitness != new_fitness){
			cout << "fitness apos swap: " << old_fitness << endl;
			cout << "fitness calculado: " << new_fitness << endl;
		}
			

		// Continua com o valor computado por esta função
		s.fitness_set(old_fitness);
		#endif*/
	

}

int Genetic::deltaEvaluation(Individuo &s, int i, int k)
{

	current_edges_value = calculatePartialRoute(s, i, k);

	swap(s.route[i], s.route[k]);

	new_edges_value = calculatePartialRoute(s, i, k);

	swap(s.route[i], s.route[k]);

	return new_edges_value - current_edges_value;
}

bool Genetic::searchFitness(Individuo &s)
{

	for (unsigned int i = 0; i < population.size(); i++)
		if (s.getFitness() == population[i].getFitness())
			return true;

	return false;
}

void Genetic::showResult()
{

	population[0].printRoute();
	population[0].printVehicles();
	population[0].printCapacities();
	population[0].printStopIndexes();
	population[0].printFitness();
}

void Genetic::printPopulation()
{

	for (unsigned int i = 0; i < population.size(); i++)
	{
		population[i].printRoute();
		population[i].printVehicles();
		population[i].printCapacities();
		population[i].printStopIndexes();
		population[i].printFitness();
		
	}
}

void Genetic::run()
{

	int generations = 0,
		alfa = 0,
		beta = 0;

	double mutation_number;

	Individuo i1(in),
		i2(in);

	// Parents
	Individuo p1(in),
		p2(in);

	// Sons of parents p1 and p2
	Individuo f1(in),
		f2(in);

	// Best solution
	Individuo best(in);

	init();

	//showResult();

	//exit(0);


	while (generations <= limit)
	{

		alfa = beta = 0;

		while (alfa < alfa_max and beta < beta_max)
		{

			best = population[0];

			selection(i1, i2, p1, 0);
			selection(i1, i2, p2, p1.getFitness());

			crossover(p1, p2, f1, f2);

			mutation_number = rand() % mutation_range;

			if (mutation_number < probability)
			{

				mutation(f1);
				mutation(f2);
				
				alfa++;
			}

			twoOptBestImprovement(f1);
			twoOptBestImprovement(f2);


			insertion(f1, best, beta);
			insertion(f2, best, beta);
		}

		generations++;

		cout << "gen: " << generations << " - best fitness: " << best.getFitness() << endl;

		partialReplacement();
	}

	population[0] = best;
}
