/*
 * Veiculo.cpp
 *
 *  Created on: 12 de mai de 2018
 *      Author: adamr
 */

#include "veiculo.h"

using namespace std;

Veiculo::Veiculo(int tamanho_rota) {

	rota_.resize(tamanho_rota+1, -1);

	rota_[0] = rota_[rota_.size() - 1] = 0;

}





