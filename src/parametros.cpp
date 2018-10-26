#include "parametros.h"

Parametros::Parametros() {
	// nothing to do here!
}

// Attributes* of article "A Genetic Algorithm for a Green Vehicle Routing Problem (2018)"

//GA-VRP1
// PopulationSize = 30,
//ProbabilityOfMutation = 0.1,
//αmax = 300,
//βmax = 3000

// GA-VRP2
//PopulationSize = 50,
//ProbabilityOfMutation = 0.05,
//αmax = 300,
//βmax = 1500

// Missing information: Number of generations (iterations)
// LuckyFactor ensures greater randomness in the solution space. It are used in binaryTour() used to select parents.

string Parametros::getInstance(){
	
	try {
		return vm["instance"];
	} catch (exception& e) {
		//cout << "error: " << e.what() << endl;
		vm["instance"] = "0";
		return vm["instance"];
	}
}

double Parametros::getSeed(){

	try {
		return stod(vm["seed"]);
	} catch (exception& e) {
		//cout << "error: " << e.what() << endl;
		vm["seed"] = "0";
		return stod( vm["seed"]);
	}
}

double Parametros::getAlphaMax(){

	try {
		return stod(vm["alpha"]);
	} catch (exception& e) {
		//cout << "error: " << e.what() << endl;
		vm["alpha"] = "300";
		return stod( vm["alpha"]);
	}
}

double Parametros::getBetaMax(){

	try {
		return stod(vm["beta"]);
	} catch (exception& e) {
		//cout << "error: " << e.what() << endl;
		vm["beta"] = "3000";
		return stod( vm["beta"]);
	}
}

int Parametros::getGenerations(){

	try {
		return stoi(vm["gens"]);
	} catch (exception& e) {
		//cout << "error: " << e.what() << endl;
		vm["gens"] = "100";
		return stoi( vm["gens"]);
	}
}

double Parametros::getProbability(){

	try {
		return stod(vm["prob"]);
	} catch (exception& e) {
		//cout << "error: " << e.what() << endl;
		vm["prob"] = "25.4";
		return stod( vm["prob"]);
	}
}

int Parametros::getPopulationSize(){

	try {
		return stod(vm["psize"]);
	} catch (exception& e) {
		//cout << "error: " << e.what() << endl;
		vm["psize"] = "30";
		return stod( vm["psize"]);
	}
}

double Parametros::getLuckyFactor(){

	try {
		return stod(vm["luckyFactor"]);
	} catch (exception& e) {
		//cout << "error: " << e.what() << endl;
		vm["luckyFactor"] = "997";
		return stod( vm["luckyFactor"]);
	}
}

int Parametros::getLuckyRange(){

	try {
		return stoi(vm["luckyRange"]);
	} catch (exception& e) {
		//cout << "error: " << e.what() << endl;
		vm["luckyRange"] = "1000";
		return stoi( vm["luckyRange"]);
	}
}

int Parametros::getMutationRange(){

	try {
		return stoi(vm["mutationRange"]);
	} catch (exception& e) {
		//cout << "error: " << e.what() << endl;
		vm["mutationRange"] = "100";
		return stoi( vm["mutationRange"]);
	}
}

int Parametros::getSelectionType(){

	try {
		return stoi(vm["stype"]);
	} catch (exception& e) {
		//cout << "error: " << e.what() << endl;
		vm["stype"] = "1";
		return stoi( vm["stype"]);
	}
}


int Parametros::getCrossoverType(){

	try {
		return stoi(vm["ctype"]);
	} catch (exception& e) {
		//cout << "error: " << e.what() << endl;
		vm["ctype"] = "1";
		return stoi( vm["ctype"]);
	}
}

int Parametros::getInsertionType(){

	try {
		return stoi(vm["itype"]);
	} catch (exception& e) {
		//cout << "error: " << e.what() << endl;
		vm["itype"] = "1";
		return stoi( vm["itype"]);
	}
}

int Parametros::getMutationType(){

	try {
		return stoi(vm["mtype"]);
	} catch (exception& e) {
		//cout << "error: " << e.what() << endl;
		vm["mtype"] = "1";
		return stoi( vm["mtype"]);
	}
}



void Parametros::Store(int argc, char * argv[ ]) {

	char optstring[] = "i:a:t:vr:dcq";
	int option_index = 0;
	int opcao = 0;

	struct option long_options[] = {
			{ "instance", required_argument, 0,				001 },
			{ "seed", required_argument, 0,					002 },
			{ "alpha", required_argument, 0,				003 },
			{ "beta"		, required_argument, 0,			004 },
			{ "psize"			, required_argument, 0,		005 },
			{ "luckyFactor"			, required_argument, 0,	006 },
			{ "luckyRange"			, required_argument, 0,	007 },
			{ "mutationRange"		, required_argument, 0,	010 },
			{ "prob"				, required_argument, 0,	011 },
			{ "stype"				, required_argument, 0,	012 },
			{ "ctype"				, required_argument, 0,	013 },
			{ "mtype"				, required_argument, 0,	014 },
			{ "itype"				, required_argument, 0,	015 },
			{ "help", no_argument, 0,						076 },
			{ "h", no_argument, 0,							076 },
			{ 0,0, 0, 0 } };

	opcao = 0;

	while (opcao != -1) {
		opcao = getopt_long(argc, argv, optstring, long_options, &option_index);
		switch (opcao) {

		case 001:
		    vm["instance"] = string(optarg);
			break;
		case 002:
			vm["seed"] = string(optarg);
			break;
		case 003:
			vm["alpha"] = string(optarg);
			break;
		case 004:
			vm["beta"] = string(optarg);
			break;
		case 005:
			vm["psize"] = string(optarg);
			break;
		case 006:
			vm["luckyFactor"] = string(optarg);
			break;
		case 007:
			vm["luckyRange"] = string(optarg);
			break;
		case 010:
			vm["mutationRange"] = string(optarg);
			break;
		case 011:
			vm["prob"] 	= string(optarg);
			break;
		case 012:
			vm["stype"] = string(optarg);
			break;
		case 013:
			vm["ctype"] = string(optarg);
			break;
		case 014:
			vm["mtype"] = string(optarg);
			break;
		case 015:
			vm["itype"] = string(optarg);
			break;
		case 076:
			cout<<"write a help." << endl;
			break;
	}
}

}

map<string,string> Parametros::vm;
