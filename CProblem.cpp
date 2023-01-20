//
// Created by wieslaw on 17.12.22.
//

#include "CProblem.h"

bool CProblem::setCodeLength(int length) {
    if(length<0){
        return false;
    }
    else{
        codeLength=length;
        return true;
    }
}


int CProblem::getCodeLength() {
    return codeLength;
}

CProblem::CProblem(){
    codeLength=0;
}
CProblem::~CProblem() {

}

double CProblem::solutionValue(std::vector<int> *genotypeCode) {
    return 0;
}

bool CProblem::loadFromFile(std::string fileName) {
    return false;
}
bool CProblem::isDataLoaded() {
    return dataProperlyLoaded;
}
