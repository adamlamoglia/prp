/*
 * aresta.h
 *
 *  Created on: 12 de mai de 2018
 *      Author: adamr
 */

#ifndef ARESTA_H_
#define ARESTA_H_

using namespace std;

#include <cmath>

class Aresta {
private:

public:
     int vertice_origem;
	int vertice_destino;
	double peso_;
	Aresta(int u,int v,double w);
	Aresta();

};

#endif /* ARESTA_H_ */
