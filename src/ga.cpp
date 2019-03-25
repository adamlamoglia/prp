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
	this->mutation_type = mtype;

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

bool Genetic::clientsServed(){
	
	for (unsigned int i = 1; i < inserted.size() - 1; i++)
			if(!inserted[i])
				return false;
	
	return true;
}

void Genetic::create(int limit)
{

	for (unsigned int i = limit; i < population.size(); i++)
	{

		int atual_index = 1,
			atual_vehicle = 1,
			random_client;

		for (unsigned int j = 1; j < inserted.size() - 1; j++)
			inserted[j] = false;
		
		if(limit > 0){

			for(unsigned int j = 0; j < population[i].route.size(); j++){
				population[i].route[j].id = 0;
				population[i].route[j].vehicle = 0;
			}

			for(unsigned int j = 0; j < population[i].fleet.size(); j++){

				if(population[i].fleet[j].capacity != in->capacity)
					population[i].fleet[j].capacity = in->capacity;
			}
		}

		while (!clientsServed())
		{

			random_client = rand() % in->num_vertices;

			while (inserted[random_client] || random_client == 0)
				random_client = rand() % in->num_vertices;

			if (population[i].fleet[atual_vehicle].capacity - in->demand[random_client] >= 0)
			{

				population[i].setRoute(atual_index, random_client);
				population[i].route[atual_index].vehicle = atual_vehicle;
				population[i].fleet[atual_vehicle].capacity -= in->demand[random_client];
				inserted[random_client] = true;
			}

			else
				atual_vehicle++;
		

			atual_index++;

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
		break;

	case 2:
		randomSelection(p);
		break;

	case 3:
		rankSelection(i1, i2, p, previous_fitness);
		break;

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
		break;

	case 2:
		uniformCrossover(p1, p2, f1, f2);
		break;

	case 3:
		onePointCrossover(p1, p2, f1, f2);
		break;

	case 4:
		routeCrossover(p1, p2, f1, f2);
		break;

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
		break;

	case 2:
		mutationScramble(f);
		break;

	case 3:
		mutationInversion(f);
		break;

	case 4:
		removeVertexFromVehicle(f);
		break;

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
			break;

		case 2:
			randomInsertion(s);
			break;

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
		inserted_vertex_f1[f1.route[i].id] = true;
		inserted_vertex_f2[f2.route[i].id] = true;
	}

	for (int i = 1; i < cut_size; i++)
	{

		if (inserted_vertex_f1[p2.route[i].id])
			repeated_vertex_f1[p2.route[i].id] = true;
		else
			inserted_vertex_f1[p2.route[i].id] = true;

		f1.route[i].id = p2.route[i].id;
	}

	for (int i = 1; i < cut_size; i++)
	{

		if (inserted_vertex_f2[p1.route[i].id])
			repeated_vertex_f2[p1.route[i].id] = true;
		else
			inserted_vertex_f2[p1.route[i].id] = true;

		f2.route[i].id = p1.route[i].id;
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

		int a = f1.route[i].id;

		if (repeated_vertex_f1[a])
		{

			f1.route[i].id = -1;
			repeated_vertex_f1[a] = false;
		}
	}

	for (unsigned int i = 1; i < in->num_vertices; i++)
	{

		int a = f2.route[i].id;

		if (repeated_vertex_f2[a])
		{

			f2.route[i].id = -1;
			repeated_vertex_f2[a] = false;
		}
	}
}

void Genetic::insertNodes(Individuo &f1, Individuo &f2)
{

	for (unsigned int i = 1; i < in->num_vertices; i++)
	{

		if (f1.route[i].id == -1)
		{

			for (unsigned int j = 1; j < in->num_vertices; j++)
			{

				if (!inserted_vertex_f1[j])
				{

					f1.route[i].id = j;
					inserted_vertex_f1[j] = true;
					break;
				}
			}
		}
	}

	for (unsigned int i = 1; i < in->num_vertices; i++)
	{

		if (f2.route[i].id == -1)
		{

			for (unsigned int j = 1; j < in->num_vertices; j++)
			{

				if (!inserted_vertex_f2[j])
				{

					f2.route[i].id = j;

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

		aux = f1.route[i].id;

		swapNodes(f1, f1.route[i].id, f2.route[i].id);
		swapNodes(f2, aux, f2.route[i].id);
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

		} while (s.route[random_node1].id == 0);

		random_node2 = rand() % in->num_vertices;
		do
		{
			random_node2 = rand() % in->num_vertices;

		} while (s.route[random_node2].id == 0 || s.route[random_node1].id == s.route[random_node2].id);

	} while (!capacityIsSatisfied(s, random_node1, random_node2));

}

bool Genetic::capacityIsSatisfied(Individuo &s, int node1, int node2)
{

	int vehicle1, vehicle2, capacity1, capacity2;

	vehicle1 = s.route[node1].vehicle;
	vehicle2 = s.route[node2].vehicle;

	if (vehicle1 == vehicle2)
		return true;

	capacity1 = s.fleet[vehicle1].capacity;
	capacity2 = s.fleet[vehicle2].capacity;

	if (capacity1 + in->demand[s.route[node1].id] - in->demand[s.route[node2].id] >= 0 &&
		capacity2 + in->demand[s.route[node2].id] - in->demand[s.route[node1].id] >= 0)
	{

		return true;
	}

	return false;
}

bool Genetic::capacityRemovingIsSatisfied(Individuo &s, int node1, int node2)
{

	int vehicle1, vehicle2, capacity1, capacity2;

	vehicle1 = s.route[node1].vehicle;
	vehicle2 = s.route[node2].vehicle;

	if(vehicle1 == vehicle2)
		return false;

	capacity1 = s.fleet[vehicle1].capacity;
	capacity2 = s.fleet[vehicle2].capacity;

	if (capacity2 - in->demand[s.route[node1].id] >= 0)
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
	int change_index = 0;

	f1 = p1;
	f2 = p2;

	//f1.printRoute();

	mask.resize(f1.getNumVehicles(), 0);

	for (int i = 0; i < mask.size(); i++)
		mask[i] = rand() % 2;

	//pick route to change
	for(int i = 0; i < mask.size(); i++){
		
		if(mask[i] == 0){
			
			pickRoute(f1, i + 1);
			
			break;
		}
		else if(i == mask.size() - 1)
			pickRoute(f1, i + 1);

	}

	//for(int i = 0; i < before_list.size(); i++)
	//	cout << before_list[i] << " ";
	
	//cout << endl;

	sortRoute(p2);

	//p2.printRoute();

	//for(int i = 0; i < after_list.size(); i++)
	//	cout << after_list[i] << " ";
	
	//cout << endl;

	updateRoute(f1);

	//f1.printRoute();

	//exit(1);

	change_index = 0;

	mask.resize(f2.getNumVehicles(), 0);

	for (int i = 0; i < mask.size(); i++)
		mask[i] = rand() % 2;

	//pick route to change
	for(int i = 0; i < mask.size(); i++){
		
		if(mask[i] == 0){
			
			pickRoute(f2, i + 1);
			
			break;
		}
		else if(i == mask.size() - 1)
			pickRoute(f2, i + 1);

	}

	sortRoute(p1);

	updateRoute(f2);

	//exit(1);
}

void Genetic::pickRoute(Individuo &s, int vehicle)
{

	int sizeRoute = 0, list_index = 0;

	for (int i = 0; i < s.route.size(); i++)
	{

		if (s.route[i].vehicle == vehicle)
			sizeRoute++;
		
	}

	before_list.resize(sizeRoute);
	after_list.resize(sizeRoute);
	sort_index.resize(sizeRoute);

	for (int i = 0; i < s.route.size(); i++)
	{

		if (s.route[i].vehicle == vehicle)
		{

			if (list_index == 0)
				begin_index = i;

			else if (list_index == before_list.size() - 1)
				end_index = i;

			before_list[list_index++] = s.route[i].id;
		}
	}
}

void Genetic::sortRoute(Individuo &s)
{

	for (int i = 0; i < before_list.size(); i++)
	{

		for (int j = 0; j < s.route.size(); j++)
		{

			if (before_list[i] == s.route[j].id)
			{

				sort_index[i] = j;
				break;
			}
		}
	}

	sort(sort_index.begin(), sort_index.end());

	for (int i = 0; i < after_list.size(); i++)
	{

		after_list[i] = s.route[sort_index[i]].id;
	}
}

void Genetic::updateRoute(Individuo &s)
{

	int before_route = 0,
		after_route = 0,
		list_index = 0;

	//this part is wrong..
	for (int i = 0; i < before_list.size(); i++)
	{
		if (i == 0){
			before_route += in->distance_matrix[0][before_list[i]];
			after_route += in->distance_matrix[0][after_list[i]];
		}
		else if (i == before_list.size() - 1){
			before_route += in->distance_matrix[before_list[i]][0];
			after_route += in->distance_matrix[after_list[i]][0];
		}
		else{
			before_route += in->distance_matrix[before_list[i]][before_list[i + 1]];
			after_route += in->distance_matrix[after_list[i]][after_list[i + 1]];
		}
	}
	//this part is wrong..

	s.fitness_set(s.fitness_get() - before_route + after_route);

	for (int i = begin_index; i <= end_index; i++)
		s.route[i].id = after_list[list_index++];
	
	#ifdef DEBUG_SWAP

		// Valor do fitness apos a execucao de swapnodes
		int old_fitness = s.fitness_get();

		// Calcula o fitness do zero
		s.setFitness();

		// Pega o novo valor do fitness
		int new_fitness = s.getFitness();

		// Verifica se existe divergencia
		if(old_fitness != new_fitness){
			//cout << "fitness apos update: " << old_fitness << endl;
			//cout << "fitness calculado: " << new_fitness << endl;
			//exit(1);
		}
			

		// Continua com o valor computado por esta função
		s.fitness_set(new_fitness);
		#endif
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

	int vehicle1, vehicle2, capacity1;

	cout << "entrou" << endl;
	s.printRoute();
	s.printVehicles();

	for(int i = 0; i < s.route.size(); i++){

		for(int j = i + 1; j < s.route.size(); j++){

			if(s.route[i].vehicle != s.route[j].vehicle && s.route[i].vehicle != 0 && s.route[j].vehicle != 0){

				if(capacityRemovingIsSatisfied(s,i,j)){
					random_node1 = i;
					random_node2 = j;
					break;
				}
			}
		}
	}

	if(s.route[random_node1].vehicle != 0 && s.route[random_node2].vehicle != 0 
	&& s.route[random_node1].vehicle != s.route[random_node2].vehicle && capacityRemovingIsSatisfied(s,random_node1,random_node2)){
		cout << "removing vehicle: " << s.route[random_node1].vehicle << endl;
		cout << "adding in vehicle: " << s.route[random_node2].vehicle << endl;

		vehicle1 = s.route[random_node1].vehicle;
		vehicle2 = s.route[random_node2].vehicle;

		if(vehicle1 < vehicle2){
			remove(s, vehicle1, vehicle2, random_node1);
		}

		else{
			remove(s, vehicle2, vehicle1, random_node2);
		}
	}

}

void Genetic::remove(Individuo &s, int vehicle_removed, int vehicle_added, int node){
	int before_route = 0,
		after_route = 0,
		capacity1,
		capacity2;
	
	
	capacity1 = s.fleet[vehicle_removed].capacity;
	capacity2 = s.fleet[vehicle_added].capacity;

	s.fleet[vehicle_added].capacity = s.fleet[vehicle_added].capacity - in->demand[s.route[node].id];
	s.fleet[vehicle_removed].capacity = s.fleet[vehicle_removed].capacity + in->demand[s.route[node].id];

	cout << "removing vehicle: " << vehicle_removed << endl;
	cout << "adding in vehicle: " << vehicle_added << endl;
	cout << "client: " << s.route[node].id << endl;

	s.printRoute();
	s.printVehicles();
	cout << endl;

	before_route = in->distance_matrix[s.route[node - 1].id][s.route[node].id] 
					+ in->distance_matrix[s.route[node].id][s.route[node + 1].id];
		
	after_route = in->distance_matrix[s.route[node - 1].id][s.route[node + 1].id];

	s.fitness_set(s.fitness_get() - before_route + after_route);

	while(s.route[node + 1].vehicle != vehicle_added){

		swap(s.route[node], s.route[node + 1]);
		node++;
	}

	s.route[node].vehicle = vehicle_added;

	before_route = in->distance_matrix[s.route[node - 1].id][s.route[node + 1].id]; 

	after_route = in->distance_matrix[s.route[node - 1].id][s.route[node].id] 
					+ in->distance_matrix[s.route[node].id][s.route[node + 1].id];

	s.fitness_set(s.fitness_get() - before_route + after_route);

	s.printRoute();
	s.printVehicles();

}

void Genetic::lineUp(Individuo &s, int vehicle1, int vehicle2, int node1, int node2)
{

	int previous_index_node1, next_index_node1, previous_index_node2, next_index_node2;

	int route_node1, route_node2;

	for (int i = node1 - 1; i >= 0; i--)
	{

		if (s.route[i].vehicle == vehicle1 || i == 0)
		{
			previous_index_node1 = i;
			break;
		}
	}

	for (int i = node1 + 1; i < s.route.size(); i++)
	{

		if (s.route[i].vehicle == vehicle1)
		{
			next_index_node1 = i;
			break;
		}

		else if (i == s.route.size() - 1)
			next_index_node1 = 0;
	}

	for (int i = node1 - 1; i >= 0; i--)
	{

		if (s.route[i].vehicle == vehicle2 || i == 0)
		{
			previous_index_node2 = i;
			break;
		}
	}

	for (int i = node1 + 1; i < s.route.size(); i++)
	{

		if (s.route[i].vehicle == vehicle2)
		{
			next_index_node2 = i;
			break;
		}

		else if (i == s.route.size() - 1)
			next_index_node2 = 0;
	}

	//route with single client
	if (previous_index_node1 == 0 && next_index_node1 == 0)
	{

		//cout << "entrou1" << endl;

		s.fitness_set(s.fitness_get() - in->distance_matrix[0][s.route[node1].id] - in->distance_matrix[s.route[node1].id][0]);
	}

	else
	{

		//cout << "entrou2" << endl;

		s.fitness_set(s.fitness_get() - in->distance_matrix[s.route[previous_index_node1].id][s.route[node1].id] - in->distance_matrix[s.route[node1].id][s.route[next_index_node1].id] + in->distance_matrix[s.route[previous_index_node1].id][s.route[next_index_node1].id]);
	}

	if (previous_index_node2 == 0 && next_index_node2 == 0)
	{

		//cout << "entrou3" << endl;

		s.fitness_set(s.fitness_get() + in->distance_matrix[0][s.route[node1].id] + in->distance_matrix[s.route[node1].id][0]);

		//s.setStopIndex(node1);
	}

	else
	{

		//cout << "entrou4" << endl;
		s.fitness_set(s.fitness_get() + in->distance_matrix[s.route[previous_index_node2].id][s.route[node1].id] + in->distance_matrix[s.route[node1].id][s.route[next_index_node2].id] - in->distance_matrix[s.route[previous_index_node2].id][s.route[next_index_node2].id]);
	}
}

void Genetic::lineUpRouteRemoved(Individuo &s, int vehicle, int node)
{
	int previous_index, next_index;

	//line up route of vehicle with removed vertex

	for (int i = node - 1; i >= 0; i--)
	{

		if (s.route[i].vehicle == vehicle || i == 0)
		{
			previous_index = i;
			break;
		}
	}

	for (int i = node + 1; i < s.route.size(); i++)
	{

		if (s.route[i].vehicle == vehicle || i == s.route.size() - 1)
		{
			next_index = i;
			break;
		}
	}

	//there's no more route
	if (previous_index == 0 && s.route[next_index].id == 0)
	{

		s.fitness_set(s.fitness_get() - in->distance_matrix[0][s.route[node].id] - in->distance_matrix[s.route[node].id][0]);
	}

	else if (s.route[previous_index].id == 0)
	{

		s.fitness_set(s.fitness_get() - in->distance_matrix[0][s.route[node].id] - in->distance_matrix[s.route[node].id][s.route[next_index].id] + in->distance_matrix[0][s.route[next_index].id]);
	}

	else if (s.route[next_index].id == 0)
	{

		s.fitness_set(s.fitness_get() - in->distance_matrix[s.route[previous_index].id][s.route[node].id] - in->distance_matrix[s.route[node].id][0] + in->distance_matrix[s.route[previous_index].id][0]);
	}

	else
	{
		s.fitness_set(s.fitness_get() - in->distance_matrix[s.route[previous_index].id][s.route[node].id] - in->distance_matrix[s.route[node].id][s.route[next_index].id] + in->distance_matrix[s.route[previous_index].id][s.route[next_index].id]);
	}
}

void Genetic::lineUpRouteAdded(Individuo &s, int vehicle, int node)
{
	int previous_index, next_index;

	//find 0 or part of the same route

	for (int i = node - 1; i >= 0; i--)
	{

		if (s.route[i].vehicle == vehicle || s.route[i].vehicle == 0)
		{
			previous_index = i;
			break;
		}
	}

	for (int i = node + 1; i < s.route.size(); i++)
	{

		if (s.route[i].vehicle == vehicle || s.route[i].vehicle == 0)
		{
			next_index = i;
			break;
		}
	}

	//line up route of vehicle with add vertex

	if (s.route[previous_index].id == 0)
	{

		s.fitness_set(s.fitness_get() - in->distance_matrix[0][s.route[next_index].id] + in->distance_matrix[0][s.route[node].id] + in->distance_matrix[s.route[node].id][s.route[next_index].id]);
	}

	else if (s.route[next_index].id == 0)
	{

		s.fitness_set(s.fitness_get() - in->distance_matrix[s.route[previous_index].id][0] + in->distance_matrix[s.route[previous_index].id][s.route[node].id] + in->distance_matrix[s.route[node].id][0]);
	}

	else
	{

		s.fitness_set(s.fitness_get() - in->distance_matrix[s.route[previous_index].id][s.route[next_index].id] + in->distance_matrix[s.route[previous_index].id][s.route[node].id] + in->distance_matrix[s.route[node].id][s.route[next_index].id]);
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

		for (unsigned int i = 1; i < in->num_vertices*2; i++)
		{

			best_delta = 0;

			improvement = false;

			for (unsigned int k = i + 1; k < in->num_vertices*2 + 1; k++)
			{

				if(solution.route[i].id != 0 && solution.route[k].id != 0){
					delta = deltaEvaluation(solution, i, k);
				

					if (delta < 0 && delta < best_delta)
					{

						best_delta = delta;
						best_i = i;
						best_k = k;
						improvement = true;
					}
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

	if(i == k - 1){
		return in->distance_matrix[s.route[i-1].id][s.route[i].id] 
				+ in->distance_matrix[s.route[i].id][s.route[k].id] 
				+ in->distance_matrix[s.route[k].id][s.route[k+1].id];
	}

	if(i == k + 1){
		return in->distance_matrix[s.route[k-1].id][s.route[k].id]
				+ in->distance_matrix[s.route[k].id][s.route[i].id] 
				+ in->distance_matrix[s.route[i].id][s.route[i+1].id]; 
				
	}

	return 	in->distance_matrix[s.route[i-1].id][s.route[i].id] 
			+ in->distance_matrix[s.route[i].id][s.route[i+1].id] 
			+ in->distance_matrix[s.route[k-1].id][s.route[k].id] 
			+ in->distance_matrix[s.route[k].id][s.route[k+1].id];

}

void Genetic::swapNodes(Individuo &s, int i, int k)
{


	int vehicle1, vehicle2, capacity1, capacity2;

	vehicle1 = s.route[i].vehicle;
	vehicle2 = s.route[k].vehicle;

	if (vehicle1 != vehicle2)
	{

		s.fleet[vehicle1].capacity = s.fleet[vehicle1].capacity + in->demand[s.route[i].id] - in->demand[s.route[k].id];
		s.fleet[vehicle2].capacity = s.fleet[vehicle2].capacity + in->demand[s.route[k].id] - in->demand[s.route[i].id];
	}

	current_edges_value = calculatePartialRoute(s, i, k);

	swap(s.route[i].id, s.route[k].id);

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
	population[0].printFitness();
}

void Genetic::printPopulation()
{

	for (unsigned int i = 0; i < population.size(); i++)
	{
		population[i].printRoute();
		population[i].printVehicles();
		population[i].printCapacities();
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
