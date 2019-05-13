using namespace std;

#include "individuo.h"
#include "output.h"
#include <map>

class Statistic{

    private:

    public:
            double mean,
                   std_deviation;
            
            int best,
                worst;

            map<int,int> values;
            pair<int,int> mode;
            Output o;
            

            Statistic();

            void calculateAll(vector<Individuo> &s);
            void calculateMean(vector<Individuo> &s);
            void standardDeviation(vector<Individuo> &s);
            void calculateMode(vector<Individuo> &s);
            void setBest(int best);
            void setWorst(vector<Individuo> &s);
            void printStatistics();
            void printBestAndWorst(int gen);

};