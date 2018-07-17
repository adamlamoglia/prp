//============================================================================
// Name        : Pollution Routing Problem
// Author      : adamlamoglia
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "parametros.h"
#include "input.h"
#include "ga.h"

using namespace std;

int main( int argc, char * argv[ ] ) {

	//srand(time(NULL));

	//if(argc > 1)

	/*TODO Utilizar a Classe Parametros e deixar que ela cuide da entrada dos dados*/
	//Parametros::Store(argc, argv);

	Input in;
	
	/*TODO: Implementar o carregamento dos arquivos de entrada atraves da Classe Parametro*/
	in.load(Parametros::getInstance());


	Genetic ga(&in, Parametros::getAlfa(), Parametros::getBeta(), Parametros::getGenerations()
					, Parametros::getProbability(), Parametros::getPopulationSize());

	ga.run();

	return 0;

}
