#ifndef PARAMETROS_H_
#define PARAMETROS_H_
//#include <omp.h>
#include <getopt.h>
#include <iostream>
#include <string>
#include <map>
using namespace std;

class Parametros {
    public:
		Parametros();
		static void Store(int ac, char * av[]);

		static string getInstance();
		static double getAlphaMax();
		static double getBetaMax();
		static int getGenerations();
		static double getProbability();
		static int getPopulationSize();
		static double getLuckyFactor();
		static int getLuckyRange();
		static int getMutationRange();
		static int getSelectionType();
		static int getCrossoverType();
		static int getMutationType();
		static int getInsertionType();
		static int getNumberVehicles();
		static int getInitType();
		static int getFitFactor();
		static int getEra();
		static int getIdleIterations();
		static int getIterations();
		static double getSeed();

		


    private:
		static map<string,string> vm;
};

#endif /* PARAMETER_H_ */
