/*
 * populacao.h
 *
 *  Created on: 12 de mai de 2018
 *      Author: adamr
 */

#ifndef POPULACAO_H_
#define POPULACAO_H_

using namespace std;

#include <vector>
#include <algorithm>
#include <stdlib.h>

#include "individuo.h"

class Populacao {
private:
	int tamanho;
	Grafo *grafo_;
	Individuo individuoInicial;

public:
	vector<Individuo> lista_de_individuos;

	Populacao(Grafo *g, int tamanho_inicial);

	int getTamanho();

	void gerarPrimeiraGeracao();
	void ordenarIndividuos();
	bool procurarIndividuoPorFitness(double fitness);
	double calcularFitness(vector<int> &rota);
	Grafo* getGrafo();
};

#endif /* POPULACAO_H_ */
