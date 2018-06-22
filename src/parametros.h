/*
 * parametros.h
 *
 *  Created on: 12 de mai de 2018
 *      Author: adamr
 */

#ifndef PARAMETROS_H_
#define PARAMETROS_H_

class Parametros {
private:


public:
	int quantidade_vertices;
	int quantidade_veiculos;
	int id_vertice;
	int x_vertice;
	int y_vertice;

	Parametros();

	int getQuantidadeVeiculos();
	int getQuantidadeVertices();
	int getIdVertice();
	int getX();
	int getY();

};

#endif /* PARAMETROS_H_ */
