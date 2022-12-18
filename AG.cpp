//
// Created by wieslaw on 17.12.22.
//

#include "AG.h"
#include "Util.h"

AG::AG(){
    population = NULL;
    populationSize=-1;
    bestSolutionScore=-1;
    properlySetUp=false;
}
AG::~AG(){
    if(population!=NULL){
        delete [] population;
    }
}

bool AG::setParameters(int populationSize, double crossProb,double mutationProb, double stopTime, CProblem* problem) {
    if(populationSize<=0 || crossProb<0 || crossProb>1 || stopTime<0 || problem ==NULL){
        return false;
    }

    this->populationSize=populationSize;
    this->crossProb = crossProb;
    this->stopTime = stopTime;
    this->problem = problem;
    this->mutationProb = mutationProb;
    population = new CIndividual[populationSize];
    bestSolution.setProblemInstance(problem);
    properlySetUp=true;

    return true;
}

CIndividual& AG::getBestSolution() {
    int* tab = bestSolution.getGeneticCode();
    std::cout<<bestSolutionScore<<std::endl;
    for(int i=0;i<problem->getCodeLength();i++){
        std::cout<<i<<": "<<tab[i]<<std::endl;
    }
    return bestSolution;
}

void AG::runIteration() {

    setNewBestSolution();
    solutionsCrossing();
    solutionsMutation();

}

bool AG::setNewBestSolution(){
    if(!properlySetUp){
        return false;
    }else{
        double currentFitness;
        bool betterSolutionFound;

        for(int i=0;i<populationSize;i++){
            currentFitness = population[i].fitness();
            if(currentFitness>bestSolutionScore){
                bestSolutionScore=currentFitness;
                bestSolution = (population[i]);
                betterSolutionFound=true;
            }
        }

        return betterSolutionFound;
    }
}

bool AG::solutionsCrossing(){
    if(!properlySetUp){
        return false;
    }
    else{
        std::vector<CIndividual> children(2);
        CIndividual* newPopulation = new CIndividual[populationSize];

        int indexOfFirstParent;
        int indexOfSecondParent;

        for(int i=0;i<populationSize-1;i+=2) {

            indexOfFirstParent = rand() % populationSize;
            indexOfSecondParent = rand() % populationSize;

            if (generateRandomRealNumber(0, 1) < crossProb) {
                children.clear();
                children = std::move(population[indexOfFirstParent].crossIndividualsSinglePoint(
                        population[indexOfSecondParent]));
            }else{
                children.clear();
                children.push_back(population[indexOfFirstParent]);
                children.push_back(population[indexOfSecondParent]);
            }

            newPopulation[i] = std::move(children.at(0));
            newPopulation[i+1] = std::move(children.at(1));
            children.clear();

        }
        children.clear();

        delete[] population;

        population = newPopulation;
        return true;
    }
}

bool AG::solutionsMutation(){

    if(!properlySetUp){
        return false;
    }else{
        for(int i=0;i<populationSize;i++){
            population[i].mutate(mutationProb);
        }
        return true;
    }

}

bool AG::initializePopulation() {
    ///Check if algorithm parameters were properly set up
    if(!properlySetUp){
        return false;
    }else {

        for(int i=0;i<populationSize;i++){
            population[i].setProblemInstance(problem);
            population[i].setGeneticCode(generateRandomBinaryList(problem->getCodeLength()));
        }
        return true;
    }
}

