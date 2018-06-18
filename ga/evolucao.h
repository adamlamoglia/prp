/*
 * evolucao.h
 *
 *  Created on: 15 de mai de 2018
 *      Author: adamr
 */

#ifndef EVOLUCAO_H_
#define EVOLUCAO_H_

using namespace std;

#include <cstddef>
#include "populacao.h"
#include "../src/parametros.h"
#include "selecao.h"
#include "cruzamento.h"
#include "mutacao.h"

class Evolucao {
private:
	Parametros *p;

	int alfa_maximo;
	int beta_maximo;
	int numero_geracoes;
	int probabilidade_mutacao;

	Populacao *populacao_;
	Selecao *seletor_;
	Cruzamento *operador_crossover;
	Mutacao *operador_mutacao;
	//Mutacao a;

	pair<Individuo,Individuo> pais_;
	pair<Individuo, Individuo> filhos_;

public:
	Evolucao(Parametros *p,Grafo *g);
	Evolucao();

	void operacaoGenetica();

};



#endif /* EVOLUCAO_H_ */
