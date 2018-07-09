/*
 * evolucao.cpp
 *
 *  Created on: 15 de mai de 2018
 *      Author: adamr
 */

#include "evolucao.h"


Evolucao::Evolucao(Grafo *g) {

	populacao_ = new Populacao(g,500);
	seletor_ = new Selecao(5);
	operador_crossover = new Cruzamento(populacao_,g->getQuantidadeVertices()/2);
	operador_mutacao = new Mutacao(populacao_);

	alfa_maximo = 1000;
	beta_maximo = 10;
	numero_geracoes = 0;

}

void Evolucao::realizarOperacaoGenetica(){
	int alfa,beta;
	float indice_mutacao_aleatorio;
	int indice_individuo_comparacao;
	double melhor_fitness;
	alfa = beta = 0;

	populacao_->gerarPrimeiraGeracao();
	numero_geracoes++;


	while(numero_geracoes <= 100){
		alfa = 0;
		beta = 0;

		while(alfa < alfa_maximo and beta < beta_maximo){

			melhor_fitness = populacao_->lista_de_individuos[0].getFitness();


			pais_ = seletor_->selecionarPorTorneioBinario(populacao_);
			pais_.first.calcularFitnessIndividual();
			pais_.second.calcularFitnessIndividual();

			filhos_ = operador_crossover->cruzarPorCorteDeUmPonto(pais_);
			filhos_.first.calcularFitnessIndividual();
			filhos_.second.calcularFitnessIndividual();


			indice_mutacao_aleatorio = rand() % 100;

			indice_mutacao_aleatorio *= 0.01;

			if(indice_mutacao_aleatorio < 0.8){


				filhos_.first.veiculo_->rota_ = operador_mutacao->doisOpt(filhos_.first.veiculo_->rota_);
				filhos_.first.calcularFitnessIndividual();


				filhos_.second.veiculo_->rota_ = operador_mutacao->doisOpt(filhos_.second.veiculo_->rota_);
				filhos_.second.calcularFitnessIndividual();

				//indice de comparacao povoado: individuos entre 250 e 500
				indice_individuo_comparacao = rand() % populacao_->getTamanho()/2 + populacao_->getTamanho()/2;



				if(!populacao_->procurarIndividuoPorFitness(filhos_.first.getFitness()) &&
						filhos_.first.getFitness() <
						populacao_->lista_de_individuos[indice_individuo_comparacao].getFitness()){

						populacao_->lista_de_individuos[indice_individuo_comparacao] = filhos_.first;

				}

				//indice de comparacao elitizado: individuos entre 0 e 250
				indice_individuo_comparacao = rand() % populacao_->getTamanho()/2;

				if(!populacao_->procurarIndividuoPorFitness(filhos_.second.getFitness()) &&
						filhos_.second.getFitness() <
						populacao_->lista_de_individuos[indice_individuo_comparacao].getFitness()){

						populacao_->lista_de_individuos[indice_individuo_comparacao] = filhos_.second;
				}

				alfa++;

			}

			populacao_->calcularFitness();
			populacao_->ordenarIndividuos();



			if(populacao_->lista_de_individuos[0].getFitness() == melhor_fitness)
				beta++;

		}

		numero_geracoes++;
	}

	populacao_->imprimirRotaFitness();

}


