/*
 * ga.h
 *
 *  Created on: 10 de jul de 2018
 *      Author: adamr
 */

#ifndef GA_H_
#define GA_H_

#include "individuo.h"
#include <algorithm>
#include <utility>

class Ga{

public:
	Input *in;

	int alfa_maximo,
		beta_maximo,
		numero_geracoes;

	double probabilidade_mutacao;

	vector<bool> vertices_visitados;

	vector<Individuo> populacao;

	Ga(Input *in, int alfa, int beta, int num_geracoes, double prob_mutacao, int quantidade_individuos);

	void inicializarPopulacao();
	void realizarOperacaoGenetica();
	void ordenarPopulacao();

};


#endif /* GA_H_ */
