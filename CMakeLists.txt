cmake_minimum_required(VERSION 3.19)
project(CAL_P1)

set(CMAKE_CXX_STANDARD 14)

add_executable(CAL_P1 main.cpp src/Vehicle/vehicle.h src/Basket/basket.h src/Basket/basket.cpp src/Vehicle/vehicle.cpp src/Company/company.h src/Company/company.cpp src/Graph/Graph.h src/Graph/MutablePriorityQueue.h)
