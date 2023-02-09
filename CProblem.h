//
// Created by wieslaw on 17.12.22.
//

#ifndef TEP6MINIPROJEKT_CPROBLEM_H
#define TEP6MINIPROJEKT_CPROBLEM_H
#include <cstdio>
#include <vector>
#include <string>

class CProblem {
public:
    CProblem();
    virtual ~CProblem();
   virtual double solutionValue(std::vector<int>* genotypeCode);
   virtual bool loadFromFile(std::string fileName);
   virtual int getCodeLength();
   bool isDataLoaded();
protected:
    bool setCodeLength(int length);
    int codeLength;
    bool dataProperlyLoaded;

};


#endif //TEP6MINIPROJEKT_CPROBLEM_H
