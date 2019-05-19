#include "ils.h"


Ils::Ils(){

}


void Ils::run(){
    
    int idleIterations = 0,
        iterations = 0;

    do{
        create();

        if(current.getFitness() < best.getFitness())
            best = current;
        
        swap2NodesCrossover();

        if(current.getFitness() < best.getFitness())
            best = current;
        
        do{
            local = current;

            perturbation();
            localSearch();

            if(local.getFitness() < current.getFitness())
                current = local;
            
            if(current.getFitness() < best.getFitness()){
                best = current;
                idleIterations = 0;
                improvement = true;
            }
            else
                idleIterations++;
            
        }while(idleIterations < maxIdleIterations);

    }while(improvement);

}