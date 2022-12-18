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
    bool setGeneticCode(int* newGeneticCode);
    ///bool setRandomGeneticCode();
    bool setProblemInstance(CProblem* newProblem);
    bool mutate(double mutationProbability);
    int* getGeneticCode();
    void operator=(CIndividual&& otherIndividual);
    void operator=(CIndividual& otherIndividual);
    std::vector<CIndividual>crossIndividualsSinglePoint(CIndividual &otherIndividual);
private:
    int geneticCodeLength;
    int* geneticCode;
    CProblem* problem;
};




#endif //TEP6MINIPROJEKT_CINDIVIDUAL_H
