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

	int seed = time(NULL);
	//int seed = 10;

	srand(seed);

	cout << "seed: " << seed << endl;

	if(argc > 1){

		Input *in = Input::getInstance();

		Parametros::Store(argc, argv);

		in->load(Parametros::getInstance(), seed);

		Genetic ga( 
			
			Parametros::getAlphaMax(),			// Standard: 300
			Parametros::getBetaMax(),			// Standard: 3000
			Parametros::getGenerations(), 		// Standard: 100
			Parametros::getProbability(),		// Standard: 25.4
			Parametros::getPopulationSize(),	// Standard: 30
			Parametros::getLuckyFactor(),		// Standard: 997
			Parametros::getLuckyRange(),		// Standard: 1000
			Parametros::getMutationRange(), 	// Standard: 100
			Parametros::getInitType(), 			// Standard: 1
			Parametros::getSelectionType(), 	// Standard: 1
			Parametros::getCrossoverType(),		// Standard: 1
			Parametros::getMutationType(),		// Standard: 1
			Parametros::getInsertionType(), 	// Standard: 1
			Parametros::getNumberVehicles(),    // Standard: 3
			Parametros::getFitFactor(),  		// Standard: 3
			Parametros::getEra());				// Standard: 10
		
		ga.run();
		ga.showResult();
	}
	else
		cout << "error: missing file" << endl;




	return 0;

}
