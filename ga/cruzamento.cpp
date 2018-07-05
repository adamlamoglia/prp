/*
 * cruzamento.cpp
 *
 *  Created on: 17 de mai de 2018
 *      Author: adamr
 */

#include "cruzamento.h"

using namespace std;

Cruzamento::Cruzamento(Populacao* populacao_, int tamanho_corte) {

	this->populacao_ = populacao_;
	this->tamanho_corte = tamanho_corte;
	this->lista_de_vertices_repetidos_na_rota.resize(populacao_->getGrafo()->getQuantidadeVertices(),false);
	this->lista_de_vertices_inseridos_na_rota.resize(populacao_->getGrafo()->getQuantidadeVertices(),false);

}


vector<int> Cruzamento::eliminarRepeticoesFilho1(vector<int> &rota_){

	for(int i = 0; i < tamanho_corte; i++){

		if(lista_de_vertices_repetidos_na_rota[rota_[i]]){
			lista_de_vertices_repetidos_na_rota[rota_[i]] = false;
			rota_[i] = -1;
		}


	}

	return rota_;
}

vector<int> Cruzamento::eliminarRepeticoesFilho2(vector<int> &rota_){

	for(int i = tamanho_corte; i < lista_de_vertices_repetidos_na_rota.size(); i++){

		if(lista_de_vertices_repetidos_na_rota[rota_[i]]){
			lista_de_vertices_repetidos_na_rota[rota_[i]] = false;
			rota_[i] = -1;
		}

	}

	return rota_;
}

vector<int> Cruzamento::inserirVerticesNaRotaDoIndividuo(vector<int> &rota_){

	for(int i = 0; i < lista_de_vertices_inseridos_na_rota.size(); i++){

			if(!lista_de_vertices_inseridos_na_rota[i]){
				for(int j = 0; j < rota_.size(); j++){
					if(rota_[j] == -1){
						rota_[j] = i;
						lista_de_vertices_inseridos_na_rota[i] = true;
						break;
					}
				}
			}

		}

		return rota_;
}

void Cruzamento::zerarListaDeVertices(){

	for(int i = 0; i < lista_de_vertices_inseridos_na_rota.size(); i++)
		lista_de_vertices_inseridos_na_rota[i] = lista_de_vertices_repetidos_na_rota[i] = false;

}

pair<Individuo, Individuo> Cruzamento::cruzarPorCorteDeUmPonto(pair<Individuo, Individuo> geradores){

	int novo_vertice;

	gerados_ = geradores;

	zerarListaDeVertices();


	for(int i = 1; i < tamanho_corte; i++){
		novo_vertice = gerados_.second.veiculo_->rota_[i];

		if(lista_de_vertices_inseridos_na_rota[novo_vertice])
			lista_de_vertices_repetidos_na_rota[novo_vertice] = true;
		else
			lista_de_vertices_inseridos_na_rota[novo_vertice] = true;


		gerados_.first.veiculo_->rota_[i] = novo_vertice;

	}

	for(int i = tamanho_corte; i < gerados_.first.veiculo_->rota_.size(); i++){
		int vertice_rota = gerados_.first.veiculo_->rota_[i];

		if(lista_de_vertices_inseridos_na_rota[vertice_rota])
			lista_de_vertices_repetidos_na_rota[vertice_rota] = true;
		else
			lista_de_vertices_inseridos_na_rota[vertice_rota] = true;
	}

	gerados_.first.veiculo_->rota_ = eliminarRepeticoesFilho1(gerados_.first.veiculo_->rota_);


	gerados_.first.veiculo_->rota_ = inserirVerticesNaRotaDoIndividuo(gerados_.first.veiculo_->rota_);

	gerados_.first.setFitness(populacao_->calcularFitness(gerados_.first.veiculo_->rota_));

	zerarListaDeVertices();

	for(int i = tamanho_corte; i < gerados_.second.veiculo_->rota_.size(); i++){
		novo_vertice = gerados_.first.veiculo_->rota_[i];

		if(lista_de_vertices_inseridos_na_rota[novo_vertice])
			lista_de_vertices_repetidos_na_rota[novo_vertice] = true;
		else
			lista_de_vertices_inseridos_na_rota[novo_vertice] = true;

		gerados_.second.veiculo_->rota_[i] = novo_vertice;

	}

	for(int i = 1; i < tamanho_corte; i++){
		int vertice_rota = gerados_.second.veiculo_->rota_[i];

		if(lista_de_vertices_inseridos_na_rota[vertice_rota])
			lista_de_vertices_repetidos_na_rota[vertice_rota] = true;
		else
			lista_de_vertices_inseridos_na_rota[vertice_rota] = true;
	}


	gerados_.second.veiculo_->rota_ = eliminarRepeticoesFilho2(gerados_.second.veiculo_->rota_);


	gerados_.second.veiculo_->rota_ = inserirVerticesNaRotaDoIndividuo(gerados_.second.veiculo_->rota_);

	gerados_.second.setFitness(populacao_->calcularFitness(gerados_.second.veiculo_->rota_));


	return gerados_;

}
