/*
 * grafo.cpp
 *
 *  Created on: 12 de mai de 2018
 *      Author: adamr
 */

#include "grafo.h"


Grafo::Grafo(int quantidade_vertices) {
	this->quantidade_vertices = quantidade_vertices;
	contador_de_arestas = 0;

	lista_de_adjacencia.resize(quantidade_vertices, vector<int>(quantidade_vertices,-1));
	lista_de_vertices.resize(quantidade_vertices);
	lista_de_arestas.resize(quantidade_vertices*(quantidade_vertices - 1)/2);

}

int Grafo::getQuantidadeVertices(){
	return quantidade_vertices;
}

int Grafo::calculoDoPeso(int x1,int x2,int y1, int y2){
	return sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
}

void Grafo::adicionarVerticeNaLista(int id, int x, int y){

	lista_de_vertices[id] = new Vertice(id, x, y);

}

void Grafo::adicionarVerticesNoGrafo(){


	for(int i = 0; i < getQuantidadeVertices(); i++)
		for(int j = 0; j < getQuantidadeVertices(); j++)
			if(i != j)
				adicionarAresta(lista_de_vertices[i], lista_de_vertices[j]);
}


void Grafo::adicionarAresta(Vertice* u, Vertice* v){

	lista_de_adjacencia[u->getId()][v->getId()] = calculoDoPeso(u->getX(),v->getX(),u->getY(),v->getY());

}

int Grafo::getQuantidadeVeiculos(){
	return quantidade_veiculos;
}

void Grafo::setQuantidadeVeiculos(int quantidadeVeiculos) {
	quantidade_veiculos = quantidadeVeiculos;
}
