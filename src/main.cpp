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
		in.load(argv[1]);

		cout << "GA for one vehicle, " << Parametros::getGenerations() << " generations" << endl;

		Genetic ga(&in, Parametros::getAlfa(), Parametros::getBeta(), Parametros::getGenerations()
					, Parametros::getProbability(), Parametros::getPopulationSize(), Parametros::getLuckyFactor());

		ga.run();
		ga.showResult();
	}
	else
		cout << "error: missing file" << endl;




	return 0;

}
