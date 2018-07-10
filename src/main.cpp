//============================================================================
// Name        : pollutionRoutingProblem.cpp
// Author      : adamlamoglia
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "Parametros/parametros.h"
#include "input.h"
//#include "ga.h"

using namespace std;

int main(int argc, char ** argv  ) {

	//srand(time(NULL));

	//if(argc > 1)

	/*TODO Utilizar a Classe Parametros e deixar que ela cuide da entrada dos dados*/
	Parametros::Store(ac, av);

	Input in;
	
	/*TODO: Implementar o carregamento dos arquivos de entrada atraves da Classe Parametro*/
	in.load(Parametros::getInstance());

	//in.lerArquivo();

	/*TODO: Nao deixar informacoes fixas no codigo. Esse eh um mal habito de programacao
		que pode ser levado para a vida toda se voce ficar mal acostumado */
	Genetic ga(&in,Parametros::getMaxIterations(), Parametros::getMaxIdleIterations());
	//Ga operador_genetico(&in, 10, 10, 100, 0.8, 500);

//	operador_genetico.realizarOperacaoGenetica();

	/*TODO: de preferencia para nomes mais curtos e em ingles*/
	ga.run();

	return 0;

}
