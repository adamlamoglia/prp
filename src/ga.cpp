/*
 * ga.cpp
 *
 *  Created on: 10 de jul de 2018
 *      Author: adamr
 */

#include "ga.h"


Genetic::Genetic(Input *in, int alfa, int beta, int generations, double prob_mutation, int size, double lucky) {

	this->in = in;

	alfa_max = alfa;
	beta_max = beta;
	limit = generations;
	probability = prob_mutation;

	lucky_factor = lucky;
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

void Genetic::sortPopulation(){

	sort(population.begin(), population.end(), lowerFitness);
}


void Genetic::create(int limit){

	for(int i = limit; i < population.size(); i++){

		for(unsigned int index = 1; index < in->num_vertices; index++)
			population[i].setRoute(index,index);

		random_shuffle ( population[i].route.begin() + 1, population[i].route.end() - 1);

		population[i].setFitness();
	}

	sortPopulation();

}

void Genetic::init(){

	create(0);
}

void Genetic::partialReplacement(){

	create(cut);
}


void Genetic::binaryTour(Individuo &i1, Individuo &i2, Individuo &p1, Individuo &p2){

		random_person = rand() % population.size();
		
		/* 
		* TODO Este numero precisa ser muito pequeno
		* A chance de ganhar atraves da sorte precisa ser bem pequena
		*/
		lucky_number = rand() % 100;

		i1 = population[random_person];

		do{

			random_person = rand() % population.size();
			i2 = population[random_person];

		}while(i1.getFitness() == i2.getFitness());

		if(i1.getFitness() < i2.getFitness() && lucky_factor > lucky_number)
			p1 = i1;

		else
			p1 = i2;

		// TODO retirar esse onze e colocar uma funcao ou variavel
		lucky_number = rand() % 100;

		do{
			random_person = rand() % population.size();

			i1 = population[random_person];

		}while(i1.getFitness() == p1.getFitness());

		do{
			random_person = rand() % population.size();

			i2 = population[random_person];
		}while(i2.getFitness() == p1.getFitness() || i1.getFitness() == i2.getFitness());

		if(i1.getFitness() < i2.getFitness() && lucky_factor > lucky_number)
			p2 = i1;

		else
			p2 = i2;

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

void Genetic::swapNodes(Individuo &s, int i, int k){

	old_fitness = s.getFitness();

	current_edges_value = 	in->distance_matrix[s.route[i]][s.route[i+1]]
							+ in->distance_matrix[s.route[i-1]][s.route[i]]
							+ in->distance_matrix[s.route[k]][s.route[k+1]]
							+ in->distance_matrix[s.route[k-1]][s.route[k]];

	swap(s.route[i],s.route[k]);

	new_edges_value = 		in->distance_matrix[s.route[i]][s.route[i+1]]
							+ in->distance_matrix[s.route[i-1]][s.route[i]]
							+ in->distance_matrix[s.route[k]][s.route[k+1]]
							+ in->distance_matrix[s.route[k-1]][s.route[k]];

	s.fitness = old_fitness - current_edges_value + new_edges_value;
}

int Genetic::twoOptLocalSearch(Individuo &solution){
	bool improvement = true;
	
	//while(improvement){

		//improvement = false;
		
		//repeat = false;

		//lowest_fitness = f.getFitness();

			//for(int i = 1; i < in->num_vertices - 2; i++){
			//	for(int k = i + 1; k < in->num_vertices - 1; k++){

					//s.route = f.route;
					//twoOptSwap(s,i,k);

					//new_fitness = s.getFitness();

					//if(new_fitness < lowest_fitness){
						//f = s;

						//repeat = true;
						//break;
			//		}
			//	}

				//if(repeat)
					//break;
			//}

			//if(!repeat)
				//no_improvement = false;
	//}

	//s = f;

}

void Genetic::twoOpt(Individuo &f, Individuo &s){

	no_improvement = true;


	while(no_improvement){

		repeat = false;

		lowest_fitness = f.getFitness();

			for(int i = 1; i < in->num_vertices - 2; i++){
				for(int k = i + 1; k < in->num_vertices - 1; k++){

					s = f;
					swapNodes(s,i,k);

					new_fitness = s.getFitness();

					if(new_fitness < lowest_fitness){
						f = s;

						repeat = true;
						break;
					}
				}

				if(repeat)
					break;
			}

			if(!repeat)
				no_improvement = false;
	}

	s = f;

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

	double random_mutation;


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

			best_fitness = population[0].getFitness();


			binaryTour(i1, i2, p1, p2);


			swapNodeCrossover(p1, p2, f1, f2);

			random_mutation = (rand() % 100)*0.01;



			if(random_mutation < probability){

				twoOpt(f1, s1);
				twoOpt(f2, s2);

				alfa++;
			}
			else{
				s1 = f1;
				s2 = f2;
			}


			if(!searchFitness(s1))
				acception(s1);


			if(!searchFitness(s2))
				acception(s2);

			sortPopulation();

			if(population[0].getFitness() == best_fitness)
				beta++;

		}

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

