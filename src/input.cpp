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


double Input::euclidian2D(double x1, double y1, double x2, double y2){
	return sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
}

double Input::geo(double x1, double y1, double x2, double y2){

	latitude_x1 = computeGeo(x1);
	longitude_y1 = computeGeo(y1);
	latitude_x2 = computeGeo(x2);
	longitude_y2 = computeGeo(y2);

	q1 = cos(longitude_y1 - longitude_y2);
	q2 = cos(latitude_x1 - latitude_x2);
	q3 = cos(latitude_x1 + latitude_x2);

	return (rrr * acos( 0.5 * ( (1+q1) * q2 - (1 - q1) * q3) ) + 1);
}

double Input::computeGeo(double a){

	deg = (int) a;
	min = a - deg;

	return (pi * (deg + 5 * min / 3) / 180);
}

void Input::addCoordenates(int id, double x, double y){

	coordinates[id].first = x;
	coordinates[id].second = y;
}

double Input::setBuild(double x1, double y1, double x2, double y2){

	if(type == "EUC_2D")
		return euclidian2D(x1,y1,x2,y2);

	return geo(x1,y1,x2,y2);
}

void Input::build(){

	pair<double,double> v1,v2;

	if(type == "EUC_2D"){

			for(unsigned int i = 0; i < num_vertices; i++){
				for(unsigned int j = 0; j < num_vertices; j++){
					v1 = coordinates[i];
					v2 = coordinates[j];

					distance_matrix[i][j] = 
					distance_matrix[j][i] = round(setBuild(v1.first, v1.second,
													v2.first, v2.second));
						
				}
			}

			return;
	}

	if(type == "GEO"){

		for(unsigned int i = 0; i < num_vertices; i++){
			for(unsigned int j = 0; j < num_vertices; j++){
				v1 = coordinates[i];
				v2 = coordinates[j];

				distance_matrix[i][j] = (int) setBuild(v1.first, v1.second,
												v2.first, v2.second);
												
				distance_matrix[j][i] = (int) setBuild(v2.first, v2.second,
												v1.first, v1.second);
			}
		}

		return;
	}


}



void Input::load(string name){

	ifstream file(name.c_str());


	if( file.is_open() ){

		while(file >> reader){

					if(reader == "DIMENSION"){

						file >> reader; // :
						file >> num_vertices;

						coordinates.resize( num_vertices );
						distance_matrix.resize( num_vertices, vector<int>(num_vertices) );
					}

					if(reader == "EDGE_WEIGHT_TYPE"){

						file >> reader; // :
						file >> type;

					}

					if(reader == "NODE_COORD_SECTION"){
						int id;
						double x,
							   y;

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

