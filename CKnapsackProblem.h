//
// Created by wieslaw on 12.12.22.
//

#ifndef TEP6MINIPROJEKT_CKNAPSACKPROBLEM_H
#define TEP6MINIPROJEKT_CKNAPSACKPROBLEM_H
#include <iostream>
#include <vector>
#include "CProblem.h"

class CKnapsackProblem: public CProblem {
public:

    CKnapsackProblem();
    ~CKnapsackProblem();
    //bool setItemTable(int** itemTable, int tableLength, double maxWeight);
    double solutionValue(std::vector<int>* genotypeCode);
    bool loadFromFile(std::string fileName);
    bool isTableLoaded();

private:
    bool deallocateItemTable();
    ///item table consists of Nx2 matrix. First column consists of weights, second one consists of values
    int** itemTable;
    int tableLength;
    double maxWeight;



};








#endif //TEP6MINIPROJEKT_CKNAPSACKPROBLEM_H
