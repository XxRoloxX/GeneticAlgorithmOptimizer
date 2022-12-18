//
// Created by wieslaw on 17.12.22.
//

#ifndef TEP6MINIPROJEKT_AG_H
#define TEP6MINIPROJEKT_AG_H


#include "CIndividual.h"

class AG {
public:
    AG();
    ~AG();
    bool setParameters(int populationSize, double crossProb,double mutationProb, double stopTime, CProblem* problem);
    CIndividual& getBestSolution();
    void runIteration();
    bool initializePopulation();

private:
    int populationSize;
    CIndividual* population;

    CProblem* problem;

    bool properlySetUp;
    double bestSolutionScore;
    CIndividual bestSolution;

    double crossProb;
    double mutationProb;
    double stopTime;

    bool setNewBestSolution();
    bool solutionsCrossing();
    bool solutionsMutation();


};


#endif //TEP6MINIPROJEKT_AG_H
