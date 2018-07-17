/*
 * ga.cpp
 *
 *  Created on: 10 de jul de 2018
 *      Author: adamr
 */

#include "ga.h"


Genetic::Genetic(Input *in, int alfa, int beta, int generations, double prob_mutation, int size) {

	this->in = in;

	alfa_max = alfa;
	beta_max = beta;
	limit = generations;
	probability = prob_mutation;

	population.resize(size, Individuo(in));

	visited_vertex.resize(in->num_vertices,false);

}

bool lowerFitness(Individuo a, Individuo b){
	return a.getFitness() < b.getFitness();
}

void Genetic::sortPopulation(){

	sort(population.begin(), population.end(), lowerFitness);
}


void Genetic::init(){
	int random;

	for(unsigned int i = 0; i < population.size(); i++){

		for(unsigned int j = 0; j < visited_vertex.size(); j++)
			visited_vertex[j] = false;

		visited_vertex[0]  =  true;


		for(unsigned int id_vertex = 1; id_vertex < in->num_vertices; id_vertex++){

			//os vertices sao escolhidos no intervalo de 1 a vertices-1
			random = rand() % (in->num_vertices - 1) + 1;

			while(visited_vertex[random])
				random = rand() % (in->num_vertices - 1) + 1;

			population[i].setRoute(id_vertex,random);

			visited_vertex[random] = true;

		}

		population[i].setFitness();
	}

	sortPopulation();
}

void Genetic::binaryTour(){

}

void Genetic::onePointCrossover(){

}

void Genetic::twoOpt(Individuo solution){

}

void Genetic::acception(){

}

bool Genetic::searchFitness(Individuo solution){

}

void Genetic::run(){

	int generations = 0,
		alfa = 0,
		beta = 0,
		random_person;

	double best_fitness,
	       random_mutation;

	Individuo f1(in),
			  f2(in),
			  s1(in),
			  s2(in);

	init();

	for(unsigned int i = 0; i < population.size(); i++){
		population[i].printRoute();
		population[i].printFitness();
	}

	/*while(generations <= limit){
		alfa = beta = 0;

		while(alfa < alfa_max and beta < beta_max){

			best_fitness = population[0].getFitness();

			binaryTour();

			onePointCrossover();

			random_mutation = (rand() % 100)*0.01;

			if(random_mutation < probability){

				twoOpt(s1);
				twoOpt(s2);
			}

			if(!searchFitness(s1)){

				//escolhe um individuo entre 250 e 500 posicao da populacao
				random_person = rand() % population.size()/2 + population.size()/2;

				if(population[random_person].getFitness() > s1.getFitness())
					population[random_person] = s1;

			}

			if(!searchFitness(s2)){

				//escolhe um individuo entre 250 e 500 posicao da populacao
				random_person = rand() % population.size()/2 + population.size()/2;

				if(population[random_person].getFitness() > s2.getFitness())
					population[random_person] = s2;

			}

			alfa++;

			sortPopulation();

			if(population[0].getFitness() == best_fitness)
				beta++;
		}

		generations++;

	}*/

}

