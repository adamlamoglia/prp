//============================================================================
// Name        : prp2.cpp
// Author      : adamlamoglia
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <string>
#include "parametros.h"
#include "../ga/evolucao.h"

using namespace std;

int main() {

	ifstream arquivo_("eil22.txt");
	string leitor_;
	Parametros p;
	Grafo *grafo_;
	Evolucao *operador_genetico;

	if(arquivo_.is_open()){

		while(arquivo_ >> leitor_){

			if(leitor_ == "DIMENSION"){
				arquivo_ >> leitor_; // :
				arquivo_ >> p.quantidade_vertices;

				grafo_ = new Grafo(p.quantidade_vertices);
				grafo_->setQuantidadeVeiculos(1);
			}

			if(leitor_ == "NODE_COORD_SECTION"){

				for(int i = 0; i < p.quantidade_vertices; i++){

					arquivo_ >> p.id_vertice; // id do vertice
					arquivo_ >> p.x_vertice; // x
					arquivo_ >> p.y_vertice; // y

					grafo_->adicionarVerticeNaLista(p.id_vertice - 1, p.x_vertice,  p.y_vertice);
				}

				grafo_->adicionarVerticesNoGrafo(); // constroi arestas
			}


		}
		arquivo_.close();

	}

	//grafo_->imprimeMatrizAdjacencia();

	operador_genetico = new Evolucao(grafo_);

	operador_genetico->realizarOperacaoGenetica();

	//cout << operador_genetico->populacao_->lista_de_individuos[0].getFitness() << endl;

}
