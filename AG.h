//
// Created by wieslaw on 17.12.22.
//

#ifndef TEP6MINIPROJEKT_AG_H
#define TEP6MINIPROJEKT_AG_H


#include "CIndividual.h"
const int TOURNAMENT_SIZE=5;

class AG {
public:
    AG();
    ~AG();
    bool setParameters(int populationSize, double crossProb,double mutationProb, double stopTime,int tournamentSize, CProblem* problem);
    CIndividual getBestSolution();
    bool runIteration();
    bool initializePopulation();
    bool runAlgorithm();

private:
    int populationSize;
    CIndividual* population;

    CProblem* problem;

    bool properlySetUp;
    //double bestSolutionScore;
    CIndividual bestSolution;

    double crossProb;
    double mutationProb;
    double stopTime;
    int tournamentSize;

    bool setNewBestSolution();
    bool solutionsCrossing();
    bool solutionsMutation();
    int getParentFromTournament();


};


#endif //TEP6MINIPROJEKT_AG_H
