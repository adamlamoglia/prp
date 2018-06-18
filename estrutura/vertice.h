/*
 * vertice.h
 *
 *  Created on: 14 de mai de 2018
 *      Author: adamr
 */

#ifndef VERTICE_H_
#define VERTICE_H_

class Vertice {
private:
	int id_;
	int x_;
	int y_;

public:
	Vertice(int id, int x, int y);
	Vertice();
	int getId();
	int getX();
	int getY();
};

#endif /* VERTICE_H_ */
