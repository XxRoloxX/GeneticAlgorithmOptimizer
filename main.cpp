#include <iostream>
#include "CKnapsackProblem.h"
#include "AG.h"


int main() {

    AG alg;
    CProblem* knapSackProblem = new CKnapsackProblem();
    knapSackProblem->loadFromFile("CKnapsack2.txt");
    alg.setParameters(100,0.4,0.2,1,10,knapSackProblem);
    /*
    alg.initializePopulation();
    for(int i=0;i<500;i++){
        alg.runIteration();
    }
    alg.getBestSolution();
    */

    alg.runAlgorithm();
    //CIndividual result = alg.getBestSolution();
    CIndividual result = alg.getBestSolution();

    result.printGeneticCode();
    delete knapSackProblem;

    return 0;
}
