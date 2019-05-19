#include "statistic.h"


Statistic::Statistic(){

    mean = std_deviation = best = worst = mode.first = mode.second = 0;

    o = Output();
}

void Statistic::calculateAll(vector<Individuo> &s){

    mean = std_deviation = best = worst = 0;

    setBest(s[0].getFitness());
    setWorst(s);
    calculateMean(s);
    calculateMode(s);
    countRepeated(s);
    standardDeviation(s);
}

void Statistic::calculateMean(vector<Individuo> &s){

    for(int i = 0; i < s.size(); i++){
        mean += s[i].getFitness();
    }

    mean /= s.size();
}

void Statistic::countRepeated(vector<Individuo> &s){

}


void Statistic::calculateMode(vector<Individuo> &s){

    for(int i = 0; i < s.size(); i++)
            values[s[i].getFitness()] = 0;

    for(int i = 0; i < s.size(); i++)
        values[s[i].getFitness()]++;
    
    for(int i = 0; i < s.size(); i++){
        
       if(values[s[i].getFitness()] > mode.second){
            mode.first  = s[i].getFitness();
            mode.second = values[s[i].getFitness()];
       }

    }

}

void Statistic::standardDeviation(vector<Individuo> &s){

    for(int i = 0; i < s.size(); i++)
        std_deviation += (s[i].getFitness() - mean)*(s[i].getFitness() - mean);
    
    std_deviation /= s.size();
    std_deviation = sqrt(std_deviation);
}

void Statistic::setBest(int best){
    this->best = best;
}

void Statistic::setWorst(vector<Individuo> &s){

    for(int i = 0; i < s.size(); i++){

        if(s[i].getFitness() > worst)
            worst = s[i].getFitness();
    }
}

void Statistic::printStatistics(){
    
    cout << "Best: " << best << endl;
    cout << "Worst: " << worst << endl;
    cout << "Mean: " << mean << endl;
    cout << "Standard Deviation: " << std_deviation << endl;
    cout << "Mode: " << mode.first << endl;
    cout << "Number of repetitions: " << mode.second << endl;
    cout << endl;

}

void Statistic::printBestAndWorst(){

    cout << best << "\t" << worst << endl;
}