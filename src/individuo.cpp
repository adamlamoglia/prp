/*
 * individuo.cpp
 *
 *  Created on: 10 de jul de 2018
 *      Author: adamr
 */

#include "individuo.h"


Individuo::Individuo() : Output() {

}

void Individuo::setRoute(unsigned int vehicle, unsigned int vertex){

	route[vehicle].push_back(vertex);

}

void Individuo::calculateFitness(){

	setFitness(0);

	for(unsigned int i = 0; i < route.size(); i++){
		
		for(unsigned int j = 1; j < route[i].size(); j++){

			if(route[i][j-1] == 0 && route[i][j] == 0)
				break;

			else if(j == 1)
				setFitness( getFitness() + in->distance_matrix[ 0 ][ route[i][j - 1] ] 
				 + in->distance_matrix[ route[i][j - 1]  ][ route[i][j] ]);

			else
				setFitness( getFitness() + in->distance_matrix[ route[i][j - 1]  ][ route[i][j] ]);
			

		}
			
	}
		

}




