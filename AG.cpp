//
// Created by wieslaw on 17.12.22.
//

#include <ctime>
#include "AG.h"
#include "Util.h"

AG::AG(){
    population = NULL;
    populationSize=-1;
    tournamentSize=-1;
    properlySetUp=false;
    srand(time(NULL));
}
AG::~AG(){
    if(population!=NULL){
        delete [] population;
    }
}

bool AG::setParameters(int populationSize, double crossProb,double mutationProb, double stopTime, int tournamentSize, CProblem* problem) {
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
    this->tournamentSize = tournamentSize;

    if(problem->isDataLoaded()){
        properlySetUp=true;

        return true;
    }else{
        return false;
    }

}
/*
CIndividual& AG::getBestSolution() {
    int* tab = bestSolution.getGeneticCode();
    std::cout<<bestSolutionScore<<std::endl;
    for(int i=0;i<problem->getCodeLength();i++){
        std::cout<<i<<": "<<tab[i]<<std::endl;
    }
    return bestSolution;
}
*/
CIndividual AG::getBestSolution() {
    /*
    int *tab = bestSolution.getGeneticCode();
    std::cout << bestSolutionScore << std::endl;
    for (int i = 0; i < problem->getCodeLength(); i++) {
        std::cout << i << ": " << tab[i] << std::endl;
    }
    return bestSolution;
     */
    /*
    if(properlySetUp){
        return bestSolution;
    }else{
        return std::move(CIndividual());
    }
     */
    setNewBestSolution();
    return std::move(bestSolution);


}
bool AG::runIteration() {
    if(properlySetUp){
      //  setNewBestSolution();
        solutionsCrossing();
        solutionsMutation();
        return true;
    }else{
        return false;
    }

}

bool AG::setNewBestSolution(){
    if(!properlySetUp){
        return false;
    }else{
        double currentFitness;
        bool betterSolutionFound=false;
        int bestSolutionIndex=0;
        double bestSolutionScore=-1;

        for(int i=0;i<populationSize;i++){
            currentFitness = population[i].fitness();
            if(currentFitness>bestSolutionScore){
                bestSolutionScore=currentFitness;
                bestSolutionIndex = i;
                betterSolutionFound=true;
            }
        }

        bestSolution = population[bestSolutionIndex];

        return betterSolutionFound;
    }
}
int AG::getParentFromTournament(){

    int currentParentIndex;
    double bestSolution=-1;
    double currentSolution;
    int bestParentIndex=-1;

    for(int i=0;i<tournamentSize;i++){
        currentParentIndex =  rand() % populationSize;
        currentSolution=population[currentParentIndex].fitness();

        if(currentSolution>=bestSolution){
            bestParentIndex=currentParentIndex;
            bestSolution=currentSolution;
        }
    }

    return bestParentIndex;
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

        for(int i=0;i<populationSize;i+=2) {

            indexOfFirstParent = getParentFromTournament();
            indexOfSecondParent = getParentFromTournament();


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
            if(i+1<populationSize){
                newPopulation[i+1] = std::move(children.at(1));
            }


            children.clear();

        }
        ///children.clear();
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
            population[i].mutate(mutationProb, population[rand()%populationSize]);
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
bool AG::runAlgorithm(){
    long timeOfStart = getCurrentTime();
    if(properlySetUp){
        initializePopulation();
        while(getCurrentTime()<timeOfStart+stopTime*MILISECONDS_IN_SECONDS){
            runIteration();
        }
        return true;
    }else{
        return false;
    }
}

