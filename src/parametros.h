/*
 * parametros.h
 *
 *  Created on: 12 de mai de 2018
 *      Author: adamr
 */

#ifndef PARAMETROS_H_
#define PARAMETROS_H_

class Parametros {
private:
	int quantidade_vertices;
	int quantidade_veiculos;
	int tamanho_populacao;
	int alfa_;
	int beta_;
	int numero_limite_geracoes;
	float fator_sorte;
	int tamanho_corte;
	int probabilidade_mutacao;

public:
	Parametros();

	int getQuantidadeVeiculos();
	int getQuantidadeVertices();
	int getTamanhoPopulacao();
	int getAlfa();
	int getBeta();
	int getNumeroLimiteGeracoes();
	float getFatorDeSorte();
	int getTamanhoCorte();
	int getProbabilidadeMutacao();
	float getFatorSorte();

	void setAlfa(int alfa);
	void setBeta(int beta);
	void setFatorSorte(float fatorSorte);
	void setNumeroLimiteGeracoes(int numeroLimiteGeracoes);
	void setProbabilidadeMutacao(int probabilidadeMutacao);
	void setQuantidadeVeiculos(int quantidadeVeiculos);
	void setQuantidadeVertices(int quantidadeVertices);
	void setTamanhoCorte(int tamanhoCorte);
	void setTamanhoPopulacao(int tamanhoPopulacao);
};

#endif /* PARAMETROS_H_ */
