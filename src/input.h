/*
 * input.h
 *
 *  Created on: 9 de jul de 2018
 *      Author: adamr
 */

#ifndef INPUT_H_
#define INPUT_H_

#include <iostream>
#include <vector>
#include <utility>
#include <fstream>
#include <cmath>

using namespace std;

class Input {

public:
	unsigned int quantidade_vertices;
	vector<vector<double> > matriz_distancias;
	vector<pair<int,int> > coordenadas_vertices;
	string leitor_arquivo;

	Input();
	~Input();

	double calcularDistanciaEuclidiana2D(int x1, int y1, int x2, int y2);
	void lerArquivo();
	void adicionarCoordenada(int id, int x, int y);
	void construirMatrizDeDistancias();

};


#endif /* INPUT_H_ */
