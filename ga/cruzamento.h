/*
 * cruzamento.h
 *
 *  Created on: 17 de mai de 2018
 *      Author: adamr
 */

#ifndef CRUZAMENTO_H_
#define CRUZAMENTO_H_

#include "populacao.h"

using namespace std;

class Cruzamento {
private:
	Populacao *populacao_;
	int tamanho_corte;
	pair<Individuo,Individuo> gerados_;
	vector<bool> lista_de_vertices_inseridos_na_rota;
	vector<bool> lista_de_vertices_repetidos_na_rota;
public:

	Cruzamento(Populacao* populacao_, int tamanho_corte);
	Cruzamento();
	vector<int> eliminarRepeticoesFilho1(vector<int> &rota_);
	vector<int> eliminarRepeticoesFilho2(vector<int> &rota_);
	vector<int> inserirVerticesNaRotaDoIndividuo(vector<int> &rota_);
	pair<Individuo, Individuo> cruzarPorCorteDeUmPonto(pair<Individuo, Individuo> geradores);
	void zerarListaDeVertices();
};


#endif /* CRUZAMENTO_H_ */
