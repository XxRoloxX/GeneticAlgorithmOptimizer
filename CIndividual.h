//
// Created by wieslaw on 12.12.22.
//

#ifndef TEP6MINIPROJEKT_CINDIVIDUAL_H
#define TEP6MINIPROJEKT_CINDIVIDUAL_H

#include <iostream>
#include <vector>
#include <bitset>
#include "CProblem.h"

class CIndividual {
public:
    CIndividual();
    ~CIndividual();
    CIndividual(CIndividual&& otherIndividual);
    CIndividual(const CIndividual& otherIndividual);
    double fitness();
    bool setGeneticCode(std::vector<int>* newGeneticCode);
    ///bool setRandomGeneticCode();
    bool setProblemInstance(CProblem* newProblem);
    //bool mutate(double mutationProbability);
    bool mutate(double mutationProbability, CIndividual& other);
    std::vector<int>* getGeneticCode();
    void operator=(CIndividual&& otherIndividual);
    void operator=(CIndividual& otherIndividual);
    void printGeneticCode();
    std::vector<CIndividual>crossIndividualsSinglePoint(CIndividual &otherIndividual);
private:
    int geneticCodeLength;
    std::vector<int>* geneticCode;
    CProblem* problem;
};




#endif //TEP6MINIPROJEKT_CINDIVIDUAL_H
