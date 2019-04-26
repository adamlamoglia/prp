using namespace std;

#include "individuo.h"

class Statistic{

    private:

    public:
            double mean,
                   std_deviation;
            
            int best,
                worst,
                repeated,
                mode;
            

            Statistic();

            void calculateAll(vector<Individuo> &s);
            
            void mean(vector<Individuo> &s);
            void standardDeviation(vector<Individuo> &s);
            void mode(vector<Individuo> &s);
            void countRepeated(vector<Individuo> &s);

};