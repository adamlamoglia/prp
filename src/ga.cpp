/*
 * ga.cpp
 *
 *  Created on: 10 de jul de 2018
 *      Author: adamr
 */

#include "ga.h"



int aux;

Genetic::Genetic(Input *in, int alfa, int beta, int generations, double prob_mutation,
		int size, double lucky_factor, int lucky_range, int mutation_range) {

	this->in = in;

	alfa_max = alfa;
	beta_max = beta;
	limit = generations;
	probability = prob_mutation;

	this->lucky_factor = lucky_factor;
	this->lucky_range = lucky_range;
	this->mutation_range = mutation_range;
	cut_size = in->num_vertices/2;

	cut = size/2;

	population.resize(size, Individuo(in));

	repeated_vertex_f1.resize(in->num_vertices,false);
	repeated_vertex_f2.resize(in->num_vertices,false);
	inserted_vertex_f1.resize(in->num_vertices,false);
	inserted_vertex_f2.resize(in->num_vertices,false);

}

Genetic::~Genetic(){

}

bool lowerFitness(Individuo a, Individuo b){
	return a.getFitness() < b.getFitness();
}

unsigned int Genetic::left(unsigned int i){

	return 2*i + 1;
}

unsigned int Genetic::right(unsigned int i){

	return 2*i + 2;
}

void Genetic::sortPopulation(){

	sort(population.begin(), population.end(), lowerFitness);
}

void Genetic::extractMin(){
	
}

void Genetic::minHeapify(unsigned int i){

	l = left(i);
	r = right(i);

	if(l < population.size() && population[l].getFitness() < population[i].getFitness())
		smallest = l;

	else 
		smallest = i;
	
	if(r < population.size() && population[r].getFitness() < population[smallest].getFitness())
		smallest = r;

	if(smallest != i){

		swap(population[i],population[smallest]);
		minHeapify(smallest);
	}

	
	
}

void Genetic::buildMinHeap(){

	for(int i = floor(population.size()/2); i >= 0; i--)
		minHeapify(i);
	
}

void Genetic::create(int limit){

	for(int i = limit; i < population.size(); i++){

		for(unsigned int index = 1; index < in->num_vertices; index++)
			population[i].setRoute(index,index);

		random_shuffle ( population[i].route.begin() + 1, population[i].route.end() - 1);

		population[i].setFitness();
		
	}
	
	//buildMinHeap();
	sortPopulation();

}

void Genetic::init(){

	create(0);
}

void Genetic::partialReplacement(){

	create(cut);
}

void Genetic::binaryTour(Individuo &i1, Individuo &i2, Individuo &p, int previous_fitness){

		lucky_number = rand() % lucky_range;


		do{

			random_person = rand() % population.size();
			i1 = population[random_person];

		}while(i1.getFitness() == previous_fitness);

		do{

			random_person = rand() % population.size();
			i2 = population[random_person];

		}while(i1.getFitness() == i2.getFitness() || i2.getFitness() == previous_fitness);

		if(i1.getFitness() < i2.getFitness() && lucky_factor > lucky_number)
			p = i1;

		else
			p = i2;

}

void Genetic::removeRepeatedNodes(Individuo &f1, Individuo &f2){

	for(int i = 1; i < in->num_vertices; i++){
		int a =  f1.route[i];
		if(repeated_vertex_f1[a]){

			f1.route[i] = -1;
			repeated_vertex_f1[a] = false;

		}

	}


	for(int i = 1; i < in->num_vertices; i++){
		int a =  f2.route[i];
		if(repeated_vertex_f2[a]){

			f2.route[i] = -1;
			repeated_vertex_f2[a] = false;
		}

	}

}

void Genetic::insertNodes(Individuo &f1, Individuo &f2){

	for(int i = 1; i < in->num_vertices; i++){

			if(f1.route[i] == -1){
				for(int j = 1; j < in->num_vertices; j++){

					if(!inserted_vertex_f1[j]){

						f1.route[i] = j;
						inserted_vertex_f1[j] = true;
						break;
					}
				}
			}

	}

	for(int i = 1; i < in->num_vertices; i++){

			if(f2.route[i] == -1){

				for(int j = 1; j < in->num_vertices; j++){

					if(!inserted_vertex_f2[j]){
						f2.route[i] = j;
						inserted_vertex_f2[j] = true;
						break;
					}
				}
			}

	}

}

void Genetic::onePointCrossover(Individuo &p1, Individuo &p2, Individuo &f1, Individuo &f2){

		f1 = p1;
		f2 = p2;


		for(int i = cut_size; i < in->num_vertices; i++){
			inserted_vertex_f1[f1.route[i]] = true;
			inserted_vertex_f2[f2.route[i]] = true;
		}


		for(int i = 1; i < cut_size; i++){

			if(inserted_vertex_f1[p2.route[i]])
				repeated_vertex_f1[p2.route[i]] = true;
			else
				inserted_vertex_f1[p2.route[i]] = true;


			f1.route[i] = p2.route[i];
		}


		for(int i = 1; i < cut_size; i++){

			if(inserted_vertex_f2[p1.route[i]])
				repeated_vertex_f2[p1.route[i]] = true;
			else
				inserted_vertex_f2[p1.route[i]] = true;


			f2.route[i] = p1.route[i];
		}



		removeRepeatedNodes(f1,f2);
		insertNodes(f1,f2);

		f1.setFitness();
		f2.setFitness();

		for(int i = 1; i < in->num_vertices; i++){
			inserted_vertex_f1[i] = false;
			inserted_vertex_f2[i] = false;
			repeated_vertex_f1[i] = false;
			repeated_vertex_f2[i] = false;
		}

}

void Genetic::uniformCrossover(Individuo &p1, Individuo &p2,Individuo &f1, Individuo &f2){

	f1 = p1;
	f2 = p2;

	for(unsigned int i = 1; i < in->num_vertices - 1; i++){

			aux = f1.route[i];
			
			swapNodes(f1,f1.route[i],f2.route[i]);	
			swapNodes(f2, aux, f2.route[i]);

	}

}

void Genetic::swapNodeCrossover(Individuo &p1, Individuo &p2, Individuo &f1, Individuo &f2){

	f1 = p1;
	f2 = p2;

	random_node1 = rand() % in->num_vertices;
	do{
		random_node1 = rand() % in->num_vertices;

	}while(random_node1 == 0 || random_node1 == in->num_vertices - 1);

	random_node2 = rand() % in->num_vertices;
	do{
		random_node2 = rand() % in->num_vertices;

	}while(random_node2 == 0 || random_node1 == in->num_vertices - 1);


	swapNodes(f1,random_node1,random_node2);

	random_node1 = rand() % in->num_vertices;

	do{
		random_node1 = rand() % in->num_vertices;
	}while(random_node1 == 0 || random_node1 == in->num_vertices - 1);

	random_node2 = rand() % in->num_vertices;

	do{
		random_node2 = rand() % in->num_vertices;
	}while(random_node2 == 0 || random_node1 == in->num_vertices - 1);

	swapNodes(f2,random_node1,random_node2);
}

void Genetic::mutationSwap(Individuo &f){

	random_node1 = rand() % in->num_vertices;

	do{
		random_node1 = rand() % in->num_vertices;

	}while(random_node1 == 0 || random_node1 == in->num_vertices - 1);

	random_node2 = rand() % in->num_vertices;
	
	do{
		random_node2 = rand() % in->num_vertices;

	}while(random_node2 == 0 || random_node1 == in->num_vertices - 1);

	swapNodes(f,random_node1,random_node2);

}

void Genetic::swapNodes(Individuo &s, int i, int k){

	current_edges_value = 	in->distance_matrix[s.route[i]][s.route[i+1]]
							+ in->distance_matrix[s.route[i-1]][s.route[i]]
							+ in->distance_matrix[s.route[k]][s.route[k+1]]
							+ in->distance_matrix[s.route[k-1]][s.route[k]];

	swap(s.route[i],s.route[k]);

	new_edges_value = 		in->distance_matrix[s.route[i]][s.route[i+1]]
							+ in->distance_matrix[s.route[i-1]][s.route[i]]
							+ in->distance_matrix[s.route[k]][s.route[k+1]]
							+ in->distance_matrix[s.route[k-1]][s.route[k]];

	s.fitness = s.fitness - current_edges_value + new_edges_value;
}

int Genetic::deltaEvaluation(Individuo &s, int i, int k){
	
	current_edges_value = 	in->distance_matrix[s.route[i]][s.route[i+1]]
							+ in->distance_matrix[s.route[i-1]][s.route[i]]
							+ in->distance_matrix[s.route[k]][s.route[k+1]]
							+ in->distance_matrix[s.route[k-1]][s.route[k]];

	swap(s.route[i],s.route[k]);

	new_edges_value = 		in->distance_matrix[s.route[i]][s.route[i+1]]
							+ in->distance_matrix[s.route[i-1]][s.route[i]]
							+ in->distance_matrix[s.route[k]][s.route[k+1]]
							+ in->distance_matrix[s.route[k-1]][s.route[k]];
	
	swap(s.route[i],s.route[k]);

	return new_edges_value - current_edges_value;
}

void Genetic::twoOptFirstImprovement(Individuo &solution){
	
	improvement = true;


	while(improvement){

		improvement = false;

		lowest_fitness = solution.getFitness();

		for(int i = 1; i < in->num_vertices - 2; i++){
				
			for(int k = i + 1; k < in->num_vertices - 1; k++){

				if(deltaEvaluation(solution,i,k) < 0){

					swapNodes(solution,i,k);

					if(solution.getFitness() < lowest_fitness)
						improvement = true;
						
				}

			}

		}

	}

}

void Genetic::twoOptBestImprovement(Individuo &solution){
	
	global_improvement = true;

	best_i = best_k = -1;

	while(global_improvement){

		best_delta = 0;

		global_improvement = false;

		for(int i = 1; i < in->num_vertices - 2; i++){
			
			improvement = false;

			for(int k = i + 1; k < in->num_vertices - 1; k++){
					
				delta = deltaEvaluation(solution,i,k);

				if(delta < 0 && delta < best_delta){
						
					best_delta = delta;
					best_i = i;
					best_k = k;
					improvement =  global_improvement = true;
				
				}

			}

			if(improvement)
				swapNodes(solution,best_i,best_k);
			
		}

	}

}

void Genetic::acception(Individuo &s){

	random_person = rand() % population.size()/2 + population.size()/2;

	if(population[random_person].getFitness() > s.getFitness())
		population[random_person] = s;
}

bool Genetic::searchFitness(Individuo &s){

	for(unsigned int i = 0; i < population.size(); i++)
		if(s.getFitness() == population[i].getFitness())
			return true;

	return false;
}

void Genetic::showResult(){

	population[0].printRoute();
	population[0].printFitness();

}

void Genetic::printPopulation(){

	for(unsigned int i = 0; i < population.size(); i++){
		population[i].printRoute();
		population[i].printFitness();
	}
}

void Genetic::run(){

	int generations = 0,
		alfa = 0,
		beta = 0,
		best_fitness;

	double mutation_number;

	Individuo i1(in),
			  i2(in);

	// Parents
	Individuo p1(in),
			  p2(in);

	// Sons of parents p1 and p2
	Individuo f1(in),
			  f2(in);
	
	// Sons after mutation
	Individuo s1(in),
			  s2(in);
			  
	// Best solution
	Individuo  best(in);

	init();

	while(generations <= limit){

		cout << "generation " << generations << " - ";

		alfa = beta = 0;

		while(alfa < alfa_max and beta < beta_max){

			best = population[0];

			binaryTour(i1, i2, p1, 0);
			binaryTour(i1, i2, p2, p1.getFitness());


			onePointCrossover(p1, p2, f1, f2);
			//uniformCrossover(p1, p2, f1, f2);
			//swapNodeCrossover(p1, p2, f1, f2);

			mutationSwap(f1);
			mutationSwap(f2);

			mutation_number = rand() % mutation_range;

			if(mutation_number < probability){
				
				twoOptBestImprovement(f1);
				twoOptBestImprovement(f2);
				//twoOptFirstImprovement(f1);
				//twoOptFirstImprovement(f2);

				alfa++;
			}

			if(!searchFitness(f1))
				acception(f1);

			if(!searchFitness(f2))
				acception(f2);

			if(f1.getFitness() < best.getFitness()){
				best = f1;
				beta++;
			}
			
			if(f1.getFitness() < best.getFitness()){
				best = f2;
				beta++;
			}


		}

		sortPopulation();

		if(generations == 0)
			best = population[0];

		else if(population[0].getFitness() < best.getFitness())
			best = population[0];

		generations++;

		cout << "best fitness: " << best.getFitness() << endl;

		partialReplacement();
	}

	population[0] = best;
}


