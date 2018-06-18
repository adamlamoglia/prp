/*
 * parametros.cpp
 *
 *  Created on: 12 de mai de 2018
 *      Author: adamr
 */

#include "parametros.h"

Parametros::Parametros() {

}

int Parametros::getQuantidadeVeiculos(){
	return quantidade_veiculos;
}

int Parametros::getQuantidadeVertices(){
	return quantidade_vertices;
}

int Parametros::getTamanhoPopulacao(){
	return tamanho_populacao;
}

int Parametros::getAlfa(){
	return alfa_;
}

int Parametros::getBeta(){
	return beta_;
}

int Parametros::getNumeroLimiteGeracoes(){
	return numero_limite_geracoes;
}

float Parametros::getFatorDeSorte(){
	return fator_sorte;
}

int Parametros::getTamanhoCorte(){
	return tamanho_corte;
}

int Parametros::getProbabilidadeMutacao(){
	return probabilidade_mutacao;
}

void Parametros::setAlfa(int alfa) {
	alfa_ = alfa;
}

void Parametros::setBeta(int beta) {
	beta_ = beta;
}

float Parametros::getFatorSorte(){
	return fator_sorte;
}

void Parametros::setFatorSorte(float fatorSorte) {
	fator_sorte = fatorSorte;
}

void Parametros::setNumeroLimiteGeracoes(int numeroLimiteGeracoes) {
	numero_limite_geracoes = numeroLimiteGeracoes;
}

void Parametros::setProbabilidadeMutacao(int probabilidadeMutacao) {
	probabilidade_mutacao = probabilidadeMutacao;
}

void Parametros::setQuantidadeVeiculos(int quantidadeVeiculos) {
	quantidade_veiculos = quantidadeVeiculos;
}

void Parametros::setQuantidadeVertices(int quantidadeVertices) {
	quantidade_vertices = quantidadeVertices;
}

void Parametros::setTamanhoCorte(int tamanhoCorte) {
	tamanho_corte = tamanhoCorte;
}

void Parametros::setTamanhoPopulacao(int tamanhoPopulacao) {
	tamanho_populacao = tamanhoPopulacao;
}
