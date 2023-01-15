//
// Created by wieslaw on 18.12.22.
//

#include <cstdlib>
#include <ctime>
#include <random>
#include "Util.h"
#include <chrono>


std::vector<int>*generateRandomBinaryList(int listSize) {

    std::vector<int>* resultList = new std::vector<int>(listSize);


    for(int i=0;i<listSize;i++){

        (*resultList)[i]=rand()%2;
    }

    return resultList;

}

double generateRandomRealNumber(double min, double max){
    return ((double)rand())/RAND_MAX *(max-min) + min;
}

long getCurrentTime(){
    return (std::chrono::duration_cast< std::chrono::milliseconds >(std::chrono::system_clock::now().time_since_epoch()).count());
}