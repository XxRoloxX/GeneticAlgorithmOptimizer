//
// Created by wieslaw on 12.12.22.
//

#include "CIndividual.h"
#include "CProblem.h"
#include <iostream>
#include <random>
#include "Util.h"

/*
class CIndividual {
public:
    CIndividual();
    double fitness();
    std::byte* getGeneticCode();
    bool setGeneticCode(std::byte* newGeneticCode, int newGeneticCodeLength);
    bool mutate(CIndividual otherIndividual);
    CIndividual* crossIndividuals(CIndividual otherIndividual);
private:
    std::byte* geneticCode;
    int geneticCodeLength;
};
 */

CIndividual::CIndividual(){

    geneticCodeLength=0;
    geneticCode=NULL;
    problem=NULL;
}
CIndividual::~CIndividual(){
    if(geneticCode!=NULL){
        delete geneticCode;
    }

}
void CIndividual::operator=(CIndividual &&otherIndividual) {
    if(geneticCode!=NULL){
        delete geneticCode;
    }
    geneticCode=otherIndividual.geneticCode;
    geneticCodeLength=otherIndividual.geneticCodeLength;
    problem=otherIndividual.problem;
    otherIndividual.geneticCode =NULL;

}
void CIndividual::operator=(CIndividual& otherIndividual) {

    if(geneticCode!=NULL){
        delete geneticCode;
    }
    geneticCodeLength=otherIndividual.geneticCodeLength;
    geneticCode = new std::vector<int>(geneticCodeLength);
    problem=otherIndividual.problem;

    for(int i=0;i<geneticCodeLength;i++){
        (*geneticCode)[i]=(*otherIndividual.geneticCode)[i];
    }
}
CIndividual::CIndividual(CIndividual&& otherIndividual) {
    geneticCode = otherIndividual.geneticCode;
    geneticCodeLength=otherIndividual.geneticCodeLength;
    problem = otherIndividual.problem;
    otherIndividual.geneticCode=NULL;
}
CIndividual::CIndividual(const CIndividual& otherIndividual) {
    geneticCodeLength=otherIndividual.geneticCodeLength;
    problem=otherIndividual.problem;
    geneticCode = new std::vector<int>(geneticCodeLength);
    for(int i=0;i<geneticCodeLength;i++){
        (*geneticCode)[i]=(*otherIndividual.geneticCode)[i];
    }

}
///If problemInstance is not NULL then return solution value as fitness
double CIndividual::fitness(){
    if(problem==NULL){
        return -1;
    }
    else{
        return problem->solutionValue(geneticCode);
    }
}

bool CIndividual::setProblemInstance(CProblem* newProblem) {
    if(newProblem!=NULL && newProblem->getCodeLength()>0){
        problem=newProblem;
        geneticCodeLength = newProblem->getCodeLength();
        return true;
    }else{
        return false;
    }

}
/*
bool CIndividual::setGeneticCode(int* newGeneticCode, int newGeneticCodeLength){
    if(newGeneticCode==NULL || newGeneticCodeLength<=0){
        return false;
    }

    geneticCode = newGeneticCode;
    geneticCodeLength=newGeneticCodeLength;
    return true;
}
 */

std::vector<int>* CIndividual::getGeneticCode(){
    return geneticCode;
}
/*
int CIndividual::getGeneticCodeLength(){
    return geneticCodeLength;
}
 */
/*
bool CIndividual::mutate(double mutationProbability){

    if(mutationProbability<0 || mutationProbability>1){
        return false;
    }

    double chance;

    for(int i=0;i<geneticCodeLength;i++){
        chance = generateRandomRealNumber(0,1);
        if(chance<mutationProbability){
            (*geneticCode)[i] = 1-(*geneticCode)[i];
        }
    }

    return true;
}
 */
bool CIndividual::mutate(double mutationProbability, CIndividual& other){
    if(geneticCodeLength!=other.geneticCodeLength){
        return false;
    }else{

        double chance;

        for(int i=0;i<geneticCodeLength;i++){
            if((*geneticCode)[i]!=(*other.geneticCode)[i]){
                chance = generateRandomRealNumber(0,1);
                if(chance<mutationProbability){
                    (*geneticCode)[i] = 1-(*geneticCode)[i];
                }
            }
        }

        return true;

    }
}
///Returns vector of crossed individuals
std::vector<CIndividual> CIndividual::crossIndividualsSinglePoint(CIndividual &otherIndividual) {
    int crossingPoint = rand()%geneticCodeLength;

    ///Create static objects
    CIndividual child1;
    CIndividual child2;

    ///Assign problems instances
    child1.setProblemInstance(problem);
    child2.setProblemInstance(problem);

    ///Create static vector with result children
    std::vector<CIndividual> vChildren;


    std::vector<int>* child1GeneticCode = new std::vector<int>(geneticCodeLength);
    std::vector<int>* child2GeneticCode = new std::vector<int>(geneticCodeLength);

    ///Actual single-point crossing algorithm
    for(int i=0;i<geneticCodeLength;i++){
        if(i<crossingPoint){
            (*child1GeneticCode)[i]=(*geneticCode)[i];
            (*child2GeneticCode)[i]=(*otherIndividual.geneticCode)[i];
        }
        else{
            (*child2GeneticCode)[i]=(*geneticCode)[i];
            (*child1GeneticCode)[i]=(*otherIndividual.geneticCode)[i];
        }
    }

    ///Set genetic code in resulting children
    child1.setGeneticCode(child1GeneticCode);
    child2.setGeneticCode(child2GeneticCode);

    child1.setProblemInstance(problem);
    child2.setProblemInstance(problem);


    ///Add children to children vector using MS
    vChildren.push_back(std::move(child1));
    vChildren.push_back(std::move(child2));

    return std::move(vChildren);
}
///Only copies reference not actual structure
bool CIndividual::setGeneticCode(std::vector<int>* newGeneticCode) {

    if(newGeneticCode==NULL){
        return false;
    }
    else{
        geneticCode=newGeneticCode;
        return true;
    }
}
void CIndividual::printGeneticCode(){

    if(problem!=NULL && geneticCode!=NULL){
        std::cout <<"Score: "<<fitness() << std::endl;
        std::cout<<"[";
        for (int i = 0; i < problem->getCodeLength(); i++) {
            std::cout <<(*geneticCode)[i]<<", ";
        }
        std::cout<<"]";
        std::cout<<std::endl;

    }

}