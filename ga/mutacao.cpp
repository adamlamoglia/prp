/*
 * mutacao.cpp
 *
 *  Created on: 20 de mai de 2018
 *      Author: adamr
 */

#include "mutacao.h"



Mutacao::Mutacao(Populacao *populacao_) {
	melhora_mutacao = false;
	this->populacao_ = populacao_;

}

bool Mutacao::verificaMelhoriaNaMutacao(vector<int> &rota_atual, vector<int> &rota_nova, int u, int v){
	int fitness_parcial_atual, fitness_parcial_novo;

	fitness_parcial_atual = populacao_->getGrafo()->lista_de_adjacencia[rota_atual[u-1]][rota_atual[u]]
							+ populacao_->getGrafo()->lista_de_adjacencia[rota_atual[u]][rota_atual[u+1]]
									+  populacao_->getGrafo()->lista_de_adjacencia[rota_atual[v-1]][rota_atual[v]]
											+ populacao_->getGrafo()->lista_de_adjacencia[rota_atual[v]][rota_atual[v+1]];

	fitness_parcial_novo = populacao_->getGrafo()->lista_de_adjacencia[rota_nova[u-1]][rota_nova[u]]
							+ populacao_->getGrafo()->lista_de_adjacencia[rota_nova[u]][rota_nova[u+1]]
									+  populacao_->getGrafo()->lista_de_adjacencia[rota_nova[v-1]][rota_nova[v]]
											+ populacao_->getGrafo()->lista_de_adjacencia[rota_nova[v]][rota_nova[v+1]];

	if(fitness_parcial_novo < fitness_parcial_atual)
		return true;

	return false;

}

//swap mutation
vector<int> Mutacao::doisOpt(vector<int> rota_){
	vector<int> rota_nova, rota_final;
	rota_nova = rota_;
	rota_final = rota_;
	int vertice_de_mudanca_atual = 1;



		for(int i = 1; i < rota_.size()-1; i++){
			for(int j = 2; j < rota_.size() - 1; j++){
				swap(rota_nova[i],rota_nova[j]);

				if(verificaMelhoriaNaMutacao(rota_,rota_nova,i,j)){
					rota_final = rota_nova;
				}
			}

		}

	return rota_final;

}

