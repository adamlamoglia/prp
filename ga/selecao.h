/*
 * selecao.h
 *
 *  Created on: 17 de mai de 2018
 *      Author: adamr
 */

#ifndef SELECAO_H_
#define SELECAO_H_

#include "populacao.h"

using namespace std;

class Selecao {
private:
	int numero_aleatorio;
	int numero_sorte;
	float fator_sorte;
	pair<Individuo, Individuo> selecionados_;
public:
	Selecao(float fator_sorte);
	Selecao();
	pair<Individuo, Individuo> selecionarPorTorneioBinario(Populacao *p);
};


#endif /* SELECAO_H_ */
