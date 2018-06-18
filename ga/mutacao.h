/*
 * mutacao.h
 *
 *  Created on: 20 de mai de 2018
 *      Author: adamr
 */

#ifndef MUTACAO_H_
#define MUTACAO_H_

#include <vector>
#include <algorithm>
#include "populacao.h"

using namespace std;

class Mutacao {

private:
	Populacao *populacao_;
	bool melhora_mutacao;
public:

	Mutacao(Populacao *populacao_);
	vector<int> doisOpt(vector<int> rota_);
	bool verificaMelhoriaNaMutacao(vector<int> &rota_atual, vector<int> &rota_nova, int u, int v);
	pair<int,int> procurarArestaMaisCustosa(vector<int,int> rota_);
};


#endif /* MUTACAO_H_ */
