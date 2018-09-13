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

int main( int argc, char ** argv ) {

	srand(time(NULL));

	if(argc > 1){

		Input in;

		/*TODO Ajeitar a Classe Parametros para o PRP*/
		Parametros::Store(argc, argv);


		/*TODO: Implementar o carregamento dos arquivos de entrada atraves da Classe Parametro*/
		//in.load(Parametros::getInstance().c_str()); //segmentation fault

		in.load(Parametros::getInstance());

		cout << "GA for one vehicle, " << Parametros::getGenerations() << " generations" << endl;

		Genetic ga(&in, 
			Parametros::getAlphaMax(),		// Padrao: 300
			Parametros::getBeta(),			// Padrao: 
			Parametros::getGenerations(), 	// Padrao: 
			Parametros::getProbability(),	// Padrao: 
			Parametros::getPopulationSize(),// Padrao: 
			Parametros::getLuckyFactor());	// Padrao: 

		ga.run();
		ga.showResult();
	}
	else
		cout << "error: missing file" << endl;




	return 0;

}
