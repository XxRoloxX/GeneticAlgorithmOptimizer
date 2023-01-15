//
// Created by wieslaw on 12.12.22.
//

#include <fstream>
#include "CKnapsackProblem.h"
#include "CProblem.h"

CKnapsackProblem::CKnapsackProblem(){

    itemTable=NULL;
    tableLength=0;
    maxWeight=0;
    dataProperlyLoaded=false;
}

CKnapsackProblem::~CKnapsackProblem(){
    deallocateItemTable();
}
bool CKnapsackProblem::deallocateItemTable() {

    if(dataProperlyLoaded && itemTable!=NULL){
        for(int i=0;i<tableLength;i++){
            delete this->itemTable[i];
        }
        delete itemTable;

        return true;
    }else{
        return false;
    }
}

bool CKnapsackProblem::setItemTable(int** itemTable, int tableLength, double maxWeight){

    if(tableLength<=0 || maxWeight<=0){
        return false;
    }
    else{
        this->tableLength=tableLength;
        this->maxWeight=maxWeight;
        this->setCodeLength(tableLength);

        deallocateItemTable();
        this->itemTable=itemTable;

        return true;
    }


}

double CKnapsackProblem::solutionValue(int* genotypeCode) {
    double valueSum=0;
    double weightSum=0;
    if(dataProperlyLoaded){
        for(int i=0;i<tableLength && weightSum<=maxWeight;i++){
            valueSum+=genotypeCode[i]*itemTable[i][0];
            weightSum+=genotypeCode[i]*itemTable[i][1];
        }

        if(weightSum>maxWeight){
            valueSum=0;
        }
    }


    return valueSum;
}
bool CKnapsackProblem::loadFromFile(std::string fileName) {

    std::ifstream myFile(fileName);
    ///myFile.open(fileName);
    int** newTable;

    if(myFile.fail()){
        return false;
    }else{

        if(itemTable!=NULL){
            for(int i=0;i<tableLength;i++){
                delete itemTable[i];
            }
        }

        myFile>>tableLength;
        myFile>>maxWeight;

        if(tableLength<=0 || maxWeight<=0){
            myFile.close();
            return false;
        }

        this->setCodeLength(tableLength);


        newTable = new int*[tableLength];

        for(int i=0;i<tableLength;i++){
            newTable[i] = new int[2];
            myFile >> newTable[i][0];
            myFile >> newTable[i][1];
        }

        myFile.close();

        itemTable=newTable;
        dataProperlyLoaded=true;
        return true;
    }
}

