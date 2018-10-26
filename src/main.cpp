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

		Parametros::Store(argc, argv);

		in.load(Parametros::getInstance());

		//cout << "GA for one vehicle, " << Parametros::getGenerations() << " generations" << endl;

		Genetic ga(&in, 
			Parametros::getAlphaMax(),			// Standard: 300
			Parametros::getBetaMax(),			// Standard: 3000
			Parametros::getGenerations(), 		// Standard: 100
			Parametros::getProbability(),		// Standard: 25.4
			Parametros::getPopulationSize(),	// Standard: 30
			Parametros::getLuckyFactor(),		// Standard: 997
			Parametros::getLuckyRange(),		// Standard: 1000
			Parametros::getMutationRange(), 	// Standard: 100
			Parametros::getSelectionType(), 	// Standard: 1
			Parametros::getCrossoverType(),		// Standard: 1
			Parametros::getMutationType(),		// Standard: 1
			Parametros::getInsertionType()); 	// Standard: 1

		ga.run();
		ga.showResult();
	}
	else
		cout << "error: missing file" << endl;




	return 0;

}
