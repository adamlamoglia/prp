/*
 * parametros.cpp
 *
 *  Created on: 12 de mai de 2018
 *      Author: adamr
 */

#include "parametros.h"

Parametros::Parametros() {

}

int Parametros::getQuantidadeVeiculos(){
	return quantidade_veiculos;
}

int Parametros::getQuantidadeVertices(){
	return quantidade_vertices;
}

int Parametros::getIdVertice(){
	return id_vertice;
}

int Parametros::getX(){
	return x_vertice;
}

int Parametros::getY(){
	return y_vertice;
}
