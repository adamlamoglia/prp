#include "individuo.h"
#include "statistic.h"
#include <algorithm>
#include <utility>
#include <unistd.h>

using namespace std;

class Ils{
    private:

    public:

        Ils();

        Input *in;

        Individuo best,
                  current,
                  local;

        int maxIterations,
            maxIdleIterations;
        
        bool improvement;

        void run();
        void create();
        void swap2NodesCrossover();
        void localSearch();
        void updateBest();
        void updateCurrent();
        void perturbation();

};
