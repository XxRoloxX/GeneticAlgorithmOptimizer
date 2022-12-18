cmake_minimum_required(VERSION 3.24)
project(TEP6MiniProjekt)

set(CMAKE_CXX_STANDARD 17)

add_executable(TEP6MiniProjekt main.cpp CKnapsackProblem.cpp CKnapsackProblem.h CIndividual.cpp CIndividual.h CProblem.cpp CProblem.h AG.cpp AG.h Util.cpp Util.h)
