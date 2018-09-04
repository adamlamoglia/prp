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
	vector<vector<double> > distance_matrix;
	vector<pair<int,int> > coordenates;
	string reader;

	Input();

	double euclidian2D(int x1, int y1, int x2, int y2);
	void load(const char* name);
	void addCoordenates(int id, int x, int y);
	void build();

};


#endif /* INPUT_H_ */
