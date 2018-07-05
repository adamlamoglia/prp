/*
 * grafo.h
 *
 *  Created on: 12 de mai de 2018
 *      Author: adamr
 */

#ifndef GRAFO_H_
#define GRAFO_H_

#include <vector>
#include <iostream>
#include "aresta.h"
#include "vertice.h"

using namespace std;

class Grafo {
private:
	int quantidade_vertices;
	int quantidade_veiculos;

public:
	int contador_de_arestas;

	vector<vector<double> > matriz_de_adjacencia;
	vector<Aresta> lista_de_arestas;
	vector<Vertice*> lista_de_vertices;


	Grafo(int quantidade_vertices);
	int getQuantidadeVertices();

	void adicionarVerticeNaLista(int id, int x, int y);
	void adicionarVerticesNoGrafo();
	void adicionarAresta(Vertice* u, Vertice* v);

	double calculoDoPeso(int x1,int x2,int y1, int y2);
	int getQuantidadeVeiculos();
	void setQuantidadeVeiculos(int quantidadeVeiculos);

	void imprimeMatrizAdjacencia();
};

#endif /* GRAFO_H_ */
