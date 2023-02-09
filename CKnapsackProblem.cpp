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
/*
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
 */

double CKnapsackProblem::solutionValue(std::vector<int>* genotypeCode) {
    double valueSum=0;
    double weightSum=0;
    if(dataProperlyLoaded && genotypeCode->size()==tableLength){
        for(int i=0;i<tableLength && weightSum<=maxWeight;i++){
            valueSum+=(*genotypeCode)[i]*itemTable[i][0];
            weightSum+=(*genotypeCode)[i]*itemTable[i][1];
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
    bool incorrectData=false;

    ///Check if file is correct
    if(myFile.fail()){
        dataProperlyLoaded=false;
        return false;
    }else{
        ///Deallocate previous table
        if(itemTable!=NULL){
            for(int i=0;i<tableLength;i++){
                delete itemTable[i];
            }
        }

        ///Read KnapsackProblem paremeters
        myFile>>tableLength;
        myFile>>maxWeight;

        ///Make sure parameters are correct
        if(tableLength<=0 || maxWeight<=0){
            myFile.close();
            dataProperlyLoaded=false;
            return false;
        }


        this->setCodeLength(tableLength);


        newTable = new int*[tableLength];

        for(int i=0;i<tableLength;i++){
            newTable[i]=NULL;
        }

        ///Load table data
        for(int i=0;i<tableLength && !incorrectData;i++){
            newTable[i] = new int[2];
            myFile >> newTable[i][0];
            myFile >> newTable[i][1];

            if(newTable[i][0]<=0 || newTable[i][1]<=0){
                incorrectData=true;
            }

        }

        myFile.close();

        ///File succescully read, save to itemTable, and mark as properly loaded object
        if(!incorrectData){
            itemTable=newTable;
            dataProperlyLoaded=true;
            return true;

        }else{

            ///deallocate incorrect table
            for(int i=0;i<tableLength;i++){
                if(newTable[i]!=NULL){
                    delete newTable[i];
                }
            }
            delete newTable;

            dataProperlyLoaded=false;
            return false;

        }

    }
}

