//============================================================================
// Name        : pollutionRoutingProblem.cpp
// Author      : adamlamoglia
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "input.h"
#include "ga.h"

using namespace std;

int main(int argc, char ** argv  ) {

	//srand(time(NULL));

	//if(argc > 1)


	Input in;

	in.lerArquivo();

	Ga operador_genetico(&in, 10, 10, 100, 0.8, 500);

	operador_genetico.realizarOperacaoGenetica();

	return 0;

}
