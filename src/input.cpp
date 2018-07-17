/*
 * input.cpp
 *
 *  Created on: 9 de jul de 2018
 *      Author: adamr
 */

#include "input.h"



Input::Input() {

	num_vertices = 0;
}


double Input::euclidian2D(int x1, int y1, int x2, int y2){
	return sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
}

void Input::addCoordenates(int id, int x, int y){

	coordenates[id].first = x;
	coordenates[id].second = y;
}

void Input::build(){

	pair<int,int> v1,v2;

	for(unsigned int i = 0; i < num_vertices; i++){
		for(unsigned int j = 0; j < num_vertices; j++){
			v1 = coordenates[i];
			v2 = coordenates[j];

			distance_matrix[i][j] = euclidian2D(v1.first, v1.second,
													v2.first, v2.second);
		}
	}
}



void Input::load(string name){

	//TODO: Não deixar informação fixa, mudar para name
	ifstream file("eil22.txt");

	if( file.is_open() ){

		while(file >> reader){

					if(reader == "DIMENSION"){

						file >> reader; // :
						file >> num_vertices;

						coordenates.resize( num_vertices );
						distance_matrix.resize( num_vertices, vector<double>(num_vertices) );
					}

					if(reader == "NODE_COORD_SECTION"){
						int id, x, y;

						for(unsigned int i = 0; i < num_vertices; i++){

							file >> id >> x >> y;

							addCoordenates(id-1,x,y);

						}

						build();
					}


		}

		file.close();
	}

}

