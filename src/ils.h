#include "individuo.h"
#include "statistic.h"
#include <algorithm>
#include <utility>
#include <unistd.h>

using namespace std;

class Ils{
    private:

    public:

        Ils(int init_type, int mutation_type, int fit_factor, int maxIdleIterations, 
            int maxIterations, double rr_factor, int strategy);

        //Input object
        Input *in;

        Individuo a,
                  b;

        //Parameters 
        int init_type,
            mutation_type,
            fit_factor;
            
        double rr_factor;

        //Ils atributes
        int maxIterations,
            maxIdleIterations,
            random_node,
            strategy;

        int node1,
            node2,
            vehicle1,
            vehicle2;

        bool improvement,
             lsImprovement;

        //Structure for possibilities in Creation of solution
        struct Insertion{
		    int vehicle;
		    int index;
		    int cost;
	    };

        vector<Insertion> permutations;

        //Creation atributes
        vector<int> nodes_inserted,
                    nodes_visited,
                    nodes_removed;

        //two Opt atributes
        int delta,
            best_i,
            best_k,
            best_delta,
            global_improvement,
            local_improvement,
            lowest_fitness,
            current_value,
            new_value,
            current1,
            current2,
            current3,
            current4,
            current5,
            change1,
            change2,
            change3,
            change4,
            change5;

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
        void ls(Individuo &s);
        void lsTokenRing(Individuo &s);
        void lsLinearUnion(Individuo &s);
        void lsMovementUnion(Individuo &s);
        void twoOptBest(Individuo &s);
        void threeOptBest(Individuo &s);
        void ruinAndRecreate(Individuo &s);
        int delta2Evaluation(Individuo &s, int vehicle, int i, int k);
        int delta3Evaluation(Individuo &s, int vehicle, int i, int j, int k);
        int calculatePartialRoute(Individuo &s, int vehicle, int i, int k);
        void swapNodes(Individuo &s, int vehicle, int i, int k);
        int searchVehicle(Individuo &s, int node);
        int searchNode(Individuo &s, int node);
        bool isRemoved(Individuo&s);
        
        

        //Perturbation functions
        void perturbation(Individuo &s, int level);
        void swap2Nodes(Individuo &s);
        void scramble(Individuo &s);
        void invert(Individuo &s);
        void chooseNodes(Individuo &s);
        void swapNodesCapacity(Individuo &s, int vehicle1, int vehicle2, int i, int k);
        bool capacityIsSatisfied(Individuo &s, int vehicle1, int vehicle2, int i, int k);
        int calculatePartialDiffRoute(Individuo &s, int vehicle1, int vehicle2, int i, int k);

        //Print out functions
        void showResult();

};
