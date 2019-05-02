#include "statistic.h"


Statistic::Statistic(){

    mean = std_deviation = best = worst = repeated = mode = 0;

    o = Output();
}

void Statistic::calculateAll(vector<Individuo> &s){

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

    int aux_fitness;

    for(int i = 0; i < s.size(); i++){
        
        aux_fitness = s[i].getFitness();

        for(int j = i + 1; j < s.size(); j++){

            if(aux_fitness == s[i].getFitness())
                repeated++;
        }
    }
}


void Statistic::calculateMode(vector<Individuo> &s){

    for(int i = 0; i < s.size(); i++)
        values[s[i].getFitness()]++;
    
    for(int i = 0; i < s.size(); i++){
        
       if(values[s[i].getFitness()] > mode)
        mode = values[s[i].getFitness()];
    }

}

void Statistic::standardDeviation(vector<Individuo> &s){

    for(int i = 0; i < s.size(); i++)
        std_deviation += (s[i].getFitness() - mean)*(s[i].getFitness() - mean);
    
    std_deviation /= s.size();
}

void Statistic::printStatistics(){
    
}