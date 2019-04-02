/*
 * input.cpp
 *
 *  Created on: 9 de jul de 2018
 *      Author: adamr
 */

#include "input.h"



Input::Input() {

	num_vertices = 0;
	capacity = 9999999;
}

Input* Input::getInstance(){
	return in;
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

	if(edge_type == "EUC_2D")
		return euclidian2D(x1,y1,x2,y2);

	return geo(x1,y1,x2,y2);
}

void Input::buildTsp(){

	pair<double,double> v1,v2;

	if(edge_type == "EUC_2D"){

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

	if(edge_type == "GEO"){

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

void Input::buildAtsp(){

}



void Input::load(string name){

	ifstream file(name.c_str());


	if( file.is_open() ){

		while(file >> reader){

					if(reader == "TYPE"){
						
						file >> reader; // :
						file >> type;
					}

					if(reader == "DIMENSION"){

						file >> reader; // :
						file >> num_vertices;

						coordinates.resize( num_vertices );
						distance_matrix.resize( num_vertices, vector<int>(num_vertices) );
						demand.resize( num_vertices, 0 ); 
					}

					if(reader == "CAPACITY"){

						file >> reader; // :
						file >> capacity;
					}

					if(reader == "EDGE_WEIGHT_TYPE"){

						file >> reader; // :
						file >> edge_type;

					}

					if(reader == "EDGE_WEIGHT_FORMAT"){

						file >> reader; // :
						file >> edge_format;
					}

					if(reader == "NODE_COORD_SECTION" || reader == "EDGE_WEIGHT_SECTION"){
						
						if(edge_format == "FULL_MATRIX"){
						
							for(unsigned int i = 0; i < num_vertices; i++){
								for(unsigned int j = 0; j < num_vertices; j++){
										file >> distance_matrix[i][j];
								}
							}
						}
						
						else{
							
							int id;
							double x,
								y;

							for(unsigned int i = 0; i < num_vertices; i++){

								file >> id >> x >> y;


								addCoordenates(id-1,x,y);

							}
						}


						if(type == "TSP" || type == "CVRP")
							buildTsp();
						
						else if(type == "ATSP" && type != "FULL_MATRIX")
							buildAtsp();
					}

					if(reader == "DEMAND_SECTION"){

						int id,
							client_demand;

						for(unsigned int i = 0; i < num_vertices; i++){
							file >> id >> client_demand;

							demand[id - 1] = client_demand;
						}
						
					}


		}


		file.close();
	}


}

