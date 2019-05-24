#include "individuo.h"
#include "statistic.h"
#include <algorithm>
#include <utility>
#include <unistd.h>

using namespace std;

class Ils{
    private:

    public:

        Ils(int init_type, int mutation_type, int fit_factor, int maxIdleIterations);

        //Input object
        Input *in;

        //Parameters 
        int init_type,
            mutation_type,
            fit_factor;

        //Ils atributes
        int maxIterations,
            maxIdleIterations,
            random_node;

        int node1,
            node2,
            vehicle1,
            vehicle2;

        bool improvement;

        //Structure for possibilities in Creation of solution
        struct Insertion{
		    int vehicle;
		    int index;
		    int cost;
	    };

        vector<Insertion> permutations;

        //Creation atributes
        vector<int> nodes_inserted,
                    nodes_visited;

        //two Opt atributes
        int delta,
            best_i,
            best_k,
            best_delta,
            global_improvement,
            local_improvement,
            lowest_fitness,
            current_value,
            new_value;

        //Ils function
        void run();
        
        //Initialization functions
        void create(Individuo &s);
        void initialization(Individuo &s, int node);
        void cheapestInit(Individuo &s, int node);
        void randomCheapestInit(Individuo &s, int node);
        void computePossibilities(Individuo &s, int node);
        bool clientsServed();
        bool clientsChecked();

        //Local search functions
        void twoOptBest(Individuo &s);
        void localSearch(Individuo &s);
        int deltaEvaluation(Individuo &s, int vehicle, int i, int k);
        int calculatePartialRoute(Individuo &s, int vehicle, int i, int k);
        void swapNodes(Individuo &s, int vehicle, int i, int k);
        

        //Perturbation functions
        void perturbation(Individuo &s);
        void swap2Nodes(Individuo &s);
        void scramble(Individuo &s);
        void invert(Individuo &s);
        void chooseNodes(Individuo &s);
        void swapNodes2(Individuo &s, int vehicle1, int vehicle2, int i, int k);
        bool capacityIsSatisfied(Individuo &s, int vehicle1, int vehicle2, int i, int k);
        int calculatePartialDiffRoute(Individuo &s, int vehicle1, int vehicle2, int i, int k);

        //Print out functions
        void showResult();

};
