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
#include <string>
#include <cmath>
#include <iomanip>

using namespace std;

class Input {

public:

	unsigned int num_vertices;

    int degree;

	double q1,
		   q2,
		   q3,
		   latitude_x1,
		   longitude_y1,
		   latitude_x2,
		   longitude_y2,
		   min,
		   pi = 3.141592,
		   rrr = 6378.388;



	vector<vector<int> > distance_matrix;

	//Represents the euclidian2D or geo coordinates of vertex i.
	vector<pair<double,double> > coordinates;

	string reader;

	string type;

	Input();

	double euclidian2D(double x1, double y1, double x2, double y2);

	double geo(double x1, double y1, double x2, double y2);

	double setBuild(double x1, double y1, double x2, double y2);

	double computeGeo(double a);

	void load(string name);

	void addCoordenates(int id, double x, double y);

	void build();

	friend ostream& operator>>(ostream& os, ifstream& file);

};


#endif /* INPUT_H_ */
