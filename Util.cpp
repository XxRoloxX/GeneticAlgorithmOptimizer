//
// Created by wieslaw on 18.12.22.
//

#include <cstdlib>
#include <ctime>
#include <random>
#include "Util.h"

int*generateRandomBinaryList(int listSize) {

    int* resultList = new int[listSize];
    srand(time(NULL));

    for(int i=0;i<listSize;i++){

            resultList[i]=rand()%2;
    }

    return resultList;

}

double generateRandomRealNumber(double min, double max){
    return ((double)rand())/RAND_MAX *(max-min) + min;
}
