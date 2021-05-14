cmake_minimum_required(VERSION 3.19)
project(CAL_P1)

set(CMAKE_CXX_STANDARD 14)

# Build GraphViewerCpp
set(GRAPHVIEWERCPP_PATH lib/GraphViewerCpp)
add_subdirectory(${GRAPHVIEWERCPP_PATH})
include_directories(${GRAPHVIEWERCPP_PATH}/include)

add_executable(CAL_P1 main.cpp src/Vehicle/vehicle.h src/Basket/basket.h src/Basket/basket.cpp src/Vehicle/vehicle.cpp src/Company/company.h src/Company/company.cpp src/Graph/Graph.h src/Graph/MutablePriorityQueue.h src/GraphBuilder/graphbuilder.h src/Utils/utils.h src/Utils/utils.cpp src/Gui/gui.h)

target_link_libraries(CAL_P1 graphviewer)
