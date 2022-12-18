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
   virtual double solutionValue(int* genotypeCode);
   virtual bool loadFromFile(std::string fileName);
   bool setCodeLength(int length);
   int getCodeLength();
private:
    int codeLength;
};


#endif //TEP6MINIPROJEKT_CPROBLEM_H
