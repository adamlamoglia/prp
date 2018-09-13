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

		//Retrive informations
		static string getInstance();
		static double getAlphaMax();
		static string getNeighborhood();
		static int getMaxIterations();
		static int getMaxIdleIterations();
		static int GetSize();
		static string GetVersion();
		static double GetSeed();

		///////////// ADAM FUNCTIONS ///////////////

		static string getName();
		static string getComment();
		static string getType();
		static int getDimension();
		static string getWeightType();
		static double getCapacity();

		static double getAlfa();
		static double getBeta();
		static int getGenerations();
		static double getProbability();
		static int getPopulationSize();
		static double getLuckyFactor();


    private:
		static map<string,string> vm;
};

#endif /* PARAMETER_H_ */
