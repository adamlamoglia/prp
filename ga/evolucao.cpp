/*
 * evolucao.cpp
 *
 *  Created on: 15 de mai de 2018
 *      Author: adamr
 */

#include "evolucao.h"


Evolucao::Evolucao(Parametros *p,Grafo *g) {

	this->p = p;

	populacao_ = new Populacao(g,p->getTamanhoPopulacao());
	seletor_ = new Selecao(p->getFatorDeSorte());
	operador_crossover = new Cruzamento(populacao_,p->getTamanhoCorte());
	operador_mutacao = new Mutacao(populacao_);

	alfa_maximo = p->getAlfa();
	beta_maximo = p->getBeta();
	numero_geracoes = 0;

}

void Evolucao::operacaoGenetica(){
	int alfa,beta;
	float indice_mutacao_aleatorio;
	int indice_individuo_comparacao;
	double melhor_fitness;
	alfa = beta = 0;

	populacao_->gerarPrimeiraGeracao();
	numero_geracoes++;

	while(numero_geracoes <= p->getNumeroLimiteGeracoes()){

		while(alfa < alfa_maximo and beta < beta_maximo){

			melhor_fitness = populacao_->lista_de_individuos[0].getFitness();

			pais_ = seletor_->selecionarPorTorneioBinario(populacao_);

			filhos_ = operador_crossover->cruzarPorCorteDeUmPonto(pais_);

			indice_mutacao_aleatorio = rand() % 100;

			indice_mutacao_aleatorio *= 0.01;

			if(indice_mutacao_aleatorio < p->getProbabilidadeMutacao()){

				//TODO: mudar classe "veiculo" para rota ser um atributo privado!
				filhos_.first.veiculo_->rota_ = operador_mutacao->doisOpt(filhos_.first.veiculo_->rota_);
				filhos_.first.setFitness(populacao_->calcularFitness(filhos_.first.veiculo_->rota_));

				filhos_.second.veiculo_->rota_ = operador_mutacao->doisOpt(filhos_.second.veiculo_->rota_);
				filhos_.second.setFitness(populacao_->calcularFitness(filhos_.second.veiculo_->rota_));

				//FILHO 1
				indice_individuo_comparacao = rand() % populacao_->getTamanho()/2 + populacao_->getTamanho();

				if(!populacao_->procurarIndividuoPorFitness(filhos_.first.getFitness()) &&
						filhos_.first.getFitness() <
						populacao_->lista_de_individuos[indice_individuo_comparacao].getFitness()){
					populacao_->lista_de_individuos[indice_individuo_comparacao] = filhos_.first;
				}

				//FILHO 2
				indice_individuo_comparacao = rand() % populacao_->getTamanho()/2 + populacao_->getTamanho();

				if(!populacao_->procurarIndividuoPorFitness(filhos_.second.getFitness()) &&
						filhos_.second.getFitness() <
						populacao_->lista_de_individuos[indice_individuo_comparacao].getFitness()){
						populacao_->lista_de_individuos[indice_individuo_comparacao] = filhos_.second;
						//alfa++;
				}

				alfa++;
			}

			populacao_->ordenarIndividuos();
			if(populacao_->lista_de_individuos[0].getFitness() == melhor_fitness)
				beta++;

		}
	}

}


