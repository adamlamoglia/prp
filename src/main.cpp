//============================================================================
// Name        : prp2.cpp
// Author      : adamlamoglia
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {

	ifstream arquivo_("att48.txt");
	string leitor_;

	if(arquivo_.is_open()){

		while(arquivo_ >> leitor_){
			cout << leitor_ << endl;

			if(leitor_ == "DIMENSION"){
				arquivo_ >> leitor_; // :

			}
		}

		arquivo_.close();
	}
}
