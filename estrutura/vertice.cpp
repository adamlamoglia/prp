/*
 * vertice.cpp
 *
 *  Created on: 14 de mai de 2018
 *      Author: adamr
 */

#include "vertice.h"

Vertice::Vertice(int id, int x, int y) {

	id_ = id;
	x_ = x;
	y_ = y;

}

Vertice::Vertice(){

}

int Vertice::getId(){
	return id_;
}

int Vertice::getX(){
	return x_;
}


int Vertice::getY(){
	return y_;
}

