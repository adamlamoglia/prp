/*
 * selecao.cpp
 *
 *  Created on: 17 de mai de 2018
 *      Author: adamr
 */

#include "selecao.h"

using namespace std;

Selecao::Selecao(float fator_sorte) {

	this->fator_sorte = fator_sorte;

	numero_sorte = rand() % 11;


}

pair<Individuo, Individuo> Selecao::selecionarPorTorneioBinario(Populacao *p){

	Individuo p1;
	Individuo p2;


	numero_aleatorio = rand() % p->getTamanho();

	p1 = p->lista_de_individuos[numero_aleatorio];

	do{

		numero_aleatorio = rand() % p->getTamanho();
		p2 = p->lista_de_individuos[numero_aleatorio];

	}while(p1.getFitness() == p2.getFitness());

	if(p1.getFitness() < p2.getFitness() && fator_sorte > numero_sorte)
		selecionados_.first = p1;

	else
		selecionados_.first = p2;



	numero_sorte = rand() % 11;


	do{
		numero_aleatorio = rand() % p->getTamanho();

		p1 = p->lista_de_individuos[numero_aleatorio];

	}while(p1.getFitness() == selecionados_.first.getFitness());

	do{
		numero_aleatorio = rand() % p->getTamanho();

		p2 = p->lista_de_individuos[numero_aleatorio];
	}while(p2.getFitness() == selecionados_.first.getFitness() || p1.getFitness() == p2.getFitness());

	if(p1.getFitness() < p2.getFitness() && fator_sorte > numero_sorte)
		selecionados_.second = p1;

	else
		selecionados_.second = p2;


	return selecionados_;

}

