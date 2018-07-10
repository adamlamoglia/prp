/*
 * input.cpp
 *
 *  Created on: 9 de jul de 2018
 *      Author: adamr
 */

#include "input.h"



Input::Input() {

	quantidade_vertices = 0;
}

Input::~Input(){

}

double Input::calcularDistanciaEuclidiana2D(int x1, int y1, int x2, int y2){
	return sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
}

void Input::adicionarCoordenada(int id, int x, int y){

	coordenadas_vertices[id].first = x;
	coordenadas_vertices[id].second = y;
}

void Input::construirMatrizDeDistancias(){
	pair<int,int> vertice1,vertice2;

	for(unsigned int i = 0; i < quantidade_vertices; i++){
		for(unsigned int j = 0; j < quantidade_vertices; j++){
			vertice1 = coordenadas_vertices[i];
			vertice2 = coordenadas_vertices[j];

			matriz_distancias[i][j] = calcularDistanciaEuclidiana2D(vertice1.first, vertice1.second,
																		vertice2.first, vertice2.second);
		}
	}
}



void Input::lerArquivo(){

	ifstream arquivo_("eil22.txt");

	if( arquivo_.is_open() ){

		while(arquivo_ >> leitor_arquivo){

					if(leitor_arquivo == "DIMENSION"){

						arquivo_ >> leitor_arquivo; // :
						arquivo_ >> quantidade_vertices;

						coordenadas_vertices.resize( quantidade_vertices );
						matriz_distancias.resize( quantidade_vertices, vector<double>(quantidade_vertices) );
					}

					if(leitor_arquivo == "NODE_COORD_SECTION"){
						int id, x, y;

						for(unsigned int i = 0; i < quantidade_vertices; i++){

							arquivo_ >> id >> x >> y;

							adicionarCoordenada(id-1,x,y);

						}

						construirMatrizDeDistancias();
					}


		}

		arquivo_.close();
	}

}

