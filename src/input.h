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
	//Represents the dimension of graph.
	unsigned int num_vertices;

	//Represents the distance between vertex i to j.
	vector<vector<double> > distance_matrix;

	//Represents the euclidian2D coordinates of vertex i.
	vector<pair<int,int> > coordinates;

	//Used in build() to read strings in file.
	string reader;

	Input();

	double euclidian2D(int x1, int y1, int x2, int y2);
	void load(const char* name);
	void addCoordenates(int id, int x, int y);
	void build();

};


#endif /* INPUT_H_ */
