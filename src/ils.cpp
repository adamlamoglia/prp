#define DEBUG
#include "ils.h"

Ils::Ils(int init_type, int mutation_type, int fit_factor, int maxIdleIterations,
		int maxIterations)
{	
	this->in = Input::getInstance();

	this->maxIterations = maxIterations;
    this->init_type = init_type;
    this->mutation_type = mutation_type;
    this->fit_factor = fit_factor;
    this->maxIdleIterations = maxIdleIterations;

    nodes_inserted.resize(in->num_vertices, false);
	nodes_visited.resize(in->num_vertices, false);

	nodes_visited[0] = true;
    nodes_inserted[0] = true;

}

bool Ils::clientsServed(){

    for (unsigned int i = 1; i < nodes_inserted.size(); i++)
		if(!nodes_inserted[i])
			return false;
	
	return true;
}

bool Ils::clientsChecked(){

    for (unsigned int i = 1; i < nodes_visited.size(); i++)
		if(!nodes_visited[i])
			return false;
	
	return true;

}

void Ils::create(Individuo &s)
{
	s.setFitness(0);

	if(s.route.size() > 0){
		s.route.clear();
			
		s.route.resize(in->num_vertices);

		for(unsigned int j = 0; j < s.fleet.size(); j++)
			s.fleet[j].setCapacity(in->capacity);
	}

    while (!clientsServed())
    {

        for (unsigned int j = 1; j < nodes_visited.size(); j++)
            if (!nodes_inserted[j])
                nodes_visited[j] = false;

        int cont = 0;

        while (!clientsChecked())
        {

            if (cont == 0)
            {
                cont = 1;
            }

            random_node = rand() % in->num_vertices;

            while (nodes_inserted[random_node] || nodes_visited[random_node])
            {
                random_node = rand() % in->num_vertices;
            }

            nodes_visited[random_node] = true;

            initialization(s, random_node);
        }
    }

    s.calculateFitness();

	for (unsigned int j = 1; j < nodes_visited.size(); j++){
		nodes_visited[j]  = false;
		nodes_inserted[j] = false;
	}

	nodes_inserted[0] = true;
	nodes_visited[0]  = true;
        
}

void Ils::initialization(Individuo &s, int node){

    	switch (init_type)
        {

            case 1: 
                cheapestInit(s, node);
            break;

            case 2: 
                randomCheapestInit(s, node);
            break;

            default: 
                randomCheapestInit(s, node);
            break;

        }
}

bool compare(Ils::Insertion &a, Ils::Insertion &b){

	return a.cost < b.cost;
			
}


void Ils::computePossibilities(Individuo &s, int node){

    Insertion possibility;
 
	if(permutations.size() > 0)
		permutations.clear();

	for(int vehicle = 0; vehicle < s.route.size(); vehicle++){

		if(s.fleet[vehicle].getCapacity() - in->demand[node] >= 0){

			//there's no route yet for vehicle to vehicle.size() - 1
			if(s.route[vehicle].size() == 0){
				
				s.setRoute(vehicle, 0);
				s.setRoute(vehicle, 0);
			}


			//take all possibilities for insertion
			for(int i = 1; i < s.route[vehicle].size(); i++){

				possibility.index = i;
				possibility.vehicle = vehicle;
				possibility.cost = in->distance_matrix[ s.route[ vehicle ][ i - 1 ] ][ node ] 
									+ in->distance_matrix[ node ][ s.route[ vehicle ][ i ] ];
				
				permutations.push_back(possibility);
			}

			if(s.route[vehicle].size() == 2)
				break;
		}

	}

	sort(permutations.begin(), permutations.end(), compare);
}

void Ils::cheapestInit(Individuo &s, int node){

    computePossibilities(s, node);

	vector<int>::iterator it = s.route[permutations[0].vehicle].begin() + permutations[0].index;


	s.route[permutations[0].vehicle].insert(it, node);
	s.fleet[permutations[0].vehicle].setCapacity(s.fleet[permutations[0].vehicle].getCapacity() - in->demand[node]);



	nodes_inserted[node] = true;

}

void Ils::randomCheapestInit(Individuo &s, int node){

    	int random_possibility;

        computePossibilities(s, node);

        if(permutations.size() >= fit_factor){
            random_possibility = rand() % fit_factor;		
        }else{
            random_possibility = 0;
        }

        vector<int>::iterator it = s.route[permutations[random_possibility].vehicle].begin() + permutations[random_possibility].index;

        s.route[permutations[random_possibility].vehicle].insert(it, node);
        s.fleet[permutations[random_possibility].vehicle].setCapacity(
        s.fleet[permutations[random_possibility].vehicle].getCapacity() - in->demand[node]);
        
        nodes_inserted[node] = true;
}

int Ils::delta2Evaluation(Individuo &s, int vehicle, int i, int k){

    current_value = calculatePartialRoute(s, vehicle, i, k);

	swap(s.route[vehicle][i], s.route[vehicle][k]);

	new_value = calculatePartialRoute(s, vehicle, i, k);

	swap(s.route[vehicle][i], s.route[vehicle][k]);

	return new_value - current_value;

}

int Ils::delta3Evaluation(Individuo &s, int vehicle, int i, int j, int k){

	current1 = calculatePartialRoute(s, vehicle, i, j);

	swap(s.route[vehicle][i], s.route[vehicle][j]);

	change1 = calculatePartialRoute(s, vehicle, i, j);

	swap(s.route[vehicle][i], s.route[vehicle][j]);
	
		
	current2 = calculatePartialRoute(s, vehicle, i, k);

	swap(s.route[vehicle][i], s.route[vehicle][k]);

	change2 = calculatePartialRoute(s, vehicle, i, k);

	swap(s.route[vehicle][i], s.route[vehicle][k]);


	current3 = calculatePartialRoute(s, vehicle, j, k);

	swap(s.route[vehicle][j], s.route[vehicle][k]);

	change3 = calculatePartialRoute(s, vehicle, j, k);

	swap(s.route[vehicle][j], s.route[vehicle][k]); 



}

int Ils::calculatePartialRoute(Individuo &s, int vehicle, int i, int k){

	if(i == k - 1){
		return in->distance_matrix[s.route[vehicle][i-1]][s.route[vehicle][i]] 
				+ in->distance_matrix[s.route[vehicle][i]][s.route[vehicle][k]] 
				+ in->distance_matrix[s.route[vehicle][k]][s.route[vehicle][k+1]];
	}

	if(i == k + 1){
		return in->distance_matrix[s.route[vehicle][k-1]][s.route[vehicle][k]]
				+ in->distance_matrix[s.route[vehicle][k]][s.route[vehicle][i]] 
				+ in->distance_matrix[s.route[vehicle][i]][s.route[vehicle][i+1]]; 
				
	}

	return 	in->distance_matrix[s.route[vehicle][i-1]][s.route[vehicle][i]] 
			+ in->distance_matrix[s.route[vehicle][i]][s.route[vehicle][i+1]] 
			+ in->distance_matrix[s.route[vehicle][k-1]][s.route[vehicle][k]] 
			+ in->distance_matrix[s.route[vehicle][k]][s.route[vehicle][k+1]];

}

void Ils::swapNodes(Individuo &s, int vehicle, int i, int k){

    current_value = calculatePartialRoute(s, vehicle, i, k);

	swap(s.route[vehicle][i], s.route[vehicle][k]);

	new_value = calculatePartialRoute(s, vehicle, i, k);

	s.setFitness(s.getFitness() - current_value + new_value);
}

void Ils::threeOptBest(Individuo &s){

	global_improvement = true;

	best_i = best_k = -1;
	delta = 1;

	for (unsigned int vehicle = 0; vehicle < s.route.size(); vehicle++)
	{


		if(s.route[vehicle].size() <= 1)
			continue;


		while (global_improvement)
		{
			global_improvement = false;


			lowest_fitness = s.getFitness();

			for (unsigned int i = 1; i < s.route[vehicle].size() - 2; i++)
			{

				best_delta = 0;

				local_improvement = false;

				for (unsigned int k = i + 1; k < s.route[vehicle].size() - 1; k++)
				{
					
						delta = delta2Evaluation(s, vehicle, i, k);

						if (delta < 0 && delta < best_delta)
						{

							best_delta = delta;
							best_i = i;
							best_k = k;
							local_improvement = true;
						}
				
				}

				if (local_improvement)
				{

					swapNodes(s, vehicle, best_i, best_k);

					if (s.getFitness() < lowest_fitness)
					{
						global_improvement = true;
					}
				}

			}

		}

	}

}

void Ils::twoOptBest(Individuo &s){

    global_improvement = true;

	best_i = best_k = -1;
	delta = 1;

	for (unsigned int vehicle = 0; vehicle < s.route.size(); vehicle++)
	{


		if(s.route[vehicle].size() <= 1)
			continue;

		while (global_improvement)
		{
			global_improvement = false;


			lowest_fitness = s.getFitness();

			for (unsigned int i = 1; i < s.route[vehicle].size() - 2; i++)
			{

				best_delta = 0;

				local_improvement = false;

				for (unsigned int k = i + 1; k < s.route[vehicle].size() - 1; k++)
				{
					
						delta = delta2Evaluation(s, vehicle, i, k);

						if (delta < 0 && delta < best_delta)
						{

							best_delta = delta;
							best_i = i;
							best_k = k;
							local_improvement = true;
						}
				
				}

				if (local_improvement)
				{

					swapNodes(s, vehicle, best_i, best_k);

					if (s.getFitness() < lowest_fitness)
					{
						global_improvement = true;
					}
				}

			}

		}

	}
}

bool Ils::capacityIsSatisfied(Individuo &s, int vehicle1, int vehicle2, int i, int k){

    int capacity1, capacity2;


	if (vehicle1 == vehicle2)
		return true;

	capacity1 = s.fleet[vehicle1].getCapacity();
	capacity2 = s.fleet[vehicle2].getCapacity();

	if (capacity1 + in->demand[s.route[vehicle1][node1]] - in->demand[s.route[vehicle2][node2]] >= 0 &&
		capacity2 + in->demand[s.route[vehicle2][node2]] - in->demand[s.route[vehicle1][node1]] >= 0)
	{

		return true;
	}

	return false;


}

void Ils::chooseNodes(Individuo &s){

    do
	{
		vehicle1 = rand() % in->num_vertices;
		//cout << "b" << endl;
	} while (s.route[vehicle1].size() <= 3);

	do
	{
		vehicle2 = rand() % in->num_vertices;
		//cout << "c" << endl;
	} while (s.route[vehicle2].size() <= 3);

	do{
		node1 = rand() % s.route[vehicle1].size();
		//cout << "d" << endl;
	}while(s.route[vehicle1][node1] == 0);
	
	do
	{
		node2 = rand() % s.route[vehicle2].size();
		//cout << "e" << endl;

	} while (s.route[vehicle1][node1] == s.route[vehicle2][node2] 
	|| s.route[vehicle2][node2] == 0);

}

void Ils::perturbation(Individuo &s, int level){

	if(level <= maxIdleIterations * 0.50){
		swap2Nodes(s);
	}
	else if(level > maxIdleIterations * 0.50 && level <= maxIdleIterations * 0.75){

		for(int i = 0; i < level; i++)
			swap2Nodes(s);
	}
	else if(level > maxIdleIterations * 0.75)
		scramble(s);
}

int Ils::calculatePartialDiffRoute(Individuo &s, int vehicle1, int vehicle2, int i, int k){

    if(vehicle1 == vehicle2){

        if(i == k - 1){
                    return in->distance_matrix[s.route[vehicle1][i-1]][s.route[vehicle1][i]] 
                        + in->distance_matrix[s.route[vehicle1][i]][s.route[vehicle2][k]] 
                        + in->distance_matrix[s.route[vehicle2][k]][s.route[vehicle2][k+1]];
        }

        if(i == k + 1){
            return in->distance_matrix[s.route[vehicle2][k-1]][s.route[vehicle2][k]]
                    + in->distance_matrix[s.route[vehicle2][k]][s.route[vehicle1][i]] 
                    + in->distance_matrix[s.route[vehicle1][i]][s.route[vehicle1][i+1]]; 
                    
        }
	}


	return 	in->distance_matrix[s.route[vehicle1][i-1]][s.route[vehicle1][i]] 
			+ in->distance_matrix[s.route[vehicle1][i]][s.route[vehicle1][i+1]] 
			+ in->distance_matrix[s.route[vehicle2][k-1]][s.route[vehicle2][k]] 
			+ in->distance_matrix[s.route[vehicle2][k]][s.route[vehicle2][k+1]];
}

void Ils::swapNodesCapacity(Individuo &s, int vehicle1, int vehicle2, int i, int k){

    if(vehicle1 != vehicle2){


		s.fleet[vehicle1].setCapacity(s.fleet[vehicle1].getCapacity() 
			+ in->demand[ s.route[vehicle1][i] ] - in->demand[ s.route[vehicle2][k] ] );
		
		s.fleet[vehicle2].setCapacity(s.fleet[vehicle2].getCapacity() 
			+ in->demand[ s.route[vehicle2][k] ] - in->demand[ s.route[vehicle1][i] ] );
		
	}

	current_value = calculatePartialDiffRoute(s, vehicle1, vehicle2, i, k);

	swap(s.route[vehicle1][i], s.route[vehicle2][k]);

	new_value = calculatePartialDiffRoute(s, vehicle1, vehicle2, i, k);

	s.setFitness(s.getFitness() - current_value + new_value);
}

void Ils::swap2Nodes(Individuo &s){

    do{
		chooseNodes(s);
	}while(!capacityIsSatisfied(s, vehicle1, vehicle2, node1, node2));

	if (node1 < node2)
		swapNodesCapacity(s, vehicle1, vehicle2, node1, node2);

	else
		swapNodesCapacity(s, vehicle2, vehicle1, node2, node1);

}

void Ils::scramble(Individuo &s){

	do
	{
		vehicle1 = rand() % in->num_vertices;
		//cout << "b" << endl;
	} while (s.route[vehicle1].size() <= 3);


	random_shuffle(s.route[vehicle1].begin() + 1, s.route[vehicle1].end() - 1);

	s.calculateFitness();

}

void Ils::invert(Individuo &s){

		do
	{
		vehicle1 = rand() % in->num_vertices;
		//cout << "b" << endl;
	} while (s.route[vehicle1].size() <= 3);


	reverse(s.route[vehicle1].begin(), s.route[vehicle1].end());

	s.calculateFitness();

}

void Ils::localSearch(Individuo &s){

}

void Ils::showResult(){

    //best.printRoute();
	//best.printFitness();
}

void Ils::run()
{

	//Solutions
    Individuo best,
			  current,
              local;
	int contador=0;

    int idleIterations = 0,
        iterations = 0;
	
	 create(best);

    do
    {

		idleIterations = 0;

		improvement = false;

        create(current);

        if (current.getFitness() < best.getFitness()){
            best = current;
			cout << "Best: " << best.getFitness() << endl;
		}

        twoOptBest(current);

        if (current.getFitness() < best.getFitness()){
            best = current;
			cout << "Best: " << best.getFitness() << endl;
		}

		#ifdef DEBUG3
			cout << "best: " << best.getFitness() << endl;
		#endif

        do
        {	
			//create(local);
            local = current;
						
            perturbation(local, idleIterations);
			//cout << "Local antes: " << local.getFitness() << endl;
			//cout << "Current antes: " << current.getFitness() << endl;
            twoOptBest(local);
			//cout << "Current: depois " << current.getFitness() << endl;
			//cout << "Local: depois " << local.getFitness() << endl;
			//cout << "Contador " << contador++ << endl;
			//cout << "Best: " << best.getFitness() << endl;
			//cout << idleIterations << " " << iterations << endl;

            if (local.getFitness() < current.getFitness()){
                current = local;
				
				if (current.getFitness() < best.getFitness())
				{
					best = current;
					improvement = true;
					idleIterations = 0;
					cout << "Best: " << best.getFitness() << endl;
					
            	}
			}
			else
				idleIterations++;
			
        } while (idleIterations < maxIdleIterations);
	
	if(!improvement)
		iterations++;
	else
		iterations=0;

    } while (improvement || iterations < maxIterations);

	best.printRoute();
	best.printFitness();
}