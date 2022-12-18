#include <iostream>
#include "CKnapsackProblem.h"
#include "AG.h"


int main() {

    AG alg;
    CProblem* knapSackProblem = new CKnapsackProblem();
    knapSackProblem->loadFromFile("CKnapsack2.txt");
    alg.setParameters(10,0.4,0.1,200,knapSackProblem);

    alg.initializePopulation();
    for(int i=0;i<1000000;i++){
        alg.runIteration();
    }
    alg.getBestSolution();

    return 0;
}
